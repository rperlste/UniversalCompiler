#include "GrammarAnalyzer.h"


GrammarAnalyzer::GrammarAnalyzer( std::fstream* grammarFileIn ){
	grammarFile = grammarFileIn;
	grammarFile->clear();
	grammarFile->seekg(0);
	error = false;
}

void  GrammarAnalyzer::analyzeGrammar(){
	char charStream;
	std::string currentGrammar;
	std::string LHS_val;
	std::string RHS_val;
	while( !grammarFile->eof() ){
		Production production;
		LHS_val = _LAMBDA;
		RHS_val = _LAMBDA;
		RightHandSide RHS;
		currentGrammar = _LAMBDA;

		// read LHS first
		charStream = grammarFile->get();
		// remove leading whitespace
		if( charStream == ' ' ){
			while( charStream == ' ' )
				charStream = grammarFile->get();
		}
		currentGrammar += charStream;
		while( charStream != '>' ){
			charStream = grammarFile->get();
			currentGrammar += charStream;
		}

		// Complete LHS
		LHS_val = currentGrammar;
		production.setLHS( LHS_val );
		this->grammar.nonterminalSet.insert( LHS_val );

		// Clear trailing whitespace
		while( charStream != '-'
				&& charStream != '—'){
			charStream = grammarFile->get();
		}

		// Test for implies symbol
		charStream = grammarFile->get();
		if( charStream != '>' ){
			analyzeError( "Lacks implies symbol." );
			return;
		}
		
		// Clear leading whitespace
		currentGrammar = _LAMBDA;
		charStream = grammarFile->get();
		while( charStream == ' ' ){
			charStream = grammarFile->get();
		}

		// Extract RHS(s) of productions
		while( charStream != '\n'
			&& !grammarFile->eof() ){

				currentGrammar = _LAMBDA;
				// nonterminal
				if( charStream == '<' ){
					//currentGrammar += charStream;
					RHS_val += charStream;
					while( charStream != '>' ){
						charStream = grammarFile->get();
						//currentGrammar += charStream;
						RHS_val += charStream;
					}
					RHS.add( RHS_val );
					RHS_val = _LAMBDA;
					charStream = grammarFile->get();
				}

				// terminal
				else if( isalpha( charStream ) ){
					while( isalpha( charStream ) ){
						currentGrammar += charStream;
						RHS_val += charStream;
						charStream = grammarFile->get();
					}
					RHS.add( RHS_val );
					RHS_val = _LAMBDA;
					this->grammar.terminalSet.insert( currentGrammar );
				}

				// test for multiple productions
				else if( charStream == '|' ){
					if( RHS.size() == 0 ){
						this->grammar.terminalSet.insert( _LAMBDA );
						RHS.add( _LAMBDA );
					}
					production.setRHS( RHS );
					grammar.productions.add( production );
					RHS.clear();
					RHS_val = _LAMBDA;
					charStream = grammarFile->get();
					if( charStream == ' ' ){
						while( charStream == ' ' )
							charStream = grammarFile->get();
					}
					continue;
				}

				// test for whitespace
				else if( charStream == ' ' ){
					//RHS += charStream;
					charStream = grammarFile->get();
					continue;
				}
				// test for EOL
				else if( charStream == '\n' ){
					if( RHS.size() == 0 ){
						this->grammar.terminalSet.insert( _LAMBDA );
						RHS.add( _LAMBDA );
					}
					break;
				}
				
				// Symbol or unknown value
				else{
					RHS_val += charStream;
					charStream = grammarFile->get();
					RHS.add( RHS_val );
					this->grammar.terminalSet.insert( RHS_val );
					RHS_val = _LAMBDA;
				}
		}
		if( RHS.size() == 0 ){
			RHS.add( _LAMBDA );
			this->grammar.terminalSet.insert( _LAMBDA );
		}
		production.setRHS( RHS );
		grammar.productions.add( production );
	}
}

Grammar GrammarAnalyzer::getGrammar(){
	return grammar;
}

void GrammarAnalyzer::printProductions(){
	
	std::cout << "\n\n::: PRODUCTIONS :::";
	try{
		for( int i = 0; i < grammar.productions.size(); i++ ){
			std::cout << "\n" << grammar.productions.get(i).getLHS() << " ->";
			for( int k = 0; k < grammar.productions.get(i).getRHS().size(); k++ ){
				std::cout << " " << grammar.productions.get(i).getRHS().get(k);
			}
			
		}
	}
	catch( IndexOutOfBounds e){
		// Do nothing
	}
}


void GrammarAnalyzer::printDataTables(){
	
	std::cout << "\n\n::: LHS list :::";
	try{
		for( int i = 0; i < grammar.productions.size(); i++ ){
			std::cout << "\n" << grammar.productions.get(i).getLHS();
		}
	}
	catch( IndexOutOfBounds e){
		// Do nothing
	}

	std::cout << "\n\n::: RHS list :::";
	try{
		for( int i = 0; i < grammar.productions.size(); i++ ){
			std::cout << "\n";
			for( int k = 0; k < grammar.productions.get(i).getRHS().size(); k++ ){
				std::cout << grammar.productions.get(i).getRHS().get(k) << " ";
			}
			
		}
	}
	catch( IndexOutOfBounds e){
		// Do nothing
	}

	std::cout << "\n\n::: Non-terminal list :::";
	try{
		for( int i = 0; i < grammar.nonterminalSet.size(); i++ ){
			std::cout << "\n" << grammar.nonterminalSet[i];
		}
	}
	catch( IndexOutOfBounds e){
		// Do nothing
	}

	std::cout << "\n\n::: Terminal list :::";
	for( int i = 0; i < grammar.terminalSet.size(); i++ ){
		std::cout << "\n" << grammar.terminalSet[i];
	}
}


void GrammarAnalyzer::analyzeError( std::string error ){
	if( error.size() > 0 ){
		std::cout << "\nGRAMMAR ANALYSIS ERROR: " << error;
	}
}

void GrammarAnalyzer::printInputGrammar(){
	grammarFile->clear();
	grammarFile->seekg(0, std::ios::beg);
	std::cout << "\n\n::: Original Grammar :::";
	while( !grammarFile->eof() ){
		std::string output;
		getline( (*grammarFile), output );
		std::cout << "\n" << output;
	}
}