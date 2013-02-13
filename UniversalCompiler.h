#ifndef _universalCompiler
#define _universalCompiler

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Scanner.h"
#include "Token.h"
#include "Parser.h"
#include "GrammarAnalyzer.h"
#include "Predict.h"
#include "ParseTable.h"
#include "Parser.h"
#include "Compiler.h"

class UniversalCompiler {
public:

	UniversalCompiler(	const char* grammarFilePtr, 
						const char* programFilePtr, 
						const char* compiledFilePtr );
	
	void greeting();

	void initialize();

	bool setGrammarFile( const std::string& grammarFileName );
	bool setProgramFile( const std::string& programFileName );
	bool setCompiledFile( const std::string& compiledFileName );

	// Runs the menu, giving access to the various
	// componenets of the UC.
	// Returns false if the user chose to exit the menu.
	bool menu();

	~UniversalCompiler();

private:
	// Files
	std::fstream grammarFile;
	std::fstream programFile;
	std::fstream compiledFile;
	
	// Compile-time Objects
	GrammarAnalyzer* grammarAnalyzer;
	Predict* predictSetAnalyzer;
	ParseTable* parseTableGenerator;
	Scanner* scanner;
	ParserDriver* parser;
	LL1Compiler* compiler;
	
	

	// Main menu options
	bool runFileManager();
	void runGrammarAnalyzer( bool );
	void runPredictSetAnalyzer( bool );
	void runParseTableGenerator( bool );
	void runScanner();
	void runParser( bool );
	void runCompiler( bool );
	void printFileToCout( std::fstream& file );
};


#endif