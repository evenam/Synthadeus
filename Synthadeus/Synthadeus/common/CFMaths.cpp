#include "CFMaths.h"

float CFMaths::__lookupTable[CFMaths::TABLE_SIZE];

// hacky bitwise floating point magic to bind a value between -pi and pi
float CFMaths::__radian_bound(float x)
{
	// get the tao coefficient (tao = 2*pi)
	float ret = x;
	ret /= 2.f * PI;

	// "bit shift" the number, removing the exponent and sign portion
	ret *= 65536.f;

	// extract the decimal between -.5 and .5 which constitues tao ratio
	int i = (int)ret;
	i &= 0xFFFF;
	ret = (float)i;

	// shift back the number, sign follows naturally
	ret /= 65536.f;

	// convert back from tao ratio to radians
	ret *= 2.f * PI;
	return ret;
}

// X macro'd taylor series, attempted 6 digit accuracy
float CFMaths::__fast_sin(float t)
{
	// accuracy reduced to 4 digits if radians are out of bounds
	if ((float)((int)t & 0x7FFFFFF) > PI) t = __radian_bound(t);

	// definition of a taylor series iteration
#define _X(exp) total += sign * acc / __factorial_templ<exp>::val(); sign *= -1; acc *= t_sqr;

	// initial values
	float acc = t * t * t, total = t, t_sqr = t * t;
	int sign = -1;

	// iterate a few times (to 6 digit accuracy)
	_X(3) _X(5) _X(7) _X(9) _X(11) _X(13) _X(15) _X(17);
#undef _X
	return total;
}

// X macro'd taylor series, attempted 6 digit accuracy
float CFMaths::__fast_cos(float t)
{
	// accuracy reduced to 4 digits if radians are out of bounds
	if ((float)((int)t & 0x7FFFFFF) > PI) t = __radian_bound(t);

	// definition of a taylor series iteration
#define _X(exp) total += sign * acc / __factorial_templ<exp>::val(); sign *= -1; acc *= t_sqr;

	// initial values
	float acc = t * t, total = 1.f, t_sqr = t * t;
	int sign = -1;

	// iterate a few times (to 6 digit accuracy)
	_X(2) _X(4) _X(6) _X(8) _X(10) _X(12) _X(14) _X(16);
#undef _X
	return total;
}

float CFMaths::__fast_abs(float t)
{
	// just unset the sign bit
	float ret = 0.f;

	// kinky casting bitlevel magics  (thanks to the IEEE 754 floating point standard)
	unsigned int f = *reinterpret_cast<int*>(&t);

	// and-off the sign bit
	f &= 0x7FFFFFFF;

	// cast back to the float with kinky reinterpret casting
	ret = *reinterpret_cast<float*>(&f);
	return ret;
}

void CFMaths::__inplace_swap(float& f1, float& f2)
{
	// kinky casting to unsigned ints
	unsigned int n1 = *reinterpret_cast<unsigned int*>(&f1);
	unsigned int n2 = *reinterpret_cast<unsigned int*>(&f2);

	// xor inplace swap algorithm
	n1 ^= n2;
	n2 ^= n1;
	n1 ^= n2;

	// kinky casting back to floats
	f1 = *reinterpret_cast<float*>(&n1);
	f2 = *reinterpret_cast<float*>(&n2);
}

float CFMaths::__regular_factorial(float x)
{
	// linear-time non-recursive factorial (woot efficiency, replace with table?)
	float fact = 1.f;
	for (float n = x; n > 1.f; n -= 1.f)
		fact *= n;
	return fact;
}

float CFMaths::__powf(float b, int e)
{
	unsigned int x;
	if (e >= 0)
		x = static_cast<unsigned int>(e);
	else
		x = static_cast<unsigned int>(-e);

	for (float z = 1.f; ; b *= b)
	{
		if ((x & 1) != 0)
			z *= b;
		if ((x >>= 1) == 0)
			return (e < 0 ? 1.f / z : z);
	}
}

float CFMaths::__lookup_sin(float radians)
{
	// convert the radians to a 4 digit number
	int index = (int)(__radian_bound(radians) * 1000.f);

	// look up the value
	return __lookupTable[index];
}

float CFMaths::__lookup_cos(float radians)
{
	// convert the radians to a 4 digit number
	int index = (int)(__radian_bound(radians) * 1000.f);

	// look up the value, offset for sin->cos phase shift
	return __lookupTable[index + PI_OVER_2];
}

void CFMaths::init()
{
	// initialize the table with the appropriate sine values
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		float radians = (float)i / 1000.f;
		__lookupTable[i] = fsinf(radians);
	}
}
