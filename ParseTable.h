#ifndef _ParseTable
#define _ParseTable

#include "Grammar.h"
#include <string>
#include <iostream>
#include <sstream>

class ParseTable{
public:
	ParseTable();
	ParseTable(         const Grammar& grammar );
	ParseTable(         const ParseTable& );
	~ParseTable();
	void                GenerateTable();
	void                GetTableAsString();
	Production          getPredictProduction( Symbol, Symbol );
	const Grammar*      getGrammar() const;
	int**               getTable() const;
private:
	Grammar             grammar;
	int                 rowSize;
	int                 colSize;
	int                 predictSize;
	std::string**       predictKeys;
	const std::string** nonterminalKeys;
	const std::string** terminalKeys;
	int**               table;
};

#endif
