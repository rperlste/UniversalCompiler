#include "Parser.h"


ParserDriver::ParserDriver( const Grammar& grammar, ParseTable* parseTable ){
	this->grammar = grammar;
	this->parseTable = new ParseTable(*parseTable);
}

void ParserDriver::LLDriver( std::fstream& programFile, bool printOutput ){
	Scanner scanner( &programFile );
	Token currentInputToken;
	Symbol topStackSymbol;
	std::string parseAction = "";
	int position = 0;

	if( printOutput ){
		std::cout << "\n\n Parser Action                 RemainingInput                 Parse Stack\n"
			<<		 " ---------------------------------------------------------------------------";
	}

	std::fstream* scannerFile = scanner.getProgramFile();
	parseStack.push(grammar.getStartSymbol());
	while( !isStackEmpty() ){
		topStackSymbol = parseStack.top();
		position = scanner.getScannerFilePosition();
		currentInputToken = scanner.scan();
		if( grammar.nonterminalSet.contains( topStackSymbol )){
			try{
				// Find production: X -> Y1 Y2 ... Ym
				Production production = parseTable->getPredictProduction(
					topStackSymbol, currentInputToken.getTokenTypeString() );

				// Remove production X so that it can be replaced with it's derived production.
				parseStack.pop();
			
				if( printOutput ){
					std::stringstream parseAction;
					parseAction << grammar.productions.getIndex( production );
					
					std::cout << "\n " << parseAction.str();
					scannerFile->clear();
					scannerFile->seekg( position );
					std::string out;
					if( !scannerFile->eof() ){
						getline(*scannerFile, out);
						std::cout << "               " << out;
					}
					std::cout << "        ";
					for( int i = 0; i < production.getRHS().size(); i++ ){
						std::cout << production[i] << " ";
					}
					
					scannerFile->clear();
					scannerFile->seekg( position );
				}

				// Push production onto stack
				for( int i = production.getRHS().size(); i > 0; i-- ){
					parseStack.push(production[i-1]);
				}
			}
			catch( ProductionNotFound e ){
				std::string reason = "Error in production: "; 
				reason += topStackSymbol;
				reason += " => Error occured at value: ";
				reason += currentInputToken.getTokenTypeString();
				throw SyntaxError( reason );
			}
		}
		else if( grammar.terminalSet.contains( topStackSymbol )){
			if( topStackSymbol == currentInputToken.getTokenTypeString() ){
				parseStack.pop();
				currentInputToken = scanner.scan();
			}
		}
		else {
			throw SyntaxError( "Error occured at value: " + currentInputToken.getTokenTypeString());
		}
	}
}


bool ParserDriver::isStackEmpty(){
	return parseStack.empty();
}

ParserDriver::~ParserDriver(){
	delete parseTable;
}
