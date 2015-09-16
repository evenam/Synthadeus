#pragma once

#include <Windows.h>
#include "Object.h"

// Basic semaphore skeleton
// see https://msdn.microsoft.com/en-us/library/windows/desktop/ms685129(v=vs.85).aspx

class Semaphore : public Object
{
private:


public:
	RTTI_MACRO(Semaphore);

	Semaphore();
	~Semaphore();

	void signal();
	void wait();
	bool check();
};

