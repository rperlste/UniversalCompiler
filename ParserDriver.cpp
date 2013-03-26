#include "ParserDriver.h"


ParserDriver::ParserDriver( const Grammar& grammar ){
	this->grammar = grammar;
	this->parseTable = new ParseTable( grammar );
	parseTable->GenerateTable();
}

void ParserDriver::parse( std::fstream& programFile, bool printOutput ){
	Scanner scanner( &programFile );
	Token currentInputToken;
	Symbol topStackSymbol;

	// Formatting for output
	int fileWidth = scanner.getProgramFileLength();
	std::string currentStackValues = "";

	//Push(S); � � Push the Start Symbol onto an empty stack
	parseStack.push_front( grammar.getStartSymbol() );

	// let a be the current input token
	currentInputToken = scanner.peekNextToken();
	if( printOutput ){
		std::cout << "\n\n RemainingInput" << std::string( fileWidth - (fileWidth - 11), ' ' )  
			<< "\t  Action\t" << "ParseStack\n"
			<< " --------------------------------------------------------------------------------";
	}
	
	while( !parseStack.empty() ){

		if( printOutput ){
			std::cout << "\n";
			scanner.printRemainingFile();
			std::cout << std::string( 
				fileWidth - (fileWidth - scanner.getScannerBufferPosition()), ' ' ) << "\t  ";
			currentStackValues = "";
			for( int indexStack = parseStack.size() -1; indexStack > -1 ; indexStack -- ){
				currentStackValues += parseStack[indexStack] + " ";
			}
		}

		// let X be the top stack symbol; let a be the current input token
		topStackSymbol = parseStack.front();

		//if X in nonterminals
		if( grammar.nonterminalSet.contains( topStackSymbol ) ){

			// if T(X, a) = X �> Y1Y2. . .Ym
			try{
				Production production = parseTable->getPredictProduction( 
					topStackSymbol,
					(tokenEnumsValues[currentInputToken.getTokenType()] != "" ) 
						? tokenEnumsValues[currentInputToken.getTokenType()] 
						: currentInputToken.getTokenTypeString() );

				//Expand nonterminal, replace X with Y1Y2. . .Ym on the stack
				parseStack.pop_front();
				for( int indexRHS = production.getRHS().size() - 1; indexRHS > -1; indexRHS -- ){
					if(    production.getRHS()[indexRHS] != "" 
					    && production.getRHS()[indexRHS][0] != '#' )
						parseStack.push_front( production.getRHS()[indexRHS] );
				}

				if( printOutput ){
					std::cout << parseTable->getPredictIndex( topStackSymbol,
					(tokenEnumsValues[currentInputToken.getTokenType()] != "" ) 
						? tokenEnumsValues[currentInputToken.getTokenType()] 
						: currentInputToken.getTokenTypeString() );
				}

			} catch ( IndexOutOfBounds e ) {
				throw SyntaxError("Syntax error at: " + currentInputToken.getTokenValue());
			}
		}
		// X in terminals
		else {
			// Match of X worked
			parseStack.pop_front();
			scanner.scannerDriver();
			if( !scanner.isDoneScanning() )
				currentInputToken = scanner.peekNextToken();

			if( printOutput ){
				std::cout << "MATCH";
			}
		}

		if( printOutput ){
			std::cout << "\t\t" << currentStackValues;
		}
	}
}
