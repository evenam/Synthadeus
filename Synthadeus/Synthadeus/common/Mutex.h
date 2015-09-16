#pragma once

#include <Windows.h>
#include "Object.h"

// Basic mutex lock skeleton
// see https://msdn.microsoft.com/en-us/library/windows/desktop/ms684266(v=vs.85).aspx

class Mutex : public Object
{
private:


public:
	RTTI_MACRO(Mutex);

	Mutex();
	~Mutex();

	void lock();
	void unlock();
	bool check();
};

