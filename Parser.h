#ifndef _ParserDriver
#define _ParserDriver

#include <stack>

#include <string>
#include "Grammar.h"
#include "ParseTable.h"
#include "Token.h"
#include "Scanner.h"

class ParserDriver{
public:
	ParserDriver( const Grammar& grammar, 
	              ParseTable* parseTable );
	~ParserDriver();
	
	void          LLDriver( std::fstream& programFile, 
	                        bool printOutput );
	bool          isStackEmpty();

private:
	Grammar                    grammar;
	ParseTable*                parseTable;
	std::stack <std::string>   parseStack;
};

#endif
