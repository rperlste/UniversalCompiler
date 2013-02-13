#ifndef _LookAheadSet
#define _LookAheadSet

#include "Production.h"
#include "GrammarSet.h"
#include "IndexedMap.h"
#include <map>
#include <list>

template< typename Key >
class LookAheadSet : public IndexedMap< Key, GrammarSet >{
public:

	// Return true if change occurred, false if none occurred
	bool setUnion( const Key& key, const Symbol& grammar );
	bool setUnion( const Key& key, const GrammarSet& grammarSet );

	// Return a Symbol representation of the set
//	Symbol getSetAsString(const int& index);
//	Symbol getSetAsString( const Symbol& key );

};

// Return true if change occurred, false if none occurred
template< typename Key >
bool LookAheadSet<Key>::setUnion( const Key& key, const Symbol& grammar ){
	GrammarSet tempGrammarSet;
	tempGrammarSet.insert( grammar );
	iterator it = this->find( key );
	if( it == this->end() ){
		return this->insert( key, tempGrammarSet );
	} else {
		return it->second.setUnion( tempGrammarSet );
	}
}

// Return true if change occurred, false if none occurred
template< typename Key >
bool LookAheadSet<Key>::setUnion( const Key& key, const GrammarSet& grammarSet ){
	iterator it = this->find( key );
	if( it == this->end() ){
		return this->insert( key, grammarSet );
	} else {
		return it->second.setUnion( grammarSet );
	}
}
/*
// Return a Symbol representation of the set
Symbol LookAheadSet::getSetAsString(const int& index){
	return this->get(*getKey( index )) + " = " + getGrammarSet(index)->getSetAsString() + "\n";
}

Symbol LookAheadSet::getSetAsString( const Symbol& key ){
	return key + " = " + getGrammarSet(key)->getSetAsString() + "\n";
}

/*
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
	if( this->find( key ) == this->end() ){
		GrammarSet grammarSet;
		lookAheadSet[ key ] = grammarSet;
		return true;
	}
	else
		return false;
}
*/

/*
bool LookAheadSet::contains( const Symbol& key, const Symbol& grammar ){
	std::map< Symbol, GrammarSet >::iterator it = this->find( key );
	if( it != this->end() )
		return (*it).second.contains( grammar );
}

bool LookAheadSet::contains( const int& index, const Symbol& grammar ){
	return getGrammarSet( index)->contains(grammar);
}

void LookAheadSet::remove( const Symbol& key, const Symbol& grammar ){
	if( this->find( key ) != this->end() )
		this->find( key )->second.remove( grammar );
}

std::map<Symbol, GrammarSet> LookAheadSet::getLookAheadSet(){
	return lookAheadSet;
}

const int LookAheadSet::size(){
	return this->size();
}

int LookAheadSet::getIndexOfKey( const Symbol& key ){
	int count = 0;
	for( std::map< Symbol, GrammarSet >::iterator it = this->begin();
		it != this->end();
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
	for( std::map< Symbol, GrammarSet >::iterator it = this->begin();
		it != this->end();
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
	for( std::map< Symbol, GrammarSet >::iterator it = this->begin();
		it != this->end();
		it++ ){
			if( count == index )
				return &(*it).second;
			count++;
	}
}

GrammarSet* LookAheadSet::getGrammarSet( const Symbol& key ){
	if( this->find( key ) != this->end() ){
		return &lookAheadSet[ key ];
	}
	else 
		throw ProductionNotFound( key );
}

GrammarSet* LookAheadSet::operator [] ( const Symbol& key ){
	return getGrammarSet( key );
}

*/
#endif