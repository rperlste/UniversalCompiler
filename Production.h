#ifndef _Production
#define _Production

#include <string>
#include <algorithm>
#include "IndexedList.h"
#include "CompilerExceptions.h"

typedef std::string Symbol;

class RightHandSide : public IndexedList<Symbol>{};

class Production {
public:

	inline bool contains( const Symbol& value ) { return RHS.contains( value ); }

	inline void setLHS( const Symbol& LHS ) { this->LHS = LHS; }
	inline Symbol getLHS() const { return LHS; }

	inline void addRHSValue( const Symbol& symbol ) { RHS.push_back( symbol ); }
	inline void setRHS( const RightHandSide& RHS ) { this->RHS.set( RHS ); }
	inline RightHandSide getRHS() { return RHS; }
	inline RightHandSide getRHS() const { return RHS; }
	inline Symbol getRHSValueByIndex( const int& index ) const { return RHS[index]; }
	inline Symbol operator [] ( const int& index ) { return RHS[index]; }

	inline bool operator < ( const Production& production ) { return this->getLHS() < production.getLHS(); }
	inline const bool operator < ( const Production& production ) const { return this->getLHS() < production.getLHS(); }

	bool operator == ( const Production& production ) {
		if( LHS.compare( production.getLHS() ) != 0 ){
			return false;
		}
		else if( RHS.size() != production.RHS.size() ){
			return false;
		}
		else{
			for( int i = 0; i < RHS.size(); i++ ){
				if( RHS[i].compare( production.getRHSValueByIndex(i)) != 0 ){
					return false;
				}
			}
		}
		return true;
	}

	const bool operator == ( const Production& production ) const {
		if( LHS.compare( production.getLHS() ) != 0 ){
			return false;
		}
		else if( RHS.size() != production.RHS.size() ){
			return false;
		}
		else{
			for( int i = 0; i < RHS.size(); i++ ){
				if( RHS[i].compare( production.getRHSValueByIndex(i)) != 0 ){
					return false;
				}
			}
		}
		return true;
	}

private:
	Symbol LHS;
	RightHandSide RHS;
};

class Productions : public IndexedList<Production> {
public:

	void add( Production production ){
		if( size() > 0 ){
			for( std::list<Production>::iterator itProd = begin();
				itProd != end();
				itProd++ ){

				// Test to see if the left hand side is being repeated.
				// Behaves like a set
				if( !contains(production) ){
					push_back( production );
					return;
				}
			}
		}
		push_back( production );
	}



	Productions getProductionSubset( Symbol nonterminal ){
		Productions productionSubset;
		if( size() > 0 ){
			for( std::list<Production>::iterator itProd = begin();
				itProd != end();
				itProd++ ){

				// Test to see if the left hand side is being repeated.
				if( itProd->getLHS() == nonterminal ){
					productionSubset.push_back(*itProd);
				}
			}
		}
		if( productionSubset.size() == 0 )
			throw ProductionNotFound( nonterminal );

		return productionSubset;
	}



	int getUniqueProductionCount( Symbol nonterminal ){
		int count = 0;
		for( std::list<Production>::iterator it = begin();
			it != end();
			it++ ){
				if( (*it).getLHS() == nonterminal )
					count++;
		}
		return count;
	}


	int getProductionIndexFirstOf( Symbol nonterminal ){
		int index = 0;
		for( std::list<Production>::iterator itProd = begin();
				itProd != end();
				itProd++ ){

				// Test to see if the left hand side is being repeated.
				if( (*itProd).getLHS() == nonterminal ){
					return index;
				}
				index++;
		}
		throw ProductionNotFound( nonterminal );
	}

};

#endif