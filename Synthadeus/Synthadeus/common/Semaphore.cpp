#include "Semaphore.h"

#define lockTime 1000

Semaphore::Semaphore(int numberOfThreads)
{
	int s = numberOfThreads;
	//CreateSemaphore();
}

Semaphore::~Semaphore()
{
}
//increment the semaphore value.
void Semaphore::signal()
{
	s++;
}

/*if semaphore value is positive, decrement the value, otherwise
suspend the thread and block on that semaphore until it is positive
*/
void Semaphore::wait(HANDLE hHandle)
{
	if (s > 0) {
		s--;
	}

	else while (s <= 0) {
		//Makes the current thread wait
		WaitForSingleObject(hHandle, lockTime);
	}
}
//returns whether a thread is available to be used
bool Semaphore::check()
{
	if (1 != 0) {
		return true;
	}
	return false;
}
