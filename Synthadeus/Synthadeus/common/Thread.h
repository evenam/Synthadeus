////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Thread Interface                                                         //
//   Everett Moser                                                            //
//   9-8-15                                                                   //
//                                                                            //
//   A generic thread interface as a base for Threads.                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Windows.h>
#include "Mutex.h"
#include "Error.h"
#include "Object.h"

// bytes of memory
#define THREAD_DEFAULT_MEMORY_SIZE 1024
#define THREAD_NO_SHARED_MEMORY 0
#define THREAD

class Thread : public Object
{
private:
	Mutex sharedMemoryLock;
	void* const sharedMemory;
	const bool memoryOwner;
	const unsigned int memorySize;
	static DWORD WINAPI threadFunc(LPVOID lParam);
	HANDLE threadHandle;
	DWORD threadID;
	void initialize();

protected:
	bool stopFlag;

public:
	RTTI_MACRO(Thread);

	Thread(); // Thread with no shared memory
	Thread(unsigned int sharedMemorySize); // Thread with owned, newly created heap memory
	Thread(void* const previouslyAllocatedSharedMemory); // Thread with non-owned heap memory
	~Thread();

	// get access to shared memory
	inline void* const getSharedMemory() 
	{
		assert(sharedMemory != NULL); 
		sharedMemoryLock.lock(); 
		return sharedMemory;
	}

	template<class TYPE> inline TYPE* const getSharedMemory() 
	{
		assert(sharedMemory != NULL); 
		sharedMemoryLock.lock();
		return reinterpret_cast<TYPE*>(sharedMemory);
	}

	// release access to shared memory
	inline void releaseSharedMemory() 
	{
		assert(sharedMemory != NULL); 
		assert(!sharedMemoryLock.check()); 
		sharedMemoryLock.unlock(); 
	}

	// abstract run and wait function
	virtual void run() = 0;
	static void wait(Thread* thread);
};

