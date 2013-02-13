#ifndef _CompilerStack
#define _CompilerStack

#include <string>
#include <stack>
#include "ActionSymbols.h"
#include "EndOfProduction.h"
#include "Production.h"

typedef std::string Symbol;

enum StackObjectType {
	ActionSymbolEnum,
	SymbolEnum,
	EOPEnum,
	SemanticrecordEnum
};

struct StackObject{

	StackObject(){}

	StackObject( ActionSymbol actionSymbol ){
		this->actionSymbol = actionSymbol;
		type = ActionSymbolEnum;
	}

	StackObject( Symbol symbol ){
		this->symbol = symbol;
		type = SymbolEnum;
	}

	StackObject( EndOfProduction EOP ){
		this->EOP = EOP;
		type = EOPEnum;
	}

	ActionSymbol actionSymbol;
	Symbol symbol;
	EndOfProduction EOP;
	SemanticRecord semanticRecord;
	StackObjectType type;
};



class CompilerStack{
public:

	void push( Production production ){
		for( int i = 0; i < production.getRHS().size(); i ++ ){
			cStack.push_back( production[0] );
		}
	}

	void push( Symbol symbol ){
		cStack.push_back( StackObject(symbol) );
	}

	void push( ActionSymbol actionSymbol ){
		cStack.push_back( StackObject(actionSymbol) );
	}

	void push( EndOfProduction EOP ){
		cStack.push_back( StackObject(EOP));
	}

	void push( StackObject stackObject ){
		cStack.push_back( stackObject );
	}

	void pop(){
		cStack.pop_back();
	}

	StackObject top(){
		return cStack.back();
	}

	int size(){
		return cStack.size();
	}

	bool empty(){
		return cStack.empty();
	}

	StackObject operator [] ( const int& index ){
		if( index >= cStack.size() ){
			throw IndexOutOfBounds();
		}
		int offset = 0;
		for( std::list<StackObject>::iterator it = cStack.end();
			it != cStack.begin();
			it -- ){
				if( offset == index )
					return (*it);
				offset ++;
		}
	}

private:
	std::list<StackObject> cStack;

};



#endif