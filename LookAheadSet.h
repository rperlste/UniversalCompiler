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

#endif
