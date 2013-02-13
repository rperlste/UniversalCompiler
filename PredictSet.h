#ifndef _PredictSet
#define _PredictSet

#include <string>
#include "Production.h"
#include "GrammarSet.h"
#include "IndexedMap.h"

class PredictSet : public IndexedMap< Production, GrammarSet > {
public:

	bool setUnion( Production& production, Symbol& predictValue );
	bool setUnion( Production& production, GrammarSet& predictValues );

//	Symbol getSetAsString(const int& index);
//	Symbol getSetAsString( const Symbol& key );

//	bool contains( const Symbol& key, const Symbol& grammar );
//	bool contains( const int& index, const Symbol& grammar );

//	void remove( const Symbol& key, const Symbol& grammar );

//	std::map<Production, GrammarSet>* getPredictSet();

//	int size();

};
// Return true if change occurred, false if none occurred
bool PredictSet::setUnion( Production& production, Symbol& predictValue ){
	GrammarSet tempGrammarSet;
	tempGrammarSet.insert( predictValue );
	if( this->find( production ) == this->end() ){
		return this->insert( production, tempGrammarSet );
	} else {
		return this->getValueByKey( production ).setUnion( tempGrammarSet );
	}
}

// Return true if change occurred, false if none occurred
bool PredictSet::setUnion( Production& production, GrammarSet& predictValues ){
	if( this->find( production ) == this->end() ){
		return this->insert( production, predictValues );
	} else {
		return this->getValueByKey( production ).setUnion( predictValues );
	}
}

/*
void PredictSet::add( Production production, std::string predictValue ){
		if( this->find( production ) == this->end() ){
			GrammarSet tempSet;
			tempSet.add( predictValue );
			this->insert( std::pair<Production,GrammarSet>( production, tempSet ));//[nonterminal]
		}
		else {
			this->find( production )->second.add( predictValue );
		}
	}

void PredictSet::add( Production production, GrammarSet predictValues ){
	if( this->find( production ) == this->end() ){
		this->insert( std::pair<Production,GrammarSet>( production, predictValues ));//[nonterminal]
	}
	else {
		this->find( production )->second.add( predictValues );
	}
}

Symbol PredictSet::getSetAsString(const int& index){

}

Symbol PredictSet::getSetAsString( const Symbol& key ){

}

bool PredictSet::contains( const Symbol& key, const Symbol& grammar ){

}

bool PredictSet::contains( const int& index, const Symbol& grammar ){

}

void PredictSet::remove( const Symbol& key, const Symbol& grammar ){

}

std::map<Production, GrammarSet>* PredictSet::getPredictSet(){
	return &predictSet;
}

int PredictSet::size(){
	return this->size();
}
*/
#endif