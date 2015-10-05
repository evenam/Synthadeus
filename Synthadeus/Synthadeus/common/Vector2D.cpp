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
	return (v1.x * v2.x + v1.y * v2.y); 
}

float Vector2D::cross(const Vector2D& v1, const Vector2D& v2) 
{ 
	return (v1.x * v2.y - v2.x * v1.y); 
}

Vector2D& Vector2D::operator= (const Vector2D& v)  
{ 
	x = v.x; 
	y = v.y; 
	return *this; 
}

Vector2D& Vector2D::operator*= (const float c)     
{ 
	x *= c; 
	y *= c; 
	return *this; 
}

Vector2D& Vector2D::operator+= (const Vector2D& v) 
{ 
	x += v.x; 
	y += v.y;
	return *this; 
}

Vector2D& Vector2D::operator-= (const Vector2D& v) 
{ 
	x -= v.x; 
	y -= v.y; 
	return *this; 
}

Vector2D operator* (const float c, const Vector2D& v)
{
	return Vector2D(c * v.x, c * v.y);
}

Vector2D operator+ (const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

Vector2D operator- (const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x - v2.x, v1.y - v2.y);
}