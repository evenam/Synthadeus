#pragma once

#include <Windows.h>
#include "Object.h"

// Basic mutex lock skeleton

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

