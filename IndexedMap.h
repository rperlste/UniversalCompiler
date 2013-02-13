#ifndef _IndexedMap
#define _IndexedMap

#include <map>
#include "ContainerExceptions.h"

template< typename Key, typename Value >
class IndexedMap{
public:
	
	typedef typename std::map<Key,Value>::key_type key_type;
	typedef typename std::map<Key,Value>::value_type value_type;
	typedef typename std::map<Key,Value>::size_type size_type;
	typedef typename std::map<Key,Value>::iterator iterator;
	typedef typename std::map<Key,Value>::const_iterator const_iterator;

	virtual ~IndexedMap(){}

	inline bool insert( const Key& key, const Value& value ) { return baseMap.insert( value_type(key,value)).second; }
	bool insertOverwrite( const Key&, const Value& );
	inline bool remove( const Key& key ) { return baseMap.erase( key ) > 0 ? true : false; }

	inline size_type size() const { return baseMap.size(); }
	inline size_type max_size() const { return baseMap.max_size(); }
	inline bool empty() { return baseMap.empty(); }

	inline iterator begin() { return baseMap.begin(); }
	inline const_iterator begin() const { return baseMap.begin(); }
	inline iterator end() { return baseMap.end(); }
	inline const_iterator end() const { return baseMap.end(); }
	inline iterator find( const Key& key ) { return baseMap.find( key ); }
	inline const_iterator find( const Key& key ) const { return baseMap.find( key ); }

	bool containsKey( const Key& );
	bool containsValue( const Value& );
	bool containsPair( const Key&, const Value& );
	bool containsPair( const value_type& );

	value_type getPairByIndex( const int& );

	Key getKeyByValue( const Value& );
	Key getKeyByIndex( const int& );

	Value getValueByKey( const Key& );
	Value getValueByIndex( const int& );

	int getIndexByValue( const Value& );
	int getIndexByKey( const Key& );

	inline Value operator [] ( const Key& key ) { return baseMap[ key ]; }

protected:

	std::map< Key, Value > baseMap;
};

template< typename Key, typename Value >
bool IndexedMap<Key,Value>::insertOverwrite( const Key& key, const Value& value ){
	iterator keyIter = baseMap.find(key);
	if( keyIter != baseMap.end() && !(baseMap.key_comp()( key, keyIter->first ) )){
		if( keyIter->second == value ) {
			return false;
		} else {
			keyIter->second = value;
			return true;
		}
	}
	else{
		baseMap.insert( keyIter, value_type( key, value ) );
		return true;
	}
}

template< typename Key, typename Value >
bool IndexedMap<Key,Value>::containsKey( const Key& key ){
    return baseMap.find( key ) == baseMap.end() ? false : true ;
}

template< typename Key, typename Value >
bool IndexedMap<Key,Value>::containsValue( const Value& value ){
    for( iterator it = baseMap.begin();
        it != baseMap.end();
        it ++ ){
        if( it->second == value )
            return true;
        }
    return false;
}

template< typename Key, typename Value >
bool IndexedMap<Key,Value>::containsPair( const value_type& value_type ){
	for( iterator it = baseMap.begin();
		it != baseMap.end();
		it ++ ){
			if( *it == value_type )
				return true;
	}
	return false;
}

template< typename Key, typename Value >
bool IndexedMap<Key,Value>::containsPair( const Key& key, const Value& value ){
	return containsPair( value_type( key, value ) );
}

template< typename Key, typename Value >
typename IndexedMap<Key,Value>::value_type IndexedMap<Key,Value>::getPairByIndex( const int& index ){
	int count = 0;
	for( iterator it = baseMap.begin();
		it != baseMap.end();
		it ++ ){
			if( count == index )
				return (*it);
			count ++;
	}
	throw IndexOutOfBounds();
}

template< typename Key, typename Value >
Key IndexedMap<Key,Value>::getKeyByValue( const Value& value ){
    for( iterator it = baseMap.begin();
        it != baseMap.end();
        it ++ ){
        if( it->second == value )
            return it->first;
    }
    throw ValueNotFound();
}

template< typename Key, typename Value >
Key IndexedMap<Key,Value>::getKeyByIndex( const int& index ){
    int count = 0;
    for( iterator it = baseMap.begin();
        it != baseMap.end();
        it ++ ){
        if( count == index )
            return it->first;
        count ++;
    }
    throw IndexOutOfBounds();
}

template< typename Key, typename Value >
Value IndexedMap<Key,Value>::getValueByKey( const Key& key ){
    iterator it = baseMap.find( key );
    if( it != baseMap.end() )
        return ( it->second );
    else
        throw KeyNotFound();
}

template< typename Key, typename Value >
Value IndexedMap<Key,Value>::getValueByIndex( const int& index ){
    int count = 0;
    for( iterator it = baseMap.begin();
        it != baseMap.end();
        it ++ ){
        if( count == index )
            return it->second;
        count ++;
    }
    throw IndexOutOfBounds();
}

template< typename Key, typename Value >
int IndexedMap<Key,Value>::getIndexByKey( const Key& key ){
    int count = 0;
    for( iterator it = baseMap.begin();
        it != baseMap.end();
        it ++ ){
        if( it->first == key )
            return count;
        count ++;
    }
    throw KeyNotFound();
}

template< typename Key, typename Value >
int IndexedMap<Key,Value>::getIndexByValue( const Value& value ){
    int count = 0;
    for( iterator it = baseMap.begin();
        it != baseMap.end();
        it ++ ){
        if( it->second == value )
            return count;
        count ++;
    }
    throw ValueNotFound();
}


#endif
