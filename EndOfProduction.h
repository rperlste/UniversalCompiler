#ifndef _EOP
#define _EOP

struct EndOfProduction {

	typedef unsigned Index;

	EndOfProduction(){}

	EndOfProduction(	Index leftIndex, 
						Index rightIndex,
						Index currentIndex,
						Index topIndex ){
		this->leftIndex = leftIndex;
		this->rightIndex = rightIndex;
		this->currentIndex = currentIndex;
		this->topIndex = topIndex;
	}

	Index leftIndex;
	Index rightIndex;
	Index currentIndex;
	Index topIndex;
};


#endif