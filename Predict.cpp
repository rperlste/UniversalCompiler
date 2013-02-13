#include "Predict.h"

Predict::Predict( const Grammar& grammar ){
	this->grammar = grammar;
}

bool Predict::DerivesLambda( Production production ){

	// Test for empty production RHS
	if( production.getRHS().size() == 0 ){
		return true;
	} else {
		// Iterate through nonterminal/terminal symbols
		for( int j = 0; j < production.getRHS().size(); j++ ){
			if( production.getRHS().get(j) == _LAMBDA )
				return true;
		}
	}

	return false;
}

void Predict::MarkLambda(){
	// Initializiation
	// for V in Vocabulary . DerivesLambda(V) := False
	for( int i = 0; i < grammar.nonterminalSet.size(); i ++ ){
		grammar.derivesLambda.insertOverwrite( grammar.nonterminalSet[i], false );
	}

	// for P in G.Productions
	for( int i = 0; i < grammar.productions.size(); i++ ){
		Production production = grammar.productions.get(i);
		if( DerivesLambda( production ) )
			grammar.derivesLambda.insertOverwrite( 
			production.getLHS(), 
			true );
	}
}

GrammarSet Predict::ComputeFirst( Symbol& symbol ){
	GrammarSet result;
	// Nonterminal symbol
	if( grammar.nonterminalSet.contains( symbol )){
		int index = grammar.productions.getProductionIndexFirstOf( symbol );
		while( grammar.productions[index].getLHS() == symbol ){
			result = ComputeFirst( grammar.productions[index].getRHS() );
			index ++;
		}
	// else terminal symbol
	} else {
		result.insert( symbol );
		return result;
	}
	return result;
}

GrammarSet Predict::ComputeFirst( Production& production ){
	return ComputeFirst( production.getRHS() );
}

GrammarSet Predict::ComputeFirst( const int& beginIndex, const int& endIndex ){
	GrammarSet result;
	for( int i = beginIndex; i < endIndex; i ++ ){
		result.setUnion( ComputeFirst( grammar.productions[i].getRHS() ));
	}
	return result;
}

GrammarSet Predict::ComputeFirst( RightHandSide& RHS ){
	GrammarSet result;
	int k = RHS.size();
	if( k == 0 ){
		// Result := {λ}; 
		result.insert( _LAMBDA );
	} else {
		// Result := FirstSet(x(1)) — {λ};
		// Compute first set for all productions of type RHS[0]
		result.setUnion( ComputeFirst( RHS[0] ));
		result.erase( _LAMBDA );

		
		int i = 1;
		// while i < k and λ ∈ FirstSet(x(i))
		while( (i < (k-1)) && grammar.firstSet[ RHS.get(i) ].contains( _LAMBDA )){

			i++;
			// Result := Result ∪ (FirstSet(x(i)) — {λ}) 
			result.setUnion( grammar.firstSet[ RHS.get(i) ] );
			result.erase( _LAMBDA );
		}
		if( (i == (k-1)) && grammar.firstSet[ RHS.get(i) ].contains( _LAMBDA )){
			result.insert( _LAMBDA );
		}
	}
	return result;
}

void Predict::FillFirstSet(){
	// Populate lambda into first sets with lambda, else initialize empty
	// for A in nonterminal
	for( int i = 0; i < grammar.nonterminalSet.size(); i ++ ){
		// if DerivesLambda(A) 
		if( grammar.derivesLambda[ grammar.nonterminalSet.get(i) ]){
			// then FirstSet(A) := {λ}; 
			grammar.firstSet.setUnion( grammar.nonterminalSet.get(i), _LAMBDA );
		}
		else{
			// else FirstSet(A) := ∅;
			grammar.firstSet.setUnion( grammar.nonterminalSet.get(i), GrammarSet() );
		}
	}

	// Union first of a production
	// for a in terminal 
	for( int termIndex = 0; termIndex < grammar.terminalSet.size(); termIndex ++ ){

		// FirstSet(a) := {i};
		grammar.firstSet.setUnion( grammar.terminalSet[termIndex], grammar.terminalSet[termIndex] );

		// for A in productions
		for( int prodIndex = 0; prodIndex < grammar.productions.size(); prodIndex ++ ){
			//if there exists a production A —> a . . . 
			if( grammar.productions.get(prodIndex).getRHS().get(0) == grammar.terminalSet[termIndex] ){
				// then FirstSet(A) := FirstSet(A) ∪ {a};
				grammar.firstSet.setUnion( grammar.productions.get(prodIndex).getLHS(), grammar.terminalSet[termIndex] );
			}
		}
	}

	// Union remaining terminals through nonterminal production calls
	// for p in productions
	for( int i = 0; i < grammar.productions.size(); i ++  ){

		// FirstSet(LHS(p)) := FirstSet(LHS(p)) ∪ ComputeFirst(RHS(p));
		grammar.firstSet.setUnion( 
				grammar.productions.get(i).getLHS(), 
				ComputeFirst( grammar.productions.get(i).getRHS() ));
	}
}


void Predict::FillFollowSet(){
	// Initialize empty set
	//for A in nonterminals
	for( int nontermIndex = 0; nontermIndex < grammar.nonterminalSet.size(); nontermIndex ++ ){
		// FollowSet(A) := ∅; 
		grammar.followSet.insert( grammar.nonterminalSet[nontermIndex], GrammarSet() );
	}

	// for each production p: A —> xBy
	// for A in production
	for( int indexA = 0; indexA < grammar.productions.size(); indexA ++ ){

		// for symbol in RHS
		for( int indexB = 0; indexB < grammar.productions.get(indexA).getRHS().size(); indexB ++ ){

			// for each occurrence of a nonterminal B in RHS(p)
			if( grammar.nonterminalSet.contains( grammar.productions.get(indexA).getRHS().get(indexB) )){
				
				GrammarSet tempGSet;
				bool yContainsLambda = false;
				// Check RHS for y value or _LAMBDA
				if( indexB < (grammar.productions.get(indexA).getRHS().size() - 1) ){
					// then FollowSet(B) := FollowSet(B) ∪ (ComputeFirst(y) — {λ}); 
					tempGSet = ComputeFirst( grammar.productions.get(indexA).getRHS().get(indexB+1) );
					if( tempGSet.contains( _LAMBDA ) ){
						yContainsLambda = true;
						tempGSet.erase( _LAMBDA );
					}
				} else {
					yContainsLambda = true;
				}

				// if λ ∈ ComputeFirst(y) 
				if( yContainsLambda ){
					// then FollowSet(B) := FollowSet(B) ∪ FollowSet(A);
					grammar.followSet[grammar.productions.get(indexA).getRHS().get(indexB)].setUnion(
						grammar.followSet[grammar.productions.get(indexA).getLHS()] );
				}
			}
		}
	}
}


void Predict::FillPredictSet(){
	// Iterate through productions
	for( int i = 0; i < grammar.productions.size(); i ++ ){
		// if LAMBDA First (X1X2. . .Xm)
		GrammarSet tempSet = ComputeFirst( grammar.productions[i].getRHS() );
		if( tempSet.contains( _LAMBDA )){
			// then (First (X1X2. . .Xm) U Follow(A)) - LAMBDA
			grammar.predictSet.setUnion( grammar.productions[i], tempSet );
			grammar.predictSet.setUnion( grammar.productions[i], grammar.followSet[grammar.productions[i].getLHS()] );
		}
		else {
			// else First (X1X2. . .Xm)
			grammar.predictSet.setUnion( grammar.productions[i], tempSet );
		}
	}
}


void Predict::PrintLookAheadSets(){
	std::cout << "\n\n::: FIRST SET :::\n";
	for( int firstSetIndex = 0; firstSetIndex < grammar.firstSet.size(); firstSetIndex++ ){
		if( grammar.firstSet.getKeyByIndex( firstSetIndex ) != _LAMBDA )
			std::cout << "\n" << grammar.firstSet.getKeyByIndex(firstSetIndex) << " = " << grammar.firstSet.getValueByIndex(firstSetIndex).getSetAsString();
	}
	
	std::cout << "\n\n::: FOLLOW SET :::\n";
	for( int followSetIndex = 0; followSetIndex < grammar.followSet.size(); followSetIndex++ ){
		std::cout << "\n" << grammar.followSet.getKeyByIndex(followSetIndex) << " = " << grammar.followSet.getValueByIndex(followSetIndex).getSetAsString();
	}

	std::cout << "\n\n::: PREDICT SET :::\n";
	for( int predictSetIndex = 0; predictSetIndex < grammar.predictSet.size(); predictSetIndex++ ){
		std::cout << "\n" << grammar.predictSet.getKeyByIndex(predictSetIndex).getLHS() << " = " << grammar.predictSet.getValueByIndex(predictSetIndex).getSetAsString();
	}
}

Grammar* Predict::getGrammar(){
	return &grammar;
}