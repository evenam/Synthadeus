#pragma once
#include "Vector2D.h"
#include "Renderable.h"

class Rectangle2 : public Renderable
{
protected:
	Point x;
	Point y;
	unsigned int lineColor;
	unsigned int bkgColor;
public:
	Rectangle2(Point X, Point Y, unsigned int lineCol, unsigned int bkgCol);
	virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette);
	virtual Point getOrigin();
};

