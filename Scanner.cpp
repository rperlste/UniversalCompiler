#include "Scanner.h"


Scanner::Scanner( std::fstream* programFile ){
	this->programFile = programFile;
	programFile->clear();
	programFile->seekg(0);
	errorDetected = false;
	isClosed = false;
	tokenBuffer = NULL;
	charBuffer = NULL;
	filePosition = 0;
	currentToken = null;
}

Token Scanner::scannerDriver(){
	if( tokenBuffer != NULL ){
		Token tokenReturn = *tokenBuffer;
		delete tokenBuffer;
		tokenBuffer = NULL;
		return tokenReturn;
	}

	State::State currentState = State::initialstate;
	char currentChar = getCurrentChar();
	std::string tokenValue = "";

	while( !isDoneScanning()
		&&  static_cast<int>(currentState) < 11 ){

		currentState = getNextState( currentState, currentChar );
		if( currentState == State::error ){
			tokenValue += currentChar;
			LexicalError( tokenValue );
			Token token( illegaltoken );
			return( token );
		}
		else if( currentState == State::blank
			|| currentState == State::emptyspace ){

			currentState = State::initialstate;
			consumeChar();
			currentChar = getCurrentChar();
		}
		else if( currentState == State::comment ){

			consumeChar();
			currentChar = getCurrentChar();
		}
		else if( currentState == State::commentend ){

			consumeChar();
			currentChar = getCurrentChar();
			currentState = State::initialstate;
		}
		else if( static_cast<int>(currentState) > 12 ){
			tokenValue += currentChar;
			consumeChar();
		}
		else if( static_cast<int>(currentState) < State::FINAL_STATE_INDEX ){
			// Move append
			tokenValue += currentChar;
			consumeChar();
			currentChar = getCurrentChar();
		}
	}
	if( static_cast<int>(currentState) < 11 ){
		currentState = getNextState( currentState, ' ' );
	}
	if( static_cast<int>(currentState) >= 11 ){
		switch( currentState ){
			case State::id:{
				Token token( id, tokenValue );
				checkExceptions( token );
				return token;
			}
			case State::intliteral:{
				Token token( intliteral, tokenValue );
				return token;
			}
			case State::plusop:{
				Token token( plusop );
				return token;
			}
			case State::assignop:{
				Token token( assignop );
				return token;
			}
			case State::comma:{
				Token token( comma );
				return token;
			}
			case State::semicolon:{
				Token token( semicolon );
				return token;
			}
			case State::lparen:{
				Token token( lparen );
				return token;
			}
			case State::rparen:{
				Token token( rparen );
				return token;
			}
			case State::minusop:{
				Token token( minusop );
				return token;
			}
		}
	}
	else{
		LexicalError( tokenValue );
	}
}

Token Scanner::scan(){
	if( tokenBuffer != NULL ){
		Token tokenReturn = *tokenBuffer;
		delete tokenBuffer;
		tokenBuffer = NULL;
		return tokenReturn;
	}

		
	State::State currentState = State::initialstate;
	char currentChar;
	std::string tokenValue = "";

	while( !isDoneScanning() ){
		currentChar = getCurrentChar();
		Action::Action currentAction = getAction( currentState, currentChar );

		switch( currentAction ) {
			case Action::Error:{
				errorDetected = true;
				LexicalError( tokenValue );
				break;
			}
			case Action::MoveAppend:{
				currentState = getNextState( currentState, currentChar );
				tokenValue += currentChar;
				consumeChar();
				break;
			}
			case Action::MoveNoAppend:{
				currentState = getNextState( currentState, currentChar );
				consumeChar();
				break;
			}
			case Action::HaltAppend:{
				tokenValue += currentChar;
				consumeChar();
				Token scannedToken( lookupCode( currentState, currentChar ), tokenValue );
				checkExceptions( scannedToken );
				
				if( scannedToken.isTokenType( null ) ){
					return scan();
				} else {
					previousToken = currentToken;
					currentToken = scannedToken;
					return scannedToken;
				}
			}
			case Action::HaltNoAppend:{
				consumeChar();
				Token scannedToken( lookupCode( currentState, currentChar ), tokenValue );
				checkExceptions( scannedToken );
				
				if( scannedToken.isTokenType( null ) ){
					return scan();
				} else {
					previousToken = currentToken;
					currentToken = scannedToken;
					return scannedToken;
				}
			}
			case Action::HaltReuse:{
				Token scannedToken( lookupCode( currentState, currentChar ));
				checkExceptions( scannedToken );
				if( scannedToken.isTokenType( null ) ){
					return scan();
				} else {
					previousToken = currentToken;
					currentToken = scannedToken;
					return scannedToken;
				}
			}
		}
	}
}

Token Scanner::peekNextToken(){
	if( isDoneScanning() ){
		Token eofToken( eofsym );
		return eofToken;
	}
	else if( hasError() ){
		Token illegalToken( illegaltoken );
		return illegalToken;
	}
	else if( tokenBuffer != NULL ) {
		return *tokenBuffer;
	} 
	else {
		tokenBuffer = new Token;
		*tokenBuffer = scan();
		return *tokenBuffer;
	}
}

bool Scanner::isDoneScanning(){
	if( programFile->eof()
		|| isClosed )
		return true;
	else
		return false;
}

bool Scanner::hasError(){
	if( errorDetected )
		return true;
	else
		return false;
}

char Scanner::getCurrentChar(){
	if( charBuffer != NULL )
		return *charBuffer;
	else {
		charBuffer = new char;
		if( isDoneScanning() ){
			*charBuffer = 'EOF';
		} else {
			*charBuffer = this->programFile->get();
			return *charBuffer;
		}
	}
}

char Scanner::peekNextChar(){
	return this->programFile->peek();
}

void Scanner::consumeChar(){
	if( charBuffer != NULL ){
		delete charBuffer;
		charBuffer = NULL;
		filePosition = programFile->tellg();
	}
}

State::State Scanner::getNextState( State::State currentState, char currentChar ){
	if( static_cast<int>(currentState) >= State::FINAL_STATE_INDEX )
		return currentState;
	return static_cast<State::State>( 
		TRANSITION_TABLE[currentState][ CharacterSet::getCharacterSetValue( currentChar ) ]);
}

Action::Action Scanner::getAction( State::State currentState, char currentChar ){
	// Error
	if( currentState == State::error ){
		return Action::Error;
	// programFileal state
	} else if( static_cast<int>(currentState) >  10 ){
		return Action::HaltNoAppend;
	// Not programFileal state
	} else {
		if( currentState == State::comment
			|| currentState == State::blank
			|| currentChar == ' ' )
			return Action::MoveNoAppend;
		else
			return Action::MoveAppend;
	}
	
	
} 

TokenEnums Scanner::lookupCode( State::State currentState, char currentChar ){
	switch( currentState){
		case State::id:
			return id;
		case State::intliteral:
			return intliteral;
		case State::emptyspace:
			return null;
		case State::plusop:
			return plusop;
		case State::commentend:
			return null;
		case State::assignop:
			return assignop;
		case State::comma:
			return comma;
		case State::semicolon:
			return semicolon;
		case State::lparen:
			return lparen;
		case State::rparen:
			return rparen;
		case State::minusop:
			return minusop;
		case State::actionsymbol:
			return actionsymbol;
	}
	// Else an error has occured somewhere.
	return illegaltoken;
}

bool caseInsensitiveStringCompare(std::string str1,std::string str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (std::string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2)) {
            return false;
        }
    }
    return true;
}

void Scanner::checkExceptions( Token& scannedToken ){
	// BEGIN
	if( caseInsensitiveStringCompare(scannedToken.getTokenValue(), TokenKeywords::BEGIN) ){
		scannedToken = Token( begin );
		return;
	
	// END
	} else if( caseInsensitiveStringCompare(scannedToken.getTokenValue(), TokenKeywords::END) ){
		scannedToken = Token( end );
		return;

	// READ
	} else if( caseInsensitiveStringCompare(scannedToken.getTokenValue(), TokenKeywords::READ) ){
		scannedToken = Token( read );
		return;

	// WRITE
	} else if( caseInsensitiveStringCompare(scannedToken.getTokenValue(), TokenKeywords::WRITE) ){
		scannedToken = Token( write );
		return;
	}

	// No keyword found.
	return;
}

void Scanner::LexicalError( std::string errorValue){
	errorDetected = true;
	std::cerr << "\nLexicalError: " << errorValue << "\n";
	return;
}

void Scanner::close(){
	delete charBuffer;
	delete tokenBuffer;
	isClosed = true;
}

int Scanner::getScannerFilePosition() const {
	return filePosition;
}

std::fstream* Scanner::getProgramFile() const{
	return programFile;
}


Token Scanner::getPreviousToken(){
	return previousToken;
}
