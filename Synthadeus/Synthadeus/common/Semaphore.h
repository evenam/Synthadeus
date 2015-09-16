#pragma once

#include <Windows.h>
#include "Object.h"

// Basic semaphore skeleton

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

