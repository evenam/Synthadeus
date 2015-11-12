////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Object ACR base and RTTI                                                 //
//   Everett Moser                                                            //
//   9-15-15                                                                  //
//                                                                            //
//   To apply ACR and RTTI support, be use this as a parent class             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Error.h"
#include <stdlib.h>
#include <limits.h>

// macro for runtime type information (RTTI)
#define RTTI_MACRO(cls) \
inline virtual const char* getClassName() { return #cls; } \
inline static const char* nameString() { return #cls; }

// object which keeps track of its heap allocations
class Object
{
private:
	// list of objects we have on the heap (maximum size)
	static unsigned short nHeapObjects;
	static Object* heapObject[USHRT_MAX];

	// modify the list of object
	static void insertPointer(Object* pointer);
	static void removePointer(Object* pointer);

public:
	// manage memory allocation and deallocation to modify the static list
	void* operator new(size_t size);
	void* operator new[](size_t size);
	void operator delete(void* ptr);
	void operator delete[](void* ptr);

	// pure virtual function enforces RTTI macro when inheriting
	inline virtual const char* getClassName() = 0;

	// query information about the list of objects allocated
	static unsigned short heapObjectCount();
	static Object** heapObjectList(); 
	static void AssertNoAbandonObjects();
};
