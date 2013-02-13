#ifndef _MarkedVocabulary
#define _MarkedVocabulary

#include "Production.h"
#include "IndexedMap.h"

class MarkedVocabulary : public IndexedMap< Symbol, bool >{
public:

	bool derivesLambda( Symbol& nonterminal ){
		iterator it = this->find( nonterminal );
		if( it != end() )
			return (*it).second;
		else
			return false;
	}

};

#endif