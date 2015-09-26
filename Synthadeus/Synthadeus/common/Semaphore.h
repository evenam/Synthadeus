#pragma once

#include <Windows.h>
#include "Object.h"

//this is a wrapper for windows semaphore object

// Basic semaphore skeleton
// see https://msdn.microsoft.com/en-us/library/windows/desktop/ms685129(v=vs.85).aspx

class Semaphore : public Object
{
private:

	HANDLE s;

	//define constants
	CONST int LockTime= 1000;
	CONST long MaxCount =10;
	CONST long InitCount =0;
	//the amount to increment semaphore
	CONST long IncCount = 1;

public:
	RTTI_MACRO(Semaphore);

	Semaphore(int, LPCTSTR);
	~Semaphore();

	void signal();
	void wait(int);
	bool check();
};

