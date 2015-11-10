#include "RoundedRectangle.h"



RoundedRectangle::RoundedRectangle(Point X, Point Y, unsigned int lineColor, unsigned int bkgColor, float XRadius, float YRadius) : Rectangle2(X, Y, lineColor, bkgColor)
{
	xRadius = XRadius;
	yRadius = YRadius;
}


void RoundedRectangle::render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette)
{
	Point origin = render2d->getInstance();
	renderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x[0] + origin[0], x[1] + origin[1], 
		y[0] + origin[0], y[1] + origin[1]), xRadius, yRadius), colorPalette[bkgColor]);
	renderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x[0] + origin[0], x[1] + origin[1], 
		y[0] + origin[0], y[1] + origin[1]), xRadius, yRadius), colorPalette[lineColor], 1.5f);
}

Point RoundedRectangle::getOrigin()
{
	return x;
}
