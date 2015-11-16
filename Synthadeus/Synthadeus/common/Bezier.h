////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   N-Point Bezier Curve Mat                                                 //
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

template <int N> class Bezier
{
private:
	Point pointList[N];
	float coefList[N];
	float minX, minY, maxX, maxY;

	inline void initializeDefault()
	{
		// zero points, generate binomial coefficients
		int halfN = N / 2 + (N % 2);
		assert(halfN >= N / 2);
		minX = minY = maxX = maxY = 0.f;
		for (int i = 1; i <= halfN; i++)
		{
			coefList[i - 1] = coefList[N - i] = CFMaths::__factorial_templ<N - 1>::val() / (rfactf((float)(i - 1)) * rfactf((float)(N - i)));
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

	inline void calculateMinMax()
	{
		minX = maxX = pointList[0].x;
		minY = maxY = pointList[0].y;
		for (int i = 1; i < N; i++)
		{
			if (pointList[i].x < minX) minX = pointList[i].x;
			if (pointList[i].y < minY) minY = pointList[i].y;
			if (pointList[i].x > maxX) maxX = pointList[i].x;
			if (pointList[i].y > maxY) maxY = pointList[i].y;
		}
		assert(minX < maxX);
		assert(minY < maxY);
	}

public:
	RTTI_MACRO(Bezier);

	inline Bezier() { initializeDefault(); }
	inline Bezier(Point first = Point(), ...)
	{
		initializeDefault();
		assert(N > 0);
		va_list vl;
		int num = N;
		minX = minY = pointList[0].x = first.x;
		maxX = maxY = pointList[0].y = first.y;
		va_start(vl, first);
		for (int i = 1; i < N; i++)
		{
			pointList[i] = *(Point*)&va_arg(vl, Vector2D);
		}
		va_end(vl);
		calculateMinMax();
	}

	// calculate bezier
	inline float getX(float t) { Point p = bezierForm(t); return p.x; }
	inline float getY(float t) { Point p = bezierForm(t); return p.y; }
	inline float get(float t) { return bezierForm(t); }
	inline const Point& operator[](float t) const { return bezierForm(t); }

	inline float getMinX() { return minX; }
	inline float getMaxX() { return maxX; }
	inline float getMinY() { return minY; }
	inline float getMaxY() { return maxY; }

	// datapoint manipulation
	inline void setPoint(int point, Point p) { assert(point >= 0); assert(point < N); pointList[point] = p; calculateMinMax(); }
	inline Point& getPoint(int point) { assert(point >= 0); assert(point < N); return pointList[point]; calculateMinMax(); }
};
