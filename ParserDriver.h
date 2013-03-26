#ifndef _ParserDriver
#define _ParserDriver

#include <stack>

#include <string>
#include "Grammar.h"
#include "ParseTable.h"
#include "Token.h"
#include "Scanner.h"

class ParserDriver {
public:
	ParserDriver(         const Grammar& );
	void parse(           std::fstream&, bool );

private:
	Grammar               grammar;
	ParseTable*           parseTable;
	IndexedList <Symbol>  parseStack;
};

#endif
