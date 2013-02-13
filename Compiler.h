#ifndef _LL1Compiler
#define _LL1Compiler

#include "Grammar.h"
#include "SemanticRecord.h"
#include "ParseTable.h"
#include "Scanner.h"
#include "EndOfProduction.h"
#include "CompilerStack.h"
#include "CompilerExceptions.h"

#include <stdio.h>
#include <stdarg.h>

class LL1Compiler{
public:
	// LL1 Compiler
	LL1Compiler( const Grammar& grammar, ParseTable& parseTable, std::fstream& programFile, std::fstream& compiledFile );
	void RunLL1Compiler( bool printOutput );
	~LL1Compiler();

	// Compiled output routines
	void initializeCompiledOutputFile();
	void Generate( char* outputData, ... );
	void closeCompiledOutputFile();

	// Auxillary routines
	std::string Extract( SemanticRecord semanticRecord );
	std::string GetTemp();
	bool LookUp( Symbol symbol );
	void Enter( Symbol symbol );
	void CheckId( Symbol s );

	// Semantic routines
	void Start();
	void Finish();
	void Assign( SemanticRecord target, SemanticRecord source );
	void ReadId( SemanticRecord inRecord );
	void WriteExpr( SemanticRecord outRecord );
	SemanticRecord GenInfix( SemanticRecord expression1, 
							SemanticRecord oprand,
							SemanticRecord expression2 );
	SemanticRecord ProccessId();
	SemanticRecord ProcessLiteral();
	SemanticRecord ProcessOperator();


private:
	// CONSTANTS
	const static unsigned MAX_SYMBOL = 1000;

	// VARIABLES
	Symbol symbolTable[MAX_SYMBOL];
	unsigned lastSymbolIndex;
	unsigned maxTempIndex;
	unsigned leftIndex;
	unsigned rightIndex; 
	unsigned topIndex; 
	unsigned currentIndex;

	// DATA_STRUCTURES AND OBJECTS
	Scanner* scanner;
	Grammar grammar;
	ParseTable* parseTable;
	CompilerStack parseStack;
	CompilerStack semanticStack;
	std::fstream* compiledOutputFile;
};

#endif