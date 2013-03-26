#ifndef _analyzer
#define _analyzer

#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <list>
#include <utility>
#include "Grammar.h"

class GrammarAnalyzer {
public:
	GrammarAnalyzer( std::fstream* grammarFile );

	void analyzeGrammar();

	Grammar getGrammar();

	void printInputGrammar();

	void printProductions();

	void printDataTables();

	void analyzeError( std::string error );

private:
	std::fstream*      grammarFile;
	bool               error;
	Grammar            grammar;
};

#endif
