#ifndef _ContainerExceptions
#define _ContainerExceptions

#include <exception>

	class IndexOutOfBounds	: public std::exception {};
	class KeyNotFound		: public std::exception {};
	class ValueNotFound		: public std::exception {};


#endif