#include "UniversalCompiler.h"


UniversalCompiler::UniversalCompiler( const char* grammarFilePtr, const char* programFilePtr, const char* compiledFilePtr ){
	if( grammarFilePtr != NULL ){
		grammarFile.open( grammarFilePtr );
	}
	if( programFilePtr != NULL ){
		programFile.open( programFilePtr );
	}
	if( compiledFilePtr != NULL ){
		compiledFile.open( compiledFilePtr );
	}

	grammarAnalyzer = NULL;
	predictSetAnalyzer = NULL;
	parseTableGenerator = NULL;
	scanner = NULL;
	parser = NULL;
	compiler = NULL;

}

UniversalCompiler::~UniversalCompiler(){
	if( grammarAnalyzer != NULL )
		delete grammarAnalyzer;
	if( predictSetAnalyzer != NULL )
		delete predictSetAnalyzer;
	if( parseTableGenerator != NULL )
		delete parseTableGenerator;
	if( scanner != NULL )
		delete scanner;
	if( parser != NULL )
		delete parser;
	if( compiler != NULL )
		delete compiler;
}

void UniversalCompiler::greeting(){
	std::cout << "  Welcome to Robert Perlstein's Universal Compiler!\n"
		<< "This project was created under the guidance of Dr. Boris Stilman\n"
		<< "of the University of Colorado in Denver.\n\n"
		<< "A Universal Compiler takes a valid format of LL(1) BNF grammar.\n"
		<< "This grammar is then analyzed, and generating tables are created\n"
		<< "so that the program code can be scanned and compiled.\n\n"
		<< "Note to users! The grammar and program code can be passed as\n"
		<< "command line arguments, and should placed in the following order...\n"
		<< "universal_compiler.exe grammar.dat program.dat\n"
		<< "The user can also set these values during runtime.\n\n"
		<< "Please enjoy the program!";
}

void UniversalCompiler::initialize(){
	// Grammar file initialization.
	if( !grammarFile ){
		std::cout << "Please set the grammar file: ";
		std::string grammarFileName;
		std::cin >> grammarFileName;
		if( !setGrammarFile( grammarFileName )){
			while( true ){
				std:: cout << "\nInvalid grammar file. Enter 'Y' if you would like to try again, anything else cancels: ";
				char choice = ' ';
				if( choice == 'Y' || choice == 'y' ){
					std::cout << "Please set the grammar file: ";
					std::cin >> grammarFileName;
					if( setGrammarFile( grammarFileName ))
						break; 
				}
				else break;
			}
		}
	}
	// Program file inisitalization.
	if( !programFile ){
		std::cout << "Please set the program file: ";
		std::string programFileName;
		std::cin >> programFileName;
		if( !setProgramFile( programFileName )){
			while( true ){
				std:: cout << "\nInvalid program file. Enter 'Y' if you would like to try again, anything else cancels: ";
				char choice = ' ';
				if( choice == 'Y' || choice == 'y' ){
					std::cout << "Please set the program file: ";
					std::cin >> programFileName;
					if( setProgramFile( programFileName ))
						break; 
				}
				else break;
			}
		}
	}
}



bool UniversalCompiler::setGrammarFile( const std::string& grammarFileName ){
	if( grammarFile )
		grammarFile.close();
	grammarFile.open( grammarFileName );
	return ( grammarFile ) ? true : false;
}

bool UniversalCompiler::setProgramFile( const std::string& programFileName ){
	if( programFile )
		programFile.close();
	programFile.open( programFileName );
	return ( programFile ) ? true : false;
}

bool UniversalCompiler::setCompiledFile( const std::string& compiledFileName ){
	if( compiledFile )
		compiledFile.close();
	compiledFile.open( compiledFileName );
	return ( compiledFile ) ? true : false;
}

// Runs the menu, giving access to the various
// componenets of the UC.
// Returns false if the user chose to exit the menu.
bool UniversalCompiler::menu(){

	char choice;
	while( true ){
		std::cout << "\n\n >>>> UNIVERSAL COMPILER <<<<\n\n"
			<< " Grammar file set: " << ((grammarFile.is_open()) ? " TRUE\n" : "FALSE\n")
			<< " Program file set: " << ((programFile.is_open()) ? " TRUE\n" : "FALSE\n")
			<< " Compiled file set: " << ((compiledFile.is_open()) ? "TRUE\n\n" : "FALSE\n\n")
			<< " -------  Main Menu  -------\n\n"
			<< " 1 ... File Manager ( Set or view grammar and program files ).\n"
			<< " 2 ... Grammar Analyzer\n"
			<< " 3 ... Predict Set Analyzer\n"
			<< " 4 ... LL(1) Parse Table Generator\n"
			<< " 5 ... Scanner\n"
			<< " 6 ... Parser\n"
			<< " 7 ... Compiler\n"
			<< " 8 ... View Compiled Code (not working yet)\n"
			<< " 0 ... EXIT.\n\n"
			<< " Enter an value from the menu: ";
		std::cin >> choice;
		if( choice < '0'
			|| choice > '9' )
			continue;
		

		switch( choice )
		{
		case '1':
			while( runFileManager() );
			break;
		case '2':
			if( grammarFile.is_open() )
				runGrammarAnalyzer(true);
			else
				std::cout << "\n\nGrammar file not found. Cannot run Grammar Analyzer.";
			break;
		case '3':
			if( grammarFile.is_open() )
				runPredictSetAnalyzer(true);
			else
				std::cout << "\n\nGrammar file not found. Cannot run Predict Set Analyzer.";
			break;
		case '4':
			if( grammarFile.is_open() )
				runParseTableGenerator(true);
			else
				std::cout << "\n\nC Cannot run Parse Table Generator.";
			break;
		case '5':
			if( programFile.is_open() )
				runScanner();
			else
				std::cout << "\n\nProgram file not found. Cannot run Scanner.";
			break;
		case '6':
			if( grammarFile.is_open()
				&& programFile.is_open() )
				runParser(true);
			else
				std::cout << "\n\nProgram or grammar file not found. Cannot run Parser.";
			break;
		case '7':
			if( grammarFile.is_open()
				&& programFile.is_open() )
				runCompiler(true);
			else
				std::cout << "\n\nProgram or grammar file not found. Cannot run Compiler.";
			break;
		case '8':
			if( compiledFile.is_open() )
				printFileToCout( compiledFile );
			else
				std::cout << "\n\nCompiled file not found.";
			break;
		case '0':
			return false;
		} // END MAIN MENU
		std::cout << "\n\n_________________________________________________________";
		return true;
	}
}

bool UniversalCompiler::runFileManager(){
	char choice;
	while( true ){
		std::cout << "\n\n -------  File Manager  ------- \n\n"
			<< " 1 ... Set grammar file.\n"
			<< " 2 ... Set program file.\n"
			<< " 3 ... Set compiled output file.\n"
			<< " 4 ... View grammar file.\n"
			<< " 5 ... View program file.\n"
			<< " 0 ... Exit File Manager.\n\n"
			<< " Enter an value from the menu: ";
		std::cin >> choice;

		switch( choice ){
		case '1':
			{
				std::string grammarFileName;
				std::cout << "\n\nEnter filename for grammar: ";
				std::cin >> grammarFileName;
				if( !setGrammarFile( grammarFileName ))
					std::cout << "\n\nInvalid grammar file.";
				break;
			}
		case '2':
			{
				std::string programFileName;
				std::cout << "\n\nEnter filename for program: ";
				std::cin >> programFileName;
				if( !setProgramFile( programFileName ))
					std::cout << "\n\nInvalid program file.";
				break;
			}
		case '3':
			{
				std::string compiledFileName;
				std::cout << "\n\nEnter filename for compiled output: ";
				std::cin >> compiledFileName;
				if( !setCompiledFile( compiledFileName ))
					std::cout << "\n\nInvalid compiled file.";
				break;
			}
		case '4':
			{
				if( !grammarFile.is_open() ){
					std::cout << "\n\nGrammar file not found.";
					break;
				}
				else{
					printFileToCout( grammarFile );
					break;
				}
			}
		case '5':
			{
				if( !programFile.is_open() ){
					std::cout << "\n\nProgram file not found.";
					break;
				}
				else{
					printFileToCout( programFile );
					break;
				}
			}
		case '0':
			{
			return false;
			}
		}
	}
}

void UniversalCompiler::runGrammarAnalyzer( bool printOutput ){
	if( grammarAnalyzer != NULL )
		delete grammarAnalyzer;

	grammarAnalyzer = new GrammarAnalyzer( &grammarFile );
	grammarAnalyzer->analyzeGrammar();
	if( printOutput ) {
		std::cout << "\n\n ------- Grammar Analyzer -------\n\n";
		grammarAnalyzer->printInputGrammar();
		grammarAnalyzer->printProductions();
		grammarAnalyzer->printDataTables();
	}
}

void UniversalCompiler::runPredictSetAnalyzer( bool printOutput ){
	if( predictSetAnalyzer != NULL )
		delete predictSetAnalyzer;

	runGrammarAnalyzer( false );
	predictSetAnalyzer = new Predict( grammarAnalyzer->getGrammar() );
	try{
		predictSetAnalyzer->MarkLambda();
		predictSetAnalyzer->FillFirstSet();
		predictSetAnalyzer->FillFollowSet();
		predictSetAnalyzer->FillPredictSet();
		if( printOutput ){
			std::cout << "\n\n ------- Predict Set Analyzer -------\n\n";
			predictSetAnalyzer->PrintLookAheadSets();
		}
	} catch( IndexOutOfBounds e ){ 
		std::cout << "There was an error while running predict: " << e.what();
	} catch( ProductionNotFound e ){ 
		std::cout << "There was an error while running predict: " << e.what();
	}
}

void UniversalCompiler::runParseTableGenerator( bool printOutput ){
	if( parseTableGenerator != NULL )
		delete parseTableGenerator;

	runPredictSetAnalyzer( false );
	parseTableGenerator = new ParseTable( (*predictSetAnalyzer->getGrammar()) ); 
	parseTableGenerator->GenerateTable();
	if( printOutput ){
		std::cout << "\n\n ------- Transition Table Generator -------\n\n";
		parseTableGenerator->GetTableAsString();
	}
}

void UniversalCompiler::runScanner(){
	if( scanner != NULL )
		delete scanner;

	scanner = new Scanner( &programFile );
	std::cout << "\n\n ------- Scanner Driver -------\n\n";
	while( !scanner->isDoneScanning() 
		&& !scanner->hasError() ){
		Token token = scanner->scannerDriver();
		if( !scanner->hasError() ){
			std::cout << token.getTokenTypeString();
			if( token.getTokenValue().length() > 0 ) {
				std::cout << "( \"" << token.getTokenValue() << "\" )\n";
			} else {
				std::cout << "()\n";
			}
		}
	}
	scanner->close();
}

void UniversalCompiler::runParser( bool printOutput ){
	if( parser != NULL )
		delete parser;

	runParseTableGenerator( false );
	parser = new ParserDriver( (*predictSetAnalyzer->getGrammar()), parseTableGenerator );
	try{
		parser->LLDriver( programFile, printOutput );
	}
	catch( SyntaxError e ){
		std::cerr << "\n\n" << e.what();
	}
	catch( GrammarException e ){
		std::cerr << "\n\nGrammar exception caught: " << e.what();
	}
}

void UniversalCompiler::runCompiler( bool printOutput ){
	if( compiler != NULL )
		delete compiler;

	runPredictSetAnalyzer( false );
	runParseTableGenerator( false );
	compiler = new LL1Compiler( (*predictSetAnalyzer->getGrammar()), (*parseTableGenerator), programFile, compiledFile );
	compiler->RunLL1Compiler( printOutput );
}

void UniversalCompiler::printFileToCout( std::fstream& file ){
	std::string out;
	file.clear();
	file.seekg(0);
	while( !file.eof() ){
		getline(file, out);
		std::cout << "\n" << out;
	}
	std::cout << "\n";
}
