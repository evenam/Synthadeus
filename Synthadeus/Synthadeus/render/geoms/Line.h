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
	// position
	Point point1, point2;

	// color
	unsigned int color;

	// linewidth
	int width;

public:

	// run time type information
	RTTI_MACRO(Line);

	// set up the line
	Line(Point startPoint, Point endPoint, unsigned int lineColor, int lineWidth);

	// the ID2D calls
	virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette);
	
	// my current origin
	virtual Point getOrigin();
};

