/*
 * Author:		Robbie Perlstein
 * Student ID:	101130094
 * Assignment:	Ad Hoc Compiler
 */

#ifndef _token
#define _token

#include <string>

enum TokenEnums {
		null,
		begin,
		end,
		read,
		write,
		id,
		intliteral,
		lparen,
		rparen,
		semicolon,
		colon,
		comma,
		assignop,
		equalop,
		plusop,
		minusop,
		multop,
		exponentialop,
		illegaltoken,
		temp,
		eofsym,
		actionsymbol };

static const char* tokenEnumsStrings[] = {
		"null",
		"begin",
		"end",
		"read",
		"write",
		"id",
		"intliteral",
		"lparen",
		"rparen",
		"semicolon",
		"colon",
		"comma",
		"assignop",
		"equalop",
		"plusop",
		"minusop",
		"multop",
		"exponentialop",
		"illegaltoken",
		"temp",
		"eofsym",
		"actionSymbol"
	};

static const char* tokenEnumsValues[] = {
		"",
		"begin",
		"end",
		"read",
		"write",
		"",
		"",
		"(",
		")",
		";",
		":",
		",",
		":=",
		"=",
		"+",
		"-",
		"*",
		"**",
		"",
		"",
		"$",
		""
	};

class Token {
public:
	typedef std::string Symbol;
    Token();
	Token( TokenEnums tokenType );
	Token( TokenEnums tokenType, Symbol );

	TokenEnums getTokenType();
	std::string getTokenTypeString();
    void setTokenType( TokenEnums tokenType );
    
    std::string getTokenValue();
    void setTokenValue( Symbol tokenValue);

	bool isTokenType( TokenEnums );

	bool operator == ( const Token &otherToken ) const;

	

private:

    TokenEnums tokenType;
    Symbol tokenValue;

};

namespace TokenKeywords{
	// KEYWORDS
    const std::string BEGIN = "begin";
    const std::string END = "end";
    const std::string READ = "read";
    const std::string WRITE = "write";
};






#endif
