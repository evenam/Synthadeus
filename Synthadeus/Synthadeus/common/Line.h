#pragma once

#include <Windows.h>
#include "Object.h"



class Line : public Object
{
private:
	float x0;
	float y0;
	float x1;
	float y1;

public:
	Line(float, float, float, float);
	~Line();
};

