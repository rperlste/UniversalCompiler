#ifndef _CompilerStackObject
#define _CompilerStackObject

#include <string>
#include <stack>
#include "ActionSymbols.h"
#include "EndOfProduction.h"
#include "Production.h"
#include "SemanticRecord.h"

typedef std::string Symbol;

enum StackObjectType {
	ActionSymbolEnum,
	SymbolEnum,
	EOPEnum,
	SemanticRecordEnum
};

struct StackObject{

	StackObject(){}

	StackObject( ActionSymbols::ActionSymbol actionSymbol ){
		this->actionSymbol = actionSymbol;
		type = ActionSymbolEnum;
	}

	StackObject( Symbol symbol ){
		this->symbol = symbol;
		if( !symbol.empty() && symbol[0] == '#' ){
			type = ActionSymbolEnum;
		} else {
			type = SymbolEnum;
		}
	}

	StackObject( EndOfProduction EOP ){
		this->EOP = EOP;
		type = EOPEnum;
	}

	StackObject( SemanticRecord semanticRecord ){
		this->semanticRecord = semanticRecord;
		type = SemanticRecordEnum;
	}

	ActionSymbols::ActionSymbol actionSymbol;
	Symbol symbol;
	EndOfProduction EOP;
	SemanticRecord semanticRecord;
	StackObjectType type;
};



#endif