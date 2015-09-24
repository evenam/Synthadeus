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

class Thread : public Object
{
public:
	enum { RUNNING = 1, IDLE = 0 };
	enum { MAX_RUNNING_THREADS = 4 };

private:
	Mutex sharedMemoryLock;
	void* const sharedMemory;
	const bool memoryOwner;
	const unsigned int memorySize;
	static DWORD WINAPI threadFunc(LPVOID lParam);
	HANDLE threadHandle;
	DWORD threadID;
	int threadState;

	static int numThreads;
	static Thread* threads[MAX_RUNNING_THREADS]; // sick threads dude! (all running threads)

protected:
	bool stopFlag;
	virtual void run() = 0;

public:
	RTTI_MACRO(Thread);

	Thread(); // Thread with no shared memory
	Thread(unsigned int sharedMemorySize); // Thread with owned, newly created heap memory
	Thread(unsigned int sharedMemorySize, void* const previouslyAllocatedSharedMemory); // Thread with non-owned heap memory
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
		sharedMemoryLock.unlock(); 
	}

	// abstract run, wait, and stop function
	static void start(Thread* thread);
	static void wait(Thread* thread);
	static void stop(Thread* thread);

	// just to make sure we good at the end of the program
	static inline void assertAllThreadsHaveTerminated()
	{
		assert(numThreads == 0);
	}
};
