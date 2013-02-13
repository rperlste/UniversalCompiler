#ifndef _CompilerExceptions
#define _CompilerExceptions

#include <string>
#include <exception>

class ProductionNotFound : public std::exception {
public:
	ProductionNotFound( std::string valueNotFound ){
		this->valueNotFound = valueNotFound;
	}
	virtual const char* what() throw(){
		std::string what = "Production \"" + valueNotFound + "\" was not found.";
		return what.c_str();
	}
private:
	std::string valueNotFound;
};

class SymbolNotFound : public std::exception {
public:
	SymbolNotFound( std::string valueNotFound ){
		this->valueNotFound = valueNotFound;
	}
	virtual const char* what() throw(){
		std::string what = "Symbol \"" + valueNotFound + "\" was not found.";
		return what.c_str();
	}
private:
	std::string valueNotFound;
};

/*
class IndexOutOfBounds : public std::exception {
public:
	virtual const char* what() throw(){ 
		return "Index is out of bounds.";
	}
};
*/

class GrammarException : public std::exception {
public:
	GrammarException( std::string reason ){
		this->reason = reason;
	}
	virtual const char* what() throw(){
		return reason.c_str();
	}
private:
	std::string reason;
};

class SyntaxError : public std::exception {
public:
	SyntaxError( std::string error ){
		this->error = error;
	}
	virtual const char* what() throw(){
		return error.c_str();
	}
private:
	std::string error;
};


class SemanticError : public std::exception {
public:
	SemanticError( std::string error ){
		this->error = error;
	}
	virtual const char* what() throw(){
		return error.c_str();
	}
private:
	std::string error;
};

class SymbolTableOverflow : public std::exception {
public:
	SymbolTableOverflow( std::string error ){
		this->error = error;
	}
	virtual const char* what() throw(){
		return error.c_str();
	}
private:
	std::string error;
};

#endif