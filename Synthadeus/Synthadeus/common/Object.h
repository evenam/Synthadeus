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

	// insert a pointer to the heap listing
	static void insertPointer(Object* pointer);

	// remove a pointer from the heap listing
	static void removePointer(Object* pointer);

public:
	// redefine new to track the reference
	void* operator new(size_t size);

	// redefine new[] to to track the reference
	void* operator new[](size_t size);

	// redefine delete to also remove the reference
	void operator delete(void* ptr);

	// redefine delete[] to remove the reference
	void operator delete[](void* ptr);

	// pure virtual function enforces RTTI macro when inheriting
	inline virtual const char* getClassName() = 0;

	// number of Object-s allocated
	static unsigned short heapObjectCount();

	// the list of Object-s allocated
	static Object** heapObjectList(); 

	// prints a nifty list of unfreed objects on the heap and throws an assert
	static void AssertNoAbandonObjects();
};
