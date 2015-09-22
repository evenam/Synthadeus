#include "Thread.h"

Thread::Thread() : 
	sharedMemory(NULL), 
	memorySize(0), 
	memoryOwner(false),
	stopFlag(false)
{
	initialize();
}

Thread::Thread(unsigned int sharedMemorySize) : 
	sharedMemory(new char[sharedMemorySize]), 
	memorySize(sharedMemorySize), 
	memoryOwner(true),
	stopFlag(false)
{
	initialize();
}

Thread::Thread(void * const previouslyAllocatedSharedMemory) : 
	sharedMemory(previouslyAllocatedSharedMemory), 
	memorySize(sizeof(previouslyAllocatedSharedMemory)), 
	memoryOwner(false),
	stopFlag(false)
{
	initialize();
}

void Thread::initialize()
{
	threadHandle = CreateThread(NULL, 0, threadFunc, this, 0, &threadID);
	if (threadHandle == NULL)
		AssertWindowsError();
}

Thread::~Thread()
{
	if (memoryOwner)
	{
		assert(sharedMemory != NULL)
		sharedMemoryLock.lock();
		delete[] sharedMemory;
	}
}

DWORD WINAPI Thread::threadFunc(LPVOID lParam)
{
	Thread* thread = (Thread*)lParam;
	thread->run();
	return 0;
}

void Thread::wait(Thread* thread)
{
	thread->stopFlag = true;
	WaitForSingleObject(thread->threadHandle, INFINITE);
}
