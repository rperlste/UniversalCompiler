#ifndef _Grammar
#define _Grammar

#include <list>
#include "CompilerExceptions.h"
#include "GrammarSet.h"
#include "LookAheadSet.h"
#include "MarkedVocabulary.h"
#include "Production.h"

static const Symbol _LAMBDA = "";

struct Grammar {

	Productions                 productions;
	GrammarSet                  nonterminalSet;
	GrammarSet                  terminalSet;
	MarkedVocabulary            derivesLambda;
	LookAheadSet <Symbol>       firstSet;
	LookAheadSet <Symbol>       followSet;
	LookAheadSet <Production>   predictSet;

	// Search through follow sets.
	// If follow set is empty, then it is
	// the only non-derivable nonterminal.
	std::string getStartSymbol(){
		for( LookAheadSet<Symbol>::size_type i = 0; 
			i < followSet.size(); 
			i ++ ){
				if( followSet.getValueByIndex(i).size() == 0 )
					return followSet.getKeyByIndex(i);
		}

		throw GrammarException( "Start symbol not found." );
	}
};


#endif
