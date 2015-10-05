////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   N-Point Bezier Curves                                                    //
//   Everett Moser                                                            //
//   9-11-15                                                                  //
//                                                                            //
//   Definitions for n-point bezier curves and niceties relating to them      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Error.h"
#include "CFMaths.h"
#include "Vector2D.h"
#include <stdarg.h>
#include "Object.h"

template <int N> class BezierCurve : public Object
{
private:
	Point pointList[N];
	float coefList[N];

	inline void initializeDefault()
	{
		// zero points, generate binomial coefficients
		int halfN = N / 2 + (N % 2);
		assert(halfN >= N / 2);
		for (int i = 1; i <= halfN; i++)
		{
			coefList[i - 1] = coefList[N - i] = CFMathsHelpers::__factorial_templ<N - 1>::val() / (factf((float)(i - 1)) * factf((float)(N - i)));
			pointList[i - 1].x = pointList[i - 1].y = pointList[N - i].x = pointList[N - i].y = 0.f;
		}
	}

	inline float bezierTerm(float t, int term)
	{
		assert(term >= 0);
		assert(term < N);

		// calculate the binomial
		float oneMinusT = 1.f - t;
		float total = 1.f;
		int i = 0;
		for (i = 1; i <= term; i++) 
			total *= t;
		for (i = 1; i < N - term; i++) 
			total *= oneMinusT;

		// mulitplu coefficient
		return (total * coefList[term]);
	}

	inline Point bezierForm(float t)
	{
		assert(t >= -0.0001f);
		assert(t <= 1.0001f);

		// polynomial calculation
		Point total = Point();
		for (int i = 0; i < N; i++)
			total += bezierTerm(t, i) * pointList[i];
		return total;
	}

public:
	RTTI_MACRO(BezierCurve);

	inline BezierCurve() { initializeDefault(); }
	inline BezierCurve(Point first = Point(), ...)
	{
		initializeDefault();
		assert(N > 0);
		va_list vl;
		int num = N;
		pointList[0] = first;
		va_start(vl, first);
		for (int i = 1; i < N; i++)
			pointList[i] = *(Point*)&va_arg(vl, Vector2D);
		va_end(vl);
	}

	// calculate bezier
	inline float getX(float t) { Point p = bezierForm(t); return p.x; }
	inline float getY(float t) { Point p = bezierForm(t); return p.y; }
	inline float get(float t) { return bezierForm(t); }
	inline const Point& operator[](float t) const { return bezierForm(t); }

	// datapoint manipulation
	inline void setPoint(int point, Point p) { assert(point >= 0); assert(point < N); pointList[point] = p; }
	inline Point& getPoint(int point) { assert(point >= 0); assert(point < N); return pointList[point]; }
};
