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
	Point point1, point2;
	unsigned int color;
	int width;

public:
	Line(Point p1, Point p2, unsigned int lineColor, int lineWidth);
	Line(float x1, float y1, float x2, float y2, unsigned int lineColor, int lineWidth);
	void set(float x1, float y1, float x2, float y2, unsigned int lineColor, int lineWidth);
	Point getPoint1();
	Point getPoint2();
	unsigned int getColor();
	int getWidth();
	virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette);
	virtual Point getOrigin();
};

