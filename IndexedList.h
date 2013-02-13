#ifndef _IndexedList
#define _IndexedList

#include <list>
#include "ContainerExceptions.h"

template< typename Value >
class IndexedList {
public:

	typedef typename std::list<Value>::size_type size_type;
	typedef typename std::list<Value>::iterator iterator;
	typedef typename std::list<Value>::const_iterator const_iterator;
	typedef typename std::list<Value>::reference reference;
	typedef typename std::list<Value>::const_reference const_reference;

	~IndexedList(){}

	inline void add( const Value& value ) { baseList.push_back( value ); }
	inline void push_back( const Value& value ) { baseList.push_back( value ); }
	inline void push_front( const Value& value ) { baseList.push_front( value ); }
	void set( const IndexedList& indexedList );

	inline void pop_back() { baseList.pop_back(); }
	inline void pop_front() { baseList.pop_front(); }
	inline void clear() { baseList.clear(); }

	inline size_type size() const { return baseList.size(); }
	inline size_type max_size() const { return baseList.max_size(); }
	inline bool empty() { return baseList.empty(); }

	inline iterator begin() { return baseList.begin(); }
	inline const_iterator begin() const { return baseList.begin(); }
	inline iterator end() { return baseList.end(); }
	inline const_iterator end() const { return baseList.end(); }
	iterator find( const Value& );
	const_iterator find( const Value& ) const;


	bool contains( const Value& );

	int getIndex( const Value& );

	inline reference front() { return baseList.front(); }
	inline const_reference front() const { return baseList.front(); }
	inline reference back() { return baseList.back(); }
	inline const_reference back() const { return baseList.back(); }
	reference operator [] ( const int& );
	const_reference operator [] ( const int& ) const;
	inline reference get ( const int& index ) { return operator[]( index ); }
	inline const_reference get ( const int& ) const { return operator[]( index ); }


private:

	std::list<Value> baseList;
};

template < typename Value >
void IndexedList<Value>::set( const IndexedList& indexedList ){
	this->clear();
	*this = indexedList;
}

template < typename Value >
typename IndexedList<Value>::iterator IndexedList<Value>::find( const Value& value ) { 
	iterator it;
	for( it = baseList.begin();
		it != baseList.end();
		it ++ ){
			if( (*it) == value )
				return it;
	}
	return it;
}

template < typename Value >
typename IndexedList<Value>::const_iterator IndexedList<Value>::find( const Value& value ) const { 
	iterator it = find( value );
	return it;
}


template < typename Value >
bool IndexedList<Value>::contains( const Value& value ){
	if( find( value ) != baseList.end() )
		return true;
	else
		return false;
}

template < typename Value >
int IndexedList<Value>::getIndex( const Value& value ){
	int count = 0;
	for( iterator it = baseList.begin();
		it != baseList.end();
		it ++ ){
			if( (*it) == value )
				return count;
			count ++;
	}
	throw ValueNotFound();
}

template < typename Value >
typename IndexedList<Value>::reference IndexedList<Value>::operator [] ( const int& index ){
	int count = 0;
	for( iterator it = baseList.begin();
		it != baseList.end();
		it ++ ){
			if( count == index )
				return (*it);
			count ++;
	}
	throw IndexOutOfBounds();
}

template < typename Value >
typename IndexedList<Value>::const_reference IndexedList<Value>::operator [] ( const int& index ) const{
	int count = 0;
	for( const_iterator it = baseList.begin();
		it != baseList.end();
		it ++ ){
			if( count == index )
				return (*it);
			count ++;
	}
	throw IndexOutOfBounds();
}

#endif