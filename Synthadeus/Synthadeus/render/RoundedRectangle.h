#pragma once
#include "Renderable.h"
#include "Rectangle2.h"
class RoundedRectangle : public Rectangle2
{
private:
	float xRadius;
	float yRadius;
public:
	RoundedRectangle(Point X, Point Y, unsigned int lineColor, unsigned int bkgColor, float XRadius, float YRadius);
	virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette);
	virtual Point getOrigin();
};

