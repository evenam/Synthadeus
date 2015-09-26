#include "Semaphore.h"

//construct a semaphore object
Semaphore::Semaphore(int numberOfResources, LPCTSTR lpName)
{
	//int s = handle to semaphore object
	s = CreateSemaphore(NULL, InitCount, MaxCount,lpName);
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

/*if semaphore value is positive, decrement the value, otherwise
suspend the thread and block on that semaphore until it is positive.
Input: the number of resources being requested.
*/
void Semaphore::wait(int numReources)
{
	if (s > 0) {
		//this may not work with a negative value. if this doesn't work, i can try recreating semaphore.
		ReleaseSemaphore(s, -IncCount, NULL);
	}

	else while (s <= 0) {
		//Makes the current thread wait
		WaitForSingleObject(s, LockTime);
	}
}

//returns whether a thread is available to be used
bool Semaphore::check()
{
	//GetLastError May work.
	
		return true;
	
}
