#include "RoundedRectangle.h"



RoundedRectangle::RoundedRectangle(Point origin, Point size, unsigned int lineColor, unsigned int bkgColor, float XRadius, float YRadius) 
	: Rectangle2(origin, size, lineColor, bkgColor)
{
	xRadius = XRadius;
	yRadius = YRadius;
}


void RoundedRectangle::render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette)
{
	Point instanceOrigin = render2d->getInstance();
	const float lineWidth = 1.5f;
	renderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(origin[0] + instanceOrigin[0], origin[1] + instanceOrigin[1],
		origin[0] + size[0] + instanceOrigin[0], origin[1] + size[1] + instanceOrigin[1]), xRadius, yRadius), colorPalette[bkgColor]);
	renderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(origin[0] + instanceOrigin[0], origin[1] + instanceOrigin[1],
		origin[0] + size[0] + instanceOrigin[0], origin[1] + size[1] + instanceOrigin[1]), xRadius, yRadius), colorPalette[lineColor], lineWidth);
}

Point RoundedRectangle::getOrigin()
{
	return origin;
}
