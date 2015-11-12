#include "CFMaths.h"

float CFMaths::__radian_bound(float x)
{
	float ret = x;
	ret /= 2.f * PI;
	ret *= 65536.f;
	int i = (int)ret;
	i &= 0xFFFF;
	ret = (float)i;
	ret /= 65536.f;
	ret *= 2.f * PI;
	return ret;
}

// X macro'd taylor series, attempted 6 digit accuracy
float CFMaths::__fast_sin(float t)
{
	// accuracy reduced to 4 digits if radians are out of bounds
	if ((float)((int)t & 0x7FFFFFF) > PI) t = __radian_bound(t);
#define _X(exp) total += sign * acc / __factorial_templ<exp>::val(); sign *= -1; acc *= t_sqr;
	float acc = t * t * t, total = t, t_sqr = t * t;
	int sign = -1;
	_X(3) _X(5) _X(7) _X(9) _X(11) _X(13) _X(15) _X(17);
#undef _X
	return total;
}

// X macro'd taylor series, attempted 6 digit accuracy
float CFMaths::__fast_cos(float t)
{
	// accuracy reduced to 4 digits if radians are out of bounds
	if ((float)((int)t & 0x7FFFFFF) > PI) t = __radian_bound(t);
#define _X(exp) total += sign * acc / __factorial_templ<exp>::val(); sign *= -1; acc *= t_sqr;
	float acc = t * t, total = 1.f, t_sqr = t * t;
	int sign = -1;
	_X(2) _X(4); _X(6) _X(8) _X(10) _X(12) _X(14) _X(16);
#undef _X
	return total;
}

float CFMaths::__fast_abs(float t)
{
	// just unset the sign bit
	float ret = 0.f;
	unsigned int f = *(unsigned int*)&t;
	f &= 0x7FFFFFFF;
	ret = *(float*)&f;
	return ret;
}

void CFMaths::__inplace_swap(float& f1, float& f2)
{
	// xor inplace swap algorithm
	unsigned int n1 = *(unsigned int*)&f1;
	unsigned int n2 = *(unsigned int*)&f2;
	n1 ^= n2;
	n2 ^= n1;
	n1 ^= n2;
	f1 = *(float*)&n1;
	f2 = *(float*)&n2;
}

float CFMaths::__regular_factorial(float x)
{
	// linear-time non-recursive factorial
	float fact = 1.f;
	for (float n = x; n > 1.f; n -= 1.f)
		fact *= n;
	return fact;
}

float CFMaths::__lookup_sin(float radians)
{
	int index = (int)(__radian_bound(radians) * 1000.f);
	return __sinTable[index];
}

void CFMaths::init()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		float radians = (float)i / 1000.f;
		__sinTable[i] = fsinf(radians);
	}
}
