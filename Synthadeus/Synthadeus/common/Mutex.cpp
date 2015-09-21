#include "Mutex.h"

/**
* @brief Constructor (doesn't lock mutex by default)
*/
Mutex::Mutex()
{
	m = CreateMutex(NULL, FALSE, NULL);
	if (!m)
		AssertWindowsError();
}

/**
* @brief Destructor.
*/
Mutex::~Mutex()
{
	if (!CloseHandle(m))
		AssertWindowsError();
}

/**
* @brief Locks mutex.
*/
void Mutex::lock()
{
	DWORD retCode = 0;
	retCode = WaitForSingleObject(m, INFINITE);
	assert(retCode != WAIT_ABANDONED && "A mutex has been abandoned! ");
	if (retCode == WAIT_FAILED)
		AssertWindowsError();
}

/**
* @brief Unlocks mutex.
*/
void Mutex::unlock()
{
	if (!ReleaseMutex(m))
		AssertWindowsError();

	//GetLastError? or just assert(retCode != 0 && "Failed to release unlock mutex!");
}

/**
* @brief Checks status of mutex. 
*  Locks mutex if immediately available.
*/
bool Mutex::check()
{
	DWORD retCode = 0;
	retCode = WaitForSingleObject(m, 0);
	assert(retCode != WAIT_ABANDONED && "A mutex has been abandoned!");
	if (retCode == WAIT_FAILED)
		AssertWindowsError();

	return retCode == WAIT_OBJECT_0;
}