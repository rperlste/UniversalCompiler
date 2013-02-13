#include "ParseTable.h"

ParseTable::ParseTable( const Grammar& grammar ){
	this->grammar = grammar;
	this->table = NULL;
}

ParseTable::ParseTable( const ParseTable& parseTable ){
	grammar = (*parseTable.getGrammar());
	rowSize = grammar.nonterminalSet.size() + 1;
	colSize = grammar.terminalSet.size() + 1;
	table = new int*[rowSize];
	for( int i = 0; i < rowSize; i++ )
		table[i] = new int[colSize];
	for( int row = 0; row < rowSize; row++ ){
		for( int col = 0; col < colSize; col++ ){
			table[row][col] = parseTable.getTable()[row][col];
		}
	}
}

void ParseTable::GenerateTable(){

	// Initialize the table.
	if( table == NULL ){
		rowSize = grammar.nonterminalSet.size() + 1;
		colSize = grammar.terminalSet.size() + 1;
		table = new int*[rowSize];
		for( int i = 0; i < rowSize; i++ )
			table[i] = new int[colSize];
		for( int row = 0; row < rowSize; row++ ){
			for( int col = 0; col < colSize; col++ ){
				table[row][col] = 0;
			}
		}
	

		// Initialize predictKeys
		predictSize = grammar.predictSet.size();
		predictKeys = new std::string*[predictSize];

		// Initialize terminal and nonterminal keys
		nonterminalKeys = new const std::string*[rowSize] + 1;
		terminalKeys = new const std::string*[colSize];
		for( int i = 0; i < rowSize-1; i++ )
			nonterminalKeys[i] = &grammar.nonterminalSet.get( i );
		for( int i = 0; i < colSize-1; i++ )
			terminalKeys[i] = &grammar.terminalSet.get( i );

		// Iterate table and place transition values
		for( int row = 0; row < rowSize-1; row++ ){
			for( int col = 0; col < colSize-1; col++ ){
				//if( grammar.predictSet.getValueByIndex(row) == (*terminalKeys[col]) ){
				//	table[row][col] = row;
				//}
			}
		}
	}
}

void ParseTable::GetTableAsString(){
	//std::string tableStr;
	std::cout << "\n\n::: Transition Table :::\n\t";
	for( int i = 0; i < colSize-1; i++ )
		std::cout << "\t" + (*terminalKeys[i]);
	std::cout << "\tERROR";
	for( int row = 0; row < rowSize-1; row++ ){
		if( row < 10 )
			std::cout << "\n" << row << "  " + (*nonterminalKeys[row]);
		else
			std::cout << "\n" << row << " " + (*nonterminalKeys[row]);
		if( (*nonterminalKeys[row]).size() <= 12 )
			std::cout << "\t";
		for( int col = 0; col < colSize; col++ ){ 
			std::stringstream ss;
			ss <<  table[row][col];
			std::cout << "\t" << ss.str();
		}
	}
	std::cout << "\n13 ERROR";
}

Production ParseTable::getPredictProduction( Symbol LHS, Symbol RHS_Token ){
	Production production;
	int row = grammar.nonterminalSet.getIndex( LHS );
	int col = grammar.terminalSet.getIndex( RHS_Token );
	return grammar.productions.get(table[row][col]);
}

const Grammar* ParseTable::getGrammar() const{
	return &grammar;
}

int** ParseTable::getTable() const{
	return table;
}

ParseTable::~ParseTable(){
	for( int i = 0; i < rowSize; i++ )
		delete[] table[i];
	delete[] table;
}
