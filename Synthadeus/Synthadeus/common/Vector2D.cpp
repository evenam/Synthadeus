#include "Vector2D.h"

Vector2D::Vector2D(float pX, float pY) : x(elem[0]), y(elem[1]), elem{ pX, pY } 
{
}

const float& Vector2D::operator[] (int item) const 
{ 
	assert(item >= 0 && item < VECTOR_SIZE); 
	return elem[item]; 
}

float& Vector2D::operator[] (int item)
{ 
	assert(item >= 0 && item < VECTOR_SIZE); 
	return elem[item]; 
}

float Vector2D::dot(const Vector2D& v1, const Vector2D& v2) 
{ 
	return (v1[0] * v2[0] + v1[1] * v2[1]); 
}

float Vector2D::cross(const Vector2D& v1, const Vector2D& v2) 
{ 
	return (v1[0] * v2[1] - v2[0] * v1[1]); 
}

Vector2D& Vector2D::operator= (const Vector2D& v)  
{ 
	elem[0] = v[0]; 
	elem[1] = v[1]; 
	return *this; 
}

Vector2D& Vector2D::operator*= (const float c)     
{ 
	elem[0] *= c; 
	elem[1] *= c; 
	return *this; 
}

Vector2D& Vector2D::operator+= (const Vector2D& v) 
{ 
	elem[0] += v[0]; 
	elem[1] += v[1];
	return *this; 
}

Vector2D& Vector2D::operator-= (const Vector2D& v) 
{ 
	elem[0] -= v[0]; 
	elem[1] -= v[1]; 
	return *this; 
}

Vector2D operator* (const float c, const Vector2D& v)
{
	return Vector2D(c * v[0], c * v[1]);
}

Vector2D operator+ (const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1[0] + v2[0], v1[1] + v2[1]);
}

Vector2D operator- (const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1[0] - v2[0], v1[1] - v2[1]);
}