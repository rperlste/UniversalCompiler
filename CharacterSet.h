#ifndef _characterSet
#define _characterSet

namespace CharacterSet {

	static enum CharacterSet {
		Letter,
		Digit,
		Blank,
		Plus,
		Minus,
		Equals,
		Colon,
		Comma,
		SemiColon,
		LParen,
		RParen,
		Underscore,
		Hash,
		Tab,
		EOL,
		Other
	};

	static CharacterSet getCharacterSetValue( const char& characterValue ){
		// Letter
		if(    ( characterValue >= 'a' && characterValue <= 'z' )
		    || ( characterValue >= 'A' && characterValue <= 'Z' ))
			return Letter;
		// Digit
		else if( characterValue >= '0' && characterValue <= '9' )
			return Digit;
		// Blank
		else if( characterValue == ' ' || characterValue == 32 )
			return Blank;
		// Plus
		else if( characterValue == '+' )
			return Plus;
		// Minus
		else if( characterValue == '-' )
			return Minus;
		// Equals
		else if( characterValue == '=' )
			return Equals;
		// Colon
		else if( characterValue == ':' )
			return Colon;
		// Comma
		else if( characterValue == ',' )
			return Comma;
		// Semicolon
		else if( characterValue == ';' )
			return SemiColon;
		// LParen
		else if( characterValue == '(' )
			return LParen;
		// RParen
		else if( characterValue == ')' )
			return RParen;
		// Underscore
		else if( characterValue == '_' )
			return Underscore;
		// Tab
		else if( characterValue == '\t' )
			return Tab;
		// EOL
		else if( characterValue == '\n' )
			return EOL;
		else
			return Other;
	}
}

#endif
