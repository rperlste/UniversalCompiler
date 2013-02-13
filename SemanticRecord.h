#ifndef _SemanticRecord
#define _SemanticRecord


const std::string OperatorEnumArr[2] = { "PlusOp", "MinusOp" };
enum Operator {
	PlusOp,
	MinusOp
};
struct OpType {
	OpType(){}
	OpType( Operator opType ){
		this->opType = opType;
	}
	Operator opType;
};


enum ExprKind {
	IdExpr,
	LiteralExpr,
	TempExpr
};
struct ExprType {
	ExprType(){}
	ExprType( ExprKind exprKind ){
		this->exprKind = exprKind;
	}
	std::string value, name;
	ExprKind exprKind;
};


enum SemanticRecordKind{
	OpRec,
	ExprRec,
	Error
};
struct SemanticRecord {
	SemanticRecord(){}
	SemanticRecord( SemanticRecordKind recordKind ){
		this->recordKind = recordKind;
	}

	OpType opRecord;
	ExprType exprRecord;
	SemanticRecordKind recordKind;
};


#endif