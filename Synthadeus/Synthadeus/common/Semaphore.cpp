#include "Semaphore.h"

//construct a semaphore object
Semaphore::Semaphore(long maxCount, LPCTSTR lpName)
{
	//int s = handle to semaphore object
	s = CreateSemaphore(NULL, InitCount, maxCount,lpName);
	if (!s) 
	{
		AssertWindowsError();
	}
}


Semaphore::~Semaphore()
{
	if (!CloseHandle(s))
		AssertWindowsError();
}

//increment the semaphore value.
void Semaphore::signal()
{
	ReleaseSemaphore(s,IncCount,NULL);
}

/*if a thread is available, increment the value, otherwise
suspend the thread and block on that semaphore until it is zero.
Input: the number of resources being requested.
*/
void Semaphore::wait(int numResources)
{
	for (int i = 0; i < numResources; i++) 
	{
		if (check() == true) {
			//this may not work with a negative value. if this doesn't work, i can try recreating semaphore.
			signal();
		}

		else {
			//Makes the current thread wait. WaitForSingleObject autmoatically decrements semaphore value if wait was signaled.
			WaitForSingleObject(s, LockTime);
		}
	}
}

//returns whether a thread is available to be used
bool Semaphore::check()
{
	DWORD waitResult =	WaitForSingleObject(s, 0);
	if (waitResult == WAIT_TIMEOUT) 
	{
		return false;
	}
	else 
	{
		signal();
		return true;
	}
}
