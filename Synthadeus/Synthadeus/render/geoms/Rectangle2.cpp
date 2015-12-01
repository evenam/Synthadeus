#include "Rectangle2.h"

// creates rectangle object
Rectangle2::Rectangle2(Point rectOrigin, Point rectSize, unsigned int lineCol, unsigned int bkgCol)
{
	origin[0] = rectOrigin[0];
	origin[1] = rectOrigin[1];
	size[0] = rectSize[0];
	size[1] = rectSize[1];
	lineColor = lineCol;
	bkgColor = bkgCol;
}

// renders rectangle object
void Rectangle2::render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette)
{
	Point instanceOrigin = render2d->getInstance();
	const float lineWidth = 1.5f;
	renderTarget->FillRectangle(D2D1::RectF(origin[0] + instanceOrigin[0], origin[1] + instanceOrigin[1], origin[0] + size[0] + instanceOrigin[0], origin[1] + size[1] + instanceOrigin[1]), colorPalette[bkgColor]);
	renderTarget->DrawRectangle(D2D1::RectF(origin[0] + instanceOrigin[0], origin[1] + instanceOrigin[1], origin[0] + size[0] + instanceOrigin[0], origin[1] + size[1] + instanceOrigin[1]), colorPalette[lineColor], lineWidth);
}

Point Rectangle2::getOrigin()
{
	return origin;
}
