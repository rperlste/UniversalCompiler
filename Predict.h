#ifndef _Predict
#define _Predict

#include <iostream>
#include "MarkedVocabulary.h"
#include "LookAheadSet.h"
#include "Grammar.h"
#include "GrammarSet.h"

class Predict{
public:
	Predict(       const Grammar& );
	void           MarkLambda();  
	GrammarSet     ComputeFirst(     RightHandSide& );
	GrammarSet     ComputeFirst(     Symbol& symbol );
	GrammarSet     ComputeFirst(     Production& );
	GrammarSet     ComputeFirst(     const int&, 
	                                 const int& );
	void           FillFirstSet();
	void           FillFollowSet();
	void           FillPredictSet();
	void           PrintLookAheadSets();
	bool           DerivesLambda(    Production );
	Grammar*       getGrammar();
private:
	Grammar        grammar;
};


#endif
