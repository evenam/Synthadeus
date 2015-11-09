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

// global constanst
#define PI  3.1415927f
#define E   2.7182818f
#define PHI 1.6180340f

namespace CFMathsHelpers
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

	template<> struct __factorial_templ<1>
	{
		static inline float val()
		{
			return 1.f;
		}
	};

	float __fast_sin(float t);
	float __fast_cos(float t);
	float __fast_abs(float t);
	void __inplace_swap(float& f1, float& f2);
	float __regular_factorial(float x);
}

#define sinf(x) (CFMathsHelpers::__fast_sin(x))
#define cosf(x) (CFMathsHelpers::__fast_cos(x))
#define absf(x) (CFMathsHelpers::__fast_abs(x))
#define swapf(x, y) (CFMathsHelpers::__inplace_swap(x, y))
#define factf(x) (CFMathsHelpers::__regular_factorial(x))
#define CONST_FACTORIAL(a) CFMathsHelpers::__factorial_templ<(a)>::val();

#define sinl(x) (CFMathsHelpers::__lookup_sin(x))
#define cosl(x) (CFMathsHelpers::__lookup_sin(x))
#define asinl(x) (CFMathsHelpers::__lookup_sin(x))
#define acosl(x) (CFMathsHelpers::__lookup_sin(x))
