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

#endif
