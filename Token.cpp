/*
 * Author:		Robbie Perlstein
 * Student ID:	101130094
 * Assignment:	Ad Hoc Compiler
 */

#include "Token.h"


Token::Token(){}

Token::Token( TokenEnums tokenType ){
	this->tokenType = tokenType;
	this->tokenValue = tokenEnumsValues[ tokenType ];
}

Token::Token( TokenEnums tokenType, std::string tokenValue ){
	this->tokenType = tokenType;
	this->tokenValue = tokenValue;
}


void Token::setTokenType( TokenEnums tokenType ){
	this->tokenType = tokenType;
}

TokenEnums Token::getTokenType(){
	return tokenType;
}

std::string Token::getTokenTypeString(){
	return tokenEnumsStrings[ tokenType ];
}

std::string Token::getTokenValue() {
	return tokenValue;
}

void Token::setTokenValue(std::string tokenValue) {
	this->tokenValue = tokenValue;
}

bool Token::isTokenType( TokenEnums tokenEnum ){
	if( this->tokenType == tokenEnum )
		return true;
	else
		return false;
}

bool Token::operator== ( const Token &other) const{
	if( this->tokenType == other.tokenType
		&& this->tokenValue == other.tokenValue )
		return true;
	else
		return false;
}

	

