#pragma once
#include "Rectangle.h"
class RoundedRectangle : public Rectangle
{
private:
	float xRadius;
	float yRadius;
public:
	RoundedRectangle(float x, float y, float xRadius, float yRadius);
	~RoundedRectangle();
};

