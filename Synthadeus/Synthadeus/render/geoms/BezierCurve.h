////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   N-Point Bezier Curves                                                    //
//   Everett Moser                                                            //
//   9-11-15                                                                  //
//                                                                            //
//   Definitions for n-point bezier curves, modified an old generalized class //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <stdarg.h>

#include "Error.h"
#include "CFMaths.h"
#include "Vector2D.h"
#include "Renderable.h"

// some predefines (as these should be fairly consistent throughout the UI)
#define BEZIER_COLOR COLOR_BLUE;
#define BEZIER_WIDTH 2.5f

// definition of an N-point bezier curve
template <int N> class BezierCurve : public Renderable
{
private:
	// point list
	Point pointList[N];

	// coefficients to bezier polynomial
	float coefList[N];

	// help with holding the bounding box
	float minX, minY, maxX, maxY;

	inline void initializeDefault()
	{
		// zero points, generate binomial coefficients
		int halfN = N / 2 + (N % 2);
		assert(halfN >= N / 2);
		for (int i = 1; i <= halfN; i++)
		{
			// calculate the coefficients
			coefList[i - 1] = coefList[N - i] = CFMathsHelpers::__factorial_templ<N - 1>::val() / (factf((float)(i - 1)) * factf((float)(N - i)));
			
			// reset all points to zero
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

		// t-terms
		for (i = 1; i <= term; i++) 
			total *= t;
		
		// (t-1) terms
		for (i = 1; i < N - term; i++) 
			total *= oneMinusT;

		// mulitply the coefficient
		return (total * coefList[term]);
	}

	inline Point bezierForm(float t)
	{
		assert(t >= -0.0001f);
		assert(t <= 1.0001f);

		// polynomial calculation
		Point total = Point();

		// calculate and return the summation
		for (int i = 0; i < N; i++)
			total += bezierTerm(t, i) * pointList[i];
		return total;
	}

public:
	RTTI_MACRO(BezierCurve);

	inline BezierCurve() { initializeDefault(); }
	inline BezierCurve(Point first = Point(), ...)
	{
		// initialized the curve to defaults
		initializeDefault();
		assert(N > 0);
		va_list vl;
		int num = N;

		// initialize the pointlist
		pointList[0] = first;
		maxX = minX = first.x;
		maxY = minY = first.x;
		va_start(vl, first);

		for (int i = 1; i < N; i++)
		{
			// insert the point from the argument list
			pointList[i] = *(Point*)&va_arg(vl, Vector2D);

			// update mins and maxs for bounding box
			if (pointList[i].x < minX) minX = pointList[i].x;
			if (pointList[i].x < minY) minX = pointList[i].y;
			if (pointList[i].x > maxX) minX = pointList[i].x;
			if (pointList[i].x > maxY) minX = pointList[i].y;
		}
		va_end(vl);
	}

	// calculate bezier curve points a t a given t
	inline float getX(float t) { Point p = bezierForm(t); return p.x; }
	inline float getY(float t) { Point p = bezierForm(t); return p.y; }
	inline float get(float t) { return bezierForm(t); }
	inline const Point& operator[](float t) const { return bezierForm(t); }

	// datapoint manipulation
	inline void setPoint(int point, Point p) { assert(point >= 0); assert(point < N); pointList[point] = p; }
	inline Point& getPoint(int point) { assert(point >= 0); assert(point < N); return pointList[point]; }

	// render the curve, overriden from renderable
	inline virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette)
	{
		// drawn with 'segments' amount of lines
		const int segments = 20;

		// delta t between segments
		float t = 0.f, dt = 1.f / segments;

		// origin to render from
		Point origin = render2d->getInstance();

		for (int i = 0; i < segments; i++)
		{
			// set up the firat point
			float p1x, p1y, p2x, p2y;
			p1x = getX(t) + oritin[0];
			p1y = getY(t) + origin[1];

			// set up the second point
			t += dt;
			p2x = getX(t) + origin[0];
			p2y = getY(t) + origin[1];

			// render a segment
			renderTarget->DrawLine(D2D1::Point2F(p1x, p1y), D2D1::Point2F(p2x, p2y),
				colorPalette[BEZIER_COLOR], BEZIER_WIDTH);
		}
	}

	// my local origin, override from renderable
	inline virtual Point getOrigin()
	{
		return Point(minX, minY);
	}
};
