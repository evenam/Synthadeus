#include "Mutex.h"

/**
* @brief Constructor (doesn't lock mutex by default)
*/
Mutex::Mutex()
{
	m = CreateMutex(NULL, FALSE, NULL);
}

/**
* @brief Destructor.
*/
Mutex::~Mutex()
{
	CloseHandle(m);
}

/**
* @brief Locks mutex.
*/
void Mutex::lock()
{
	WaitForSingleObject(m, INFINITE);
}

/**
* @brief Unlocks mutex.
*/
void Mutex::unlock()
{
	ReleaseMutex(m);
}

/**
* @brief Checks status of mutex. 
*  Locks mutex if immediately available.
*/
bool Mutex::check()
{
	return WaitForSingleObject(m, 0) == WAIT_OBJECT_0;
}