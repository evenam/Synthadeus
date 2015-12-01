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
	// actual element data
	float elem[VECTOR_SIZE];

public:
	RTTI_MACRO(Vector2D);

	// pointers to the elements
	// TODO: look into why these may or may not be assigned correctly
	float &x, &y;

	// define the X and Y 
	Vector2D(float pX = 0.f, float pY = 0.f);

	// array style element access (const)
	const float& operator[] (int item) const;

	// array style element access (mutable)
	float& operator[] (int item);

	// standard 2D vector dot product
	static float dot(const Vector2D& v1, const Vector2D& v2);

	// standard 2D vector cross product
	static float cross(const Vector2D& v1, const Vector2D& v2);

	// assignment
	Vector2D& operator= (const Vector2D& v);

	// multiplication assignment by a constant
	Vector2D& operator*= (const float c);

	// addition assignment by a constant
	Vector2D& operator+= (const Vector2D& v);

	// subtraction assignment by a constant
	Vector2D& operator-= (const Vector2D& v);
};

// constant multiplication
Vector2D operator* (const float c, const Vector2D& v);

// vector component addition
Vector2D operator+ (const Vector2D& v1, const Vector2D& v2);

// vector component subtraction
Vector2D operator- (const Vector2D& v1, const Vector2D& v2);

// make vectors and points equivalent
typedef Vector2D Point;
