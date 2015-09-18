#include "Mutex.h"

/**
* @brief Constructor (doesn't lock mutex by default)
*/
Mutex::Mutex()
{
	m = CreateMutex(NULL, FALSE, NULL);

	//just assert(m != NULL && "Failed to create mutex!"); or GetLastError for more info?
}

/**
* @brief Destructor.
*/
Mutex::~Mutex()
{
	retCode = CloseHandle(m);
	//GetLastError? or just assert(retCode != 0 && "Failed to close mutex!")
}

/**
* @brief Locks mutex.
*/
void Mutex::lock()
{
	retCode = WaitForSingleObject(m, INFINITE);
	assert(retCode != WAIT_ABANDONED && "A mutex has been abandoned!");

	//GetLastError? or just assert(retCode != WAIT_FAILED && "Failed to wait for mutex!");
}

/**
* @brief Unlocks mutex.
*/
void Mutex::unlock()
{
	retCode = ReleaseMutex(m);

	//GetLastError? or just assert(retCode != 0 && "Failed to release unlock mutex!");
}

/**
* @brief Checks status of mutex. 
*  Locks mutex if immediately available.
*/
bool Mutex::check()
{
	retCode = WaitForSingleObject(m, 0);
	assert(retCode != WAIT_ABANDONED && "A mutex has been abandoned!");

	//GetLastError? or just assert(retCode != WAIT_FAILED && "Failed to wait for mutex!");

	return retCode == WAIT_OBJECT_0;
}