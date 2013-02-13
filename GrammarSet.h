#ifndef _GrammarSet
#define _GrammarSet

#include <set>
#include <string>
#include "IndexedSet.h"

typedef std::string Symbol;

class GrammarSet : public IndexedSet<Symbol>{
public:

	// Returns set in format "{ "A", "B", "C" }"
	std::string getSetAsString(){
		if( size() == 0 )
			return "{ }";

		std::string setValue = "{ ";
		for( size_type i = 0; i < size(); i++ ){
			setValue += "\"" + this->get(i) + "\"";
			if( i != (size()-1) )
				setValue += " , ";
			else
				setValue += " ";
		}
		setValue += "}";

		return setValue;
	}
};

#endif
