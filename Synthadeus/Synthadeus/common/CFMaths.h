////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Compiler Enhanced Floating Point Math Functions                          //
//   Everett Moser                                                            //
//   8-20-15                                                                  //
//                                                                            //
//   Definitions for fast sinf/cosf/abfs/swapf/factf functions.               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

// global constants
#define PI  3.1415927f
#define TAO 6.2831854f
#define EU  2.7182818f
#define PHI 1.6180340f

namespace CFMaths
{
	// precision constants for helping compute compounded error. 
	const static float __cfepsilon = 0.000001f;
	const static float __cfunboundedepsilon = 0.0001f;

	// quickly (and inaccurately) constrain radians
	float __radian_bound(float x);

	// compile time factorial via templates
	template<int N> struct __factorial_templ
	{
		static inline float val()
		{
			return ((float)N * __factorial_templ<N - 1>::val());
		}
	};

	// base case factorial
	template<> struct __factorial_templ<0>
	{
		static inline float val()
		{
			return 1.f;
		}
	};

	// via taylor series
	float __fast_sin(float t);
	float __fast_cos(float t);

	// via bit twiddling
	float __fast_abs(float t);
	void __inplace_swap(float& f1, float& f2);

	// via loop :(
	float __regular_factorial(float x);

	// power function like the standard library
	float __powf(float b, int e);

	// table size is 4 digit precision radians aka 5 quadrants
	enum { PI_OVER_2 = 1571, TABLE_SIZE = (1571 * 5) };
	extern float __lookupTable[TABLE_SIZE];

	// table queries
	float __lookup_sin(float radians);
	float __lookup_cos(float radians);

	// initialize the lookup tables
	void init();
}

// created to help find math errors
#define USE_CMATH_ALSO
#ifndef USE_CMATH_ALSO
// quick redefines for these functions
#define fsinf(x) (CFMaths::__fast_sin(x))
#define fcosf(x) (CFMaths::__fast_cos(x))
#define fabsf(x) (CFMaths::__fast_abs(x))

#define fpowf(x, y) (CFMaths::__powf(x, y))
#else

// redefine the cmath equivalents
#include <cmath>
#define fsinf sinf
#define fcosf cosf
#define fabsf abs

#define fpowf powf
#endif

// these will always be defined since there are no counterparts
#define iswapf(x, y) (CFMaths::__inplace_swap(x, y))
#define rfactf(x) (CFMaths::__regular_factorial(x))
#define CONST_FACTORIAL(a) CFMaths::__factorial_templ<(a)>::val();
#define lsinf(x) (CFMaths::__lookup_sin(x))
