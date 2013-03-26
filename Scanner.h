#ifndef _scanner
#define _scanner


#include <fstream>
#include <iostream>
#include <string>
#include "Action.h"
#include "State.h"
#include "Token.h"
#include "TransitionTable.h"
#include "CharacterSet.h"

/*****************************************************
 *                   Scanner                         *
 *  The Scanner class reads a file and is used to    *
 *  extract Tokens within that file, and report any  *
 *  errors it has detected, such as illegal grammar. *
 *****************************************************/
class Scanner{

public:

	Scanner( std::fstream* );

	Token             scannerDriver();
	Token             scan();
	Token             peekNextToken();
	Token             getPreviousToken();
	int               getScannerFilePosition() const;
	std::fstream*     getProgramFile() const;
	bool              isDoneScanning();
	bool              hasError();
	void              close();

private:

	char              getCurrentChar();
	char              peekNextChar();
	void              consumeChar();
	Action::Action    getAction( State::State, char );
	State::State      getNextState( State::State, char );
	TokenEnums        lookupCode( State::State, char );
	void              checkExceptions( Token& );
	void              LexicalError( std::string );

	int               filePosition;
	bool              errorDetected;
	bool              isClosed;
	Token*            tokenBuffer;
	Token             currentToken;
	Token             previousToken;
	char*             charBuffer;
	std::fstream*     programFile;
};

#endif
