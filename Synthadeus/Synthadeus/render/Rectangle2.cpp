#include "Rectangle2.h"

Rectangle2::Rectangle2(Point X, Point Y, unsigned int lineCol, unsigned int bkgCol)
{
	x[0] = X[0];
	x[1] = X[1];
	y[0] = Y[0];
	y[1] = Y[1];
	lineColor = lineCol;
	bkgColor = bkgCol;
}

void Rectangle2::render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette)
{
	Point origin = render2d->getInstance();
	renderTarget->FillRectangle(D2D1::RectF(x[0] + origin[0], x[1] + origin[1], y[0] + origin[0], y[1] + origin[1]), colorPalette[bkgColor]);
	renderTarget->DrawRectangle(D2D1::RectF(x[0] + origin[0], x[1] + origin[1], y[0] + origin[0], y[1] + origin[1]), colorPalette[lineColor], 1.5f);
}

Point Rectangle2::getOrigin()
{
	return x;
}
