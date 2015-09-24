#include "Thread.h"

int Thread::numThreads = 0;
Thread* Thread::threads[Thread::MAX_RUNNING_THREADS];

Thread::Thread() :
	sharedMemory(NULL),
	memorySize(0),
	memoryOwner(false),
	stopFlag(false),
	threadState(IDLE)
{
}

Thread::Thread(unsigned int sharedMemorySize) : 
	sharedMemory(new char[sharedMemorySize]), 
	memorySize(sharedMemorySize), 
	memoryOwner(true),
	stopFlag(false),
	threadState(IDLE)
{
}

Thread::Thread(void * const previouslyAllocatedSharedMemory) : 
	sharedMemory(previouslyAllocatedSharedMemory), 
	memorySize(sizeof(previouslyAllocatedSharedMemory)), 
	memoryOwner(false),
	stopFlag(false),
	threadState(IDLE)
{
}

Thread::~Thread()
{
	DWORD code = 0;
	if (!TerminateThread(threadHandle, code))
		AssertWindowsError();
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
	thread->threadState = RUNNING;
	return 0;
}

void Thread::start(Thread* thread)
{
	DebugPrintf("Attempting to start thread: %s\n", thread->getClassName());
	assert(thread != NULL);
	thread->stopFlag = false;
	thread->threadHandle = CreateThread(NULL, 0, threadFunc, thread, 0, &(thread->threadID));
	if (thread->threadHandle == NULL)
		AssertWindowsError();
	thread->threadState = RUNNING;
	numThreads++;
	DebugPrintf("Successfully started thread: %s\n", thread->getClassName());
}

void Thread::wait(Thread* thread)
{
	DebugPrintf("Waiting for thread to stop: %s\n", thread->getClassName());
	assert(thread != NULL);
	thread->stopFlag = true;
	DWORD code = 0;
	code = WaitForSingleObject(thread->threadHandle, INFINITE);
	assert(code != WAIT_ABANDONED && "A thread has been abandoned! ");
	if (code == WAIT_FAILED)
		AssertWindowsError();
	thread->threadState = IDLE;
	numThreads--;
	DebugPrintf("Thread has stopped normally: %s\n", thread->getClassName())
}

void Thread::stop(Thread* thread)
{
	DebugPrintf("Terminating thread: %s\n", thread->getClassName());
	assert(thread != NULL);
	thread->stopFlag = true;
	DWORD code = 0;
	if (!TerminateThread(thread->threadHandle, code))
		AssertWindowsError();
	thread->threadState = IDLE;
	numThreads--;
	DebugPrintf("Thread terminated: %s\n", thead->getClassName());
}
