#include "Object.h"

unsigned short Object::nHeapObjects = 0;
Object* Object::heapObject[USHRT_MAX];

#if defined(DEBUG) || defined(_DEBUG)
#define insert(a) insertPointer(a)
#define remove(a) removePointer(a)
#else
#define insert(a) nHeapObjects++
#define remove(a) nHeapObjects--
#endif

void Object::insertPointer(Object* pointer)
{
	heapObject[nHeapObjects++] = pointer;
}

void Object::removePointer(Object* pointer)
{

	for (int i = 0; i < nHeapObjects; i++)
	{
		if (heapObject[i] == (Object*)pointer)
		{
			for (; i < nHeapObjects - 1; i++)
			{
				heapObject[i] = heapObject[i + 1];
			}
			heapObject[i++] = NULL;
			break;
		}
	}
	nHeapObjects--;
}

void* Object::operator new(size_t size)
{
	void* ptr = malloc(size);
	if (!ptr)
		assert(!"Failed to allocate memory.");
	insert((Object *)ptr);
	return ptr;
}

void* Object::operator new[](size_t size)
{
	void* ptr = malloc(size);
	if (!ptr)
		assert(!"Failed to allocate memory.");
	insert((Object *)ptr);
	return ptr;
}

void Object::operator delete(void* ptr)
{
	remove((Object *)ptr);
	free(ptr);
}

void Object::operator delete[](void* ptr)
{
	remove((Object *)ptr);
	free(ptr);
}

unsigned short Object::heapObjectCount()
{ 
	return nHeapObjects; 
}

Object** Object::heapObjectList()
{ 
	return heapObject; 
}

void Object::AssertNoAbandonObjects()
{
	if (nHeapObjects > 0)
	{
#if defined(DEBUG) || defined(_DEBUG)
		DebugPrintf("%s\n", "List of objects not freed:\n------------------------------");
		for (int i = 0; i < nHeapObjects; i++)
		{
			DebugPrintf(" *\t%s\n", heapObject[i]->getClassName());
			delete heapObject[i];
			heapObject[i] = NULL;
		}
		assert(!"Heap still has objects on it. (debug-mode clean)");
#else
		DebugPrintf("*** MEMORY LEAKS DETECTED ***\n");
#endif
	}
}


