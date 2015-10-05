////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   A 2D Vector                                                              //
//   Everett Moser                                                            //
//   9-12-15                                                                  //
//                                                                            //
//   Definitions for a 2D vector with dot, cross, and handy operators         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Error.h"
#include "Object.h"

#define VECTOR_SIZE 2

class Vector2D : public Object
{
private:
	// actual data
	float elem[VECTOR_SIZE];

public:
	RTTI_MACRO(Vector2D);

	float &x, &y;

	Vector2D(float pX = 0.f, float pY = 0.f);

	// designed to make sense
	const float& operator[] (int item) const;
	float& operator[] (int item);

	// handy dandy vector math
	static float dot(const Vector2D& v1, const Vector2D& v2);
	static float cross(const Vector2D& v1, const Vector2D& v2);

	Vector2D& operator= (const Vector2D& v);
	Vector2D& operator*= (const float c);
	Vector2D& operator+= (const Vector2D& v);
	Vector2D& operator-= (const Vector2D& v);
};

Vector2D operator* (const float c, const Vector2D& v);
Vector2D operator+ (const Vector2D& v1, const Vector2D& v2);
Vector2D operator- (const Vector2D& v1, const Vector2D& v2);

typedef Vector2D Point;
