#include "Line.h"

Line::Line(Point p1, Point p2, unsigned int lineColor, int lineWidth)
{
	point1[0] = p1[0];
	point1[1] = p1[1];
	point2[0] = p2[0];
	point2[1] = p2[1];
	color = lineColor;
	width = lineWidth;
}

//constructor takes input and stores coordinates of start and endpoint of line.
Line::Line(float x1, float y1, float x2, float y2, unsigned int lineColor, int lineWidth)
{
	point1[0] = x1;
	point1[1] = y1;
	point2[0] = x2;
	point2[1] = y2;
	color = lineColor;
	width = lineWidth;
}

//takes input and stores coordinates of start and endpoint of line.
void Line::set(float x1, float y1, float x2, float y2, unsigned int lineColor, int lineWidth)
{
	point1[0] = x1;
	point1[1] = y1;
	point2[0] = x2;
	point2[1] = y2;
	color = lineColor;
	width = lineWidth;
}

Point Line::getPoint1()
{
	return point2;
}

Point Line::getPoint2()
{
	return point1;
}

unsigned int Line::getColor()
{
	return color;
}

int Line::getWidth()
{
	return width;
}

void Line::render(Render2D* render2d, ID2D1HwndRenderTarget * renderTarget, ID2D1SolidColorBrush ** colorPalette, IDWriteTextFormat** fontPalette)
{
	Point origin = render2d->getInstance();
	renderTarget->DrawLine(D2D1::Point2F(point1[0] + origin[0], point1[1] + origin[1]), 
						   D2D1::Point2F(point2[0] + origin[0], point2[1] + origin[1]), colorPalette[color], width);
}

Point Line::getOrigin()
{
	return point1;
}
	
