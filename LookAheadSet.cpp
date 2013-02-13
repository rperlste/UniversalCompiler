#include "LookAheadSet.h"

// Return true if change occurred, false if none occurred
bool LookAheadSet::add( const Symbol& key, const Symbol& grammar ){
	if( lookAheadSet.find( key ) == lookAheadSet.end() ){
		return lookAheadSet[ key ].add( grammar );
	} else {
		GrammarSet grammarSet;
		grammarSet.add( grammar );
		lookAheadSet[ key ] = grammarSet;
		return true;
	}
}

// Return true if change occurred, false if none occurred
bool LookAheadSet::add( const Symbol& key, const GrammarSet& grammarSet ){
	bool changes = false;
	if( lookAheadSet.find( key ) != lookAheadSet.end() ){
		if( lookAheadSet[ key ].add( grammarSet ) )
			changes = true;
	} else {
		lookAheadSet[ key ] = grammarSet;
		return true;
	}
	return changes;
}

bool LookAheadSet::add( std::list<Production> productions ){
	bool changes = false;
	for( std::list<Production>::iterator it = productions.begin();
		it != productions.end();
		it++ ){
			for( int i = 0; i < (*it).RHSsize(); i++ ){
				if( add( (*it).getLHS(), (*it->getRHS()->getSymbol(i)) ))
					changes = true;
			}
	}
	return changes;
}

// Return true if change occurred, false if none occurred
bool LookAheadSet::add( const Symbol& key ){
	if( lookAheadSet.find( key ) == lookAheadSet.end() ){
		GrammarSet grammarSet;
		lookAheadSet[ key ] = grammarSet;
		return true;
	}
	else
		return false;
}

// Return a Symbol representation of the set
Symbol LookAheadSet::getSetAsString(const int& index){
	return (*getKey( index )) + " = " + getGrammarSet(index)->getSetAsString() + "\n";
}

Symbol LookAheadSet::getSetAsString( const Symbol& key ){
	return key + " = " + getGrammarSet(key)->getSetAsString() + "\n";
}

bool LookAheadSet::contains( const Symbol& key, const Symbol& grammar ){
	std::map< Symbol, GrammarSet >::iterator it = lookAheadSet.find( key );
	if( it != lookAheadSet.end() )
		return (*it).second.contains( grammar );
}

bool LookAheadSet::contains( const int& index, const Symbol& grammar ){
	return getGrammarSet( index)->contains(grammar);
}

void LookAheadSet::remove( const Symbol& key, const Symbol& grammar ){
	if( lookAheadSet.find( key ) != lookAheadSet.end() )
		lookAheadSet.find( key )->second.remove( grammar );
}

std::map<Symbol, GrammarSet> LookAheadSet::getLookAheadSet(){
	return lookAheadSet;
}

const int LookAheadSet::size(){
	return lookAheadSet.size();
}

int LookAheadSet::getIndexOfKey( const Symbol& key ){
	int count = 0;
	for( std::map< Symbol, GrammarSet >::iterator it = lookAheadSet.begin();
		it != lookAheadSet.end();
		it++ ){
			if( (*it).first == key )
				return count;
			count++;
	}
	throw ProductionNotFound( key );
}

const Symbol* LookAheadSet::getKey( const int& index ){
	if( index >= size() )
		throw IndexOutOfBounds();
	int count = 0;
	for( std::map< Symbol, GrammarSet >::iterator it = lookAheadSet.begin();
		it != lookAheadSet.end();
		it++ ){
			if( count == index )
				return &(*it).first;
			count++;
	}
}

GrammarSet* LookAheadSet::getGrammarSet( const int index ){
	if( index >= size() )
		throw IndexOutOfBounds();
	int count = 0;
	for( std::map< Symbol, GrammarSet >::iterator it = lookAheadSet.begin();
		it != lookAheadSet.end();
		it++ ){
			if( count == index )
				return &(*it).second;
			count++;
	}
}

GrammarSet* LookAheadSet::getGrammarSet( const Symbol& key ){
	if( lookAheadSet.find( key ) != lookAheadSet.end() ){
		return &lookAheadSet[ key ];
	}
	else 
		throw ProductionNotFound( key );
}

GrammarSet* LookAheadSet::operator [] ( const Symbol& key ){
	return getGrammarSet( key );
}
