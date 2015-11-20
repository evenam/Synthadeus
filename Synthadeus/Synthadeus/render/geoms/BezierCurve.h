////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   N-Point Bezier Curves Renderable                                         //
//   Everett Moser                                                            //
//   11-16-15                                                                 //
//                                                                            //
//   Render an N-point Bezier Curve                                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <stdarg.h>

#include "Error.h"
#include "CFMaths.h"
#include "Vector2D.h"
#include "Renderable.h"
#include "Bezier.h"

// some predefines (as these should be fairly consistent throughout the UI)
#define BEZIER_COLOR COLOR_WHITE
#define BEZIER_WIDTH 2.5f

// definition of an N-point bezier curve
template <int N> class BezierCurve : public Renderable
{
private:
	Bezier<N> thisCurve;

public:
	RTTI_MACRO(BezierCurve);

	inline BezierCurve(Point first = Point(), ...) : thisCurve(Point(0.f, 0.f))
	{
		assert(N > 0);
		va_list vl;
		int num = N;
		va_start(vl, first);
		thisCurve.setPoint(0, first);
		for (int i = 1; i < N; i++)
			thisCurve.setPoint(i,*(Point*)&va_arg(vl, Vector2D));
		va_end(vl);
	};

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
			// set up the first point
			float p1x, p1y, p2x, p2y;
			p1x = thisCurve.getX(t) + origin[0];
			p1y = thisCurve.getY(t) + origin[1];

			// set up the second point
			t += dt;
			p2x = thisCurve.getX(t) + origin[0];
			p2y = thisCurve.getY(t) + origin[1];

			// render a segment
			renderTarget->DrawLine(D2D1::Point2F(p1x, p1y), D2D1::Point2F(p2x, p2y), colorPalette[BEZIER_COLOR], BEZIER_WIDTH);
		}
	}

	// my local origin, override from renderable
	inline virtual Point getOrigin()
	{
		return Point(thisCurve.getMinX(), thisCurve.getMinY());
	}
};
