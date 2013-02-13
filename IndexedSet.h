#ifndef _IndexedSet
#define _IndexedSet

#include <set>
#include "ContainerExceptions.h"

template< typename Value >
class IndexedSet {
public:

	typedef typename std::set<Value>::size_type size_type;
	typedef typename std::set<Value>::iterator iterator;
	typedef typename std::set<Value>::const_iterator const_iterator;

	virtual ~IndexedSet(){}

	inline bool insert( const Value& value ) { return baseSet.insert( value ).second; }
	inline bool erase( const Value& value ) { return baseSet.erase( value ) > 0 ? true : false; }
	inline void clear() { baseSet.clear(); }
	bool setUnion( const IndexedSet& );


	inline size_type size() const { return baseSet.size(); }
	inline size_type max_size() const { return baseSet.max_size(); }
	inline bool empty() { return baseSet.empty(); }

	inline iterator begin() { return baseSet.begin(); }
	inline const_iterator begin() const { return baseSet.begin(); }
	inline iterator end() { return baseSet.end(); }
	inline const_iterator end() const { return baseSet.end(); }
	inline iterator find( const Value& value ) { return baseSet.find( value ); }
	inline const_iterator find( const Value& value ) const { return baseSet.find( value ); }

	bool contains( const Value& );

	int getIndex( const Value& );
	const int getIndex( const Value& ) const;

	Value get( const int& );
	Value operator [] ( const int& );

protected:

	std::set< Value > baseSet;
};

template< typename Value >
bool IndexedSet<Value>::setUnion( const IndexedSet& indexedSet ){
	bool changes = false;
	for( iterator it = indexedSet.begin();
		it != indexedSet.end();
		it ++ ){
			if( this->insert( *it ) )
				changes = true;
	}
	return changes;
}

template< typename Value >
bool IndexedSet<Value>::contains( const Value& value ){
	if( baseSet.find( value ) != baseSet.end() )
		return true;
	else
		return false;
}

template< typename Value >
int IndexedSet<Value>::getIndex( const Value& value ){

	int count = 0;

	for( iterator it = baseSet.begin();
		it != baseSet.end();
		it ++ ){
			if( (*it) == value )
				return count;
			count ++;
	}

	throw ValueNotFound();
}

template< typename Value >
const int IndexedSet<Value>::getIndex( const Value& value ) const{

	int count = 0;

	for( iterator it = baseSet.begin();
		it != baseSet.end();
		it ++ ){
			if( (*it) == value )
				return count;
			count ++;
	}

	throw ValueNotFound();
}

template< typename Value >
Value IndexedSet<Value>::get( const int& index ){

	int count = 0;

	for( iterator it = baseSet.begin();
		it != baseSet.end();
		it ++ ){
			if( count == index )
				return (*it);
			count ++;
	}

	throw IndexOutOfBounds();
}

template< typename Value >
Value IndexedSet<Value>::operator [] ( const int& index ){
	return get( index );
}

#endif
