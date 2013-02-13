#ifndef _ActionSymbols
#define _ActionSymbols

enum ActionSymbol{
	Start,
	Assign,
	ReadId,
	WriteExpr,
	GenInfix,
	ProcessLiteral,
	ProcessOp,
	ProcessId,
	Copy
};
/*
namespace ActionSymbols{

	void Start();
	void Assign( $1, $2 );
	void ReadId( $1);
	void WriteExpr( $1 );
	void GenInfix( $$, $1, $2, $$ );
	void ProcessLiteral();
	void ProcessOp();
	void ProcessId();
	void Copy( $x, $y );
}
*/

#endif