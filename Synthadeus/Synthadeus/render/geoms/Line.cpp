#include "Line.h"

Line::Line(Point startPoint, Point endPoint, unsigned int lineColor, int lineWidth)
{
	point1[0] = startPoint[0];
	point1[1] = startPoint[1];
	point2[0] = endPoint[0];
	point2[1] = endPoint[1];
	color = lineColor;
	width = lineWidth;
}

void Line::render(Render2D* render2d, ID2D1HwndRenderTarget * renderTarget, ID2D1SolidColorBrush ** colorPalette, IDWriteTextFormat** fontPalette)
{
	// calculate render area based on origin and viewport
	Point instanceOrigin = render2d->getInstance();
	renderTarget->DrawLine(D2D1::Point2F(point1[0] + instanceOrigin[0], point1[1] + instanceOrigin[1]),
						   D2D1::Point2F(point2[0] + instanceOrigin[0], point2[1] + instanceOrigin[1]), colorPalette[color], width);
}

Point Line::getOrigin()
{
	// treat the start point as the origin
	return point1;
}
