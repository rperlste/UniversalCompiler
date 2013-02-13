#include "Compiler.h"

LL1Compiler::LL1Compiler( const Grammar& grammar, ParseTable& parseTable, std::fstream& programFile, std::fstream& compiledFile ){
	this->grammar = grammar;
	this->parseTable = &parseTable;
	lastSymbolIndex = 0;
	scanner = new Scanner( &programFile );
	this->compiledOutputFile = &compiledFile;
}

LL1Compiler::~LL1Compiler(){
	delete scanner;
	closeCompiledOutputFile();
}

void LL1Compiler::RunLL1Compiler( bool printOutput ){
	leftIndex = 0;
	rightIndex = 0; 
	topIndex = 2; 
	currentIndex = 1;

	initializeCompiledOutputFile();

	parseStack.push( grammar.getStartSymbol() );
	semanticStack.push( grammar.getStartSymbol() );

	while( !parseStack.empty() ){
		StackObject topSymbol = parseStack.top();
		Token currentInputToken = scanner->scan();

		// if X in nonterminals
		if( topSymbol.type == SymbolEnum
			&& grammar.nonterminalSet.contains( topSymbol.symbol ) ){
			try{ 
				// T(X, a) = X —> Y1Y2. . . Ym
				Production predictProduction = parseTable->getPredictProduction( topSymbol.symbol, currentInputToken.getTokenValue() );
				parseStack.pop();
				parseStack.push( EndOfProduction( leftIndex, rightIndex, currentIndex, topIndex));

				// Push YmYm-1. . .Y1 on the parse stack
				// Push YmYm-1. . .Y1 - ActionSymbol on the semantic stack
				int nonActionSymCount = 0;
				for( int i = 0; i < predictProduction.getRHS().size(); i++ ){ 
					parseStack.push( predictProduction[i] );
					if( !predictProduction[i].empty()
						&& predictProduction[i][0] != '#' ){
						semanticStack.push( predictProduction[i] );
						nonActionSymCount ++;
					}
				}
				leftIndex = currentIndex;
				rightIndex = topIndex;
				currentIndex = rightIndex;
				topIndex += nonActionSymCount;
			} catch (ProductionNotFound e){
				//SyntaxError();
			}
		}
		else if (topSymbol.type == SymbolEnum
			&& grammar.terminalSet.contains( topSymbol.symbol ) ){
			if( topSymbol.symbol == currentInputToken.getTokenValue() ){
				//Place token info from scanner in semantic symbol
				semanticStack.push(currentInputToken.getTokenValue());
				parseStack.pop();
				currentInputToken = scanner->scan();
				currentIndex ++;
			} else {
				//SyntaxError();
			}
		}
		else if( topSymbol.type == EOPEnum ){
			leftIndex = topSymbol.EOP.leftIndex;
			rightIndex = topSymbol.EOP.rightIndex;
			topIndex = topSymbol.EOP.topIndex;
			currentIndex = topSymbol.EOP.currentIndex + 1;
			parseStack.pop();
		}

		else{ // topSymbol == ACTION_SYMBOL
			parseStack.pop();
			// Call Routine for action symbol
		}
	}
}

void LL1Compiler::initializeCompiledOutputFile(){
	compiledOutputFile->clear();
	compiledOutputFile->flush();
	compiledOutputFile->seekg(0);
}

void LL1Compiler::closeCompiledOutputFile(){
	compiledOutputFile = NULL;
}

void LL1Compiler::Generate( char* outputData, ... ){
	va_list vl;
	va_start(vl, outputData );
	char* currentData = outputData;
	do{ 
		(*compiledOutputFile) << currentData ;
		currentData = va_arg(vl, char*);
	} while( currentData != NULL );
	(*compiledOutputFile) << "\n";
	va_end(vl);
}

std::string LL1Compiler::GetTemp(){
	maxTempIndex ++;
	std::string tempName = "Temp&" + maxTempIndex;
	CheckId( tempName );
	return tempName;
}

bool LL1Compiler::LookUp( Symbol symbol ){
	for( int i = 0; i < lastSymbolIndex; i++ ){
		if( symbolTable[i] == symbol )
			return true;
	}
}

void LL1Compiler::Enter( Symbol symbol ){
	if( lastSymbolIndex < MAX_SYMBOL ){
		symbolTable[lastSymbolIndex] = symbol;
		lastSymbolIndex ++;
	}
	else{
		throw SymbolTableOverflow( "Symbol table overflow: " + symbol );
	}
}
void LL1Compiler::CheckId( Symbol symbol ){
	if( !LookUp( symbol )){
		Enter( symbol );
		Generate( "Declare", &symbol[0], "Integer" );
	}
}

std::string LL1Compiler::Extract( SemanticRecord semanticRecord ){
	switch( semanticRecord.recordKind ){
	case OpRec:
		return OperatorEnumArr[ semanticRecord.opRecord.opType ];
	case ExprRec:
		return semanticRecord.exprRecord.value;
	case Error:
		throw SemanticError( "SemanticError" );
	}
}

void LL1Compiler::Start(){
	maxTempIndex = 0;
}

void LL1Compiler::Finish(){
	Generate( "Halt" );
}

void LL1Compiler::Assign( SemanticRecord target, SemanticRecord source ){
	Generate( "Store", Extract(source), target.exprRecord.value );
}

void LL1Compiler::ReadId( SemanticRecord inRecord ){
	Generate( "Read", inRecord.exprRecord.name, "Integer" );
}

void LL1Compiler::WriteExpr( SemanticRecord outRecord ){
	Generate( "Write", Extract(outRecord), "Integer" );
}
SemanticRecord LL1Compiler::GenInfix( SemanticRecord e1, 
						SemanticRecord op,
						SemanticRecord e2 ){
	SemanticRecord eRec( ExprRec );
	eRec.exprRecord.exprKind = TempExpr;
	eRec.exprRecord.name = GetTemp();
	Generate( &Extract(e1)[0], &Extract(e2)[0], &eRec.exprRecord.name[0] );
	return eRec;
}
SemanticRecord LL1Compiler::ProccessId(){
	CheckId( Extract( semanticStack[currentIndex-1].semanticRecord ));
	SemanticRecord eRec( ExprRec );
	eRec.exprRecord.exprKind = IdExpr;
	eRec.exprRecord.name = Extract( semanticStack[currentIndex-1].semanticRecord );
	return eRec;
}
SemanticRecord LL1Compiler::ProcessLiteral(){
	SemanticRecord eRec( ExprRec );
	eRec.exprRecord.exprKind = LiteralExpr;
	eRec.exprRecord.value = Extract( semanticStack[currentIndex-1].semanticRecord );
	return eRec;
}
SemanticRecord LL1Compiler::ProcessOperator(){
	SemanticRecord eRec( OpRec );
	if( scanner->getPreviousToken().getTokenType() == plusop ){
		eRec.opRecord.opType = PlusOp;
	}
	else{
		eRec.opRecord.opType = MinusOp;
	}
	return eRec;
}