#include "GrammarSet.h"



// Return true if change occurred, false if none occurred
bool GrammarSet::add( const Symbol& grammar ){
	return grammarSet.insert( grammar ).second;
}

// Return true if change occurred, false if none occurred
bool GrammarSet::add( GrammarSet grammarSetIn ){
	bool changes = false;
	for( int i = 0; i < grammarSetIn.size(); i++ ){
		if( this->grammarSet.insert( (*grammarSetIn[i]) ).second )
			changes = true;
	}
	return changes;
}

// Return true if change occurred, false if none occurred
bool GrammarSet::remove( const Symbol& grammar ){
	if( grammarSet.find( grammar ) != grammarSet.end() ){
		grammarSet.erase( grammarSet.find( grammar ) );
		return true;
	}
	else
		return false;
}



std::set<Symbol>* GrammarSet::getGrammarSet(){
	return &grammarSet;
}

const int GrammarSet::size(){
	return grammarSet.size();
}

bool GrammarSet::contains( const Symbol& grammar ){
	if( grammarSet.find( grammar ) != grammarSet.end() )
		return true;
	else
		return false;
}

const int GrammarSet::getIndex( const Symbol& symbol ){
	int index = 0;
	for( std::set<Symbol>::iterator it = grammarSet.begin();
		it != grammarSet.end();
		it++ ){
		if( (*it) == symbol )
			return index;
		index++;
	}
	throw GrammarException( "Value not found => " + symbol ); 
}

const Symbol* GrammarSet::getSymbol( const int& index ){
	if( index >= size() )
		throw IndexOutOfBounds();
	else{
		int count = 0;
		for( std::set<Symbol>::iterator itSet = grammarSet.begin();
			itSet != grammarSet.end();
			itSet++ ){
				if( count == index )
					return &(*itSet);
				count++;
		}
	}
}

const Symbol* GrammarSet::operator [] ( const int& index ){
	return getSymbol( index );
}


