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

#define RTTI_MACRO(cls) inline virtual const char* getClassName() { return #cls; }

class Object
{
private:
	static unsigned short nHeapObjects;
	static Object* heapObject[USHRT_MAX];

public:
	inline void* operator new(size_t size)
	{
		void* ptr = malloc(size);
		if (!ptr)
			assert(!"Failed to allocate memory.");
		nHeapObjects++;
		return ptr;
	}

	inline void* operator new[](size_t size)
	{
		void* ptr = malloc(size);
		if (!ptr)
			assert(!"Failed to allocate memory.");
		nHeapObjects++;
		return ptr;
	}

	void operator delete(void* ptr)
	{
		free(ptr);
		nHeapObjects--;
	}

	void operator delete[](void* ptr)
	{
		free(ptr);
		nHeapObjects--;
	}

	inline virtual const char* getClassName() = 0;

	static inline unsigned short heapObjectCount() { return nHeapObjects; }
	static inline Object** heapObjectList() { return heapObject; }
};
