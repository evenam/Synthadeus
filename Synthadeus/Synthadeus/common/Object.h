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

#define RTTI_MACRO(cls) \
inline virtual const char* getClassName() { return #cls; } \
inline static const char* nameString() { return #cls; }

class Object
{
private:
	static unsigned short nHeapObjects;
	static Object* heapObject[USHRT_MAX];
	static void insertPointer(Object* pointer);
	static void removePointer(Object* pointer);

public:
	void* operator new(size_t size);
	void* operator new[](size_t size);
	void operator delete(void* ptr);
	void operator delete[](void* ptr);

	inline virtual const char* getClassName() = 0;

	static unsigned short heapObjectCount();
	static Object** heapObjectList(); 
	static void AssertNoAbandonObjects();
};
