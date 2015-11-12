////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Line																      //
//   James Bellard                                                            //
//   9-27-15                                                                  //
//                                                                            //
//   Stores the 2 points of a line data and draws the line on the screen.	  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Renderable.h"
#include "Vector2D.h"

class Line : public Renderable
{
private:
	// line data
	Point point1, point2;
	unsigned int color;
	int width;

public:
	// set up the line
	Line(Point startPoint, Point endPoint, unsigned int lineColor, int lineWidth);

	// overrides from renderable
	virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette);
	virtual Point getOrigin();
};

