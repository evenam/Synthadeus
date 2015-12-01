#include "Object.h"

unsigned short Object::nHeapObjects = 0;
Object* Object::heapObject[USHRT_MAX];

#if defined(DEBUG) || defined(_DEBUG)

// insert and remove only modify the list if we are in debug mode
#define insert(a) insertPointer(a)
#define remove(a) removePointer(a)

#else

// else we just count number of references
#define insert(a) nHeapObjects++
#define remove(a) nHeapObjects--

#endif

void Object::insertPointer(Object* pointer)
{
	// append the object to the back of the list
	assert(nHeapObjects < USHRT_MAX);
	heapObject[nHeapObjects++] = pointer;
}

void Object::removePointer(Object* pointer)
{
	// idiot test
	assert(nHeapObjects > 0);

	// find the object
	for (int i = 0; i < nHeapObjects; i++)
	{
		if (heapObject[i] == (Object*)pointer)
		{
			// remove it by overwriting its reference, movinf the rest of the 
			for (; i < nHeapObjects - 1; i++)
			{
				heapObject[i] = heapObject[i + 1];
			}

			// replace the last point with NULL for safety
			heapObject[i++] = NULL;
			break;
		}
	}

	// we have one less object
	nHeapObjects--;
}

void* Object::operator new(size_t size)
{
	// allocate the memory
	void* ptr = malloc(size);
	if (!ptr)
		assert(!"Failed to allocate memory.");

	// add the object reference
	insert((Object *)ptr);
	return ptr;
}

void* Object::operator new[](size_t size)
{
	// allocate the memory
	void* ptr = malloc(size);
	if (!ptr)
		assert(!"Failed to allocate memory.");

	// add the object reference
	insert((Object *)ptr);
	return ptr;
}

void Object::operator delete(void* ptr)
{
	// remove the reference
	remove((Object *)ptr);

	// free the memory
	free(ptr);
}

void Object::operator delete[](void* ptr)
{
	// remove the reference
	remove((Object *)ptr);

	// free the memory
	free(ptr);
}

unsigned short Object::heapObjectCount()
{ 
	// the size of the heap list
	return nHeapObjects; 
}

Object** Object::heapObjectList()
{ 
	// return the list of object statically held
	return heapObject; 
}

void Object::AssertNoAbandonObjects()
{
	// only if we have objects on the heap
	if (nHeapObjects > 0)
	{
#if defined(DEBUG) || defined(_DEBUG)
		// in debug mode, log the list of all objects with the nifty RTTI_MACRO function decl's
		DebugPrintf("%s\n", "List of objects not freed:\n------------------------------");
		for (int i = 0; i < nHeapObjects; i++)
		{
			DebugPrintf(" *\t%s\n", heapObject[i]->getClassName());
			delete heapObject[i];
			heapObject[i] = NULL;
		}

		// throw the assert that we haven't cleaned up properly
		assert(!"Heap still has objects on it. (debug-mode clean)");
#else
		
		// in release mode, just log and exit normally. the end user will thank us later
		DebugPrintf("*** MEMORY LEAKS DETECTED ***\n");
#endif
	}
}


