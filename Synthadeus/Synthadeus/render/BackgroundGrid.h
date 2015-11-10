#pragma once
#include "Renderable.h"
#include "Vector2D.h"

class BackgroundGrid : public Renderable
{
private:
	Point gridOrigin, gridSize, gridCellSize;
	unsigned int gridColor, gridBackground;
public:
	BackgroundGrid(Point origin, Point size, Point cellSize, unsigned int lineColor, unsigned int bgkColor);
	void setSize(Point origin, Point size, Point cellSize);
	void setColor(unsigned int lineColor, unsigned int bkgColor);
	virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette);
	virtual Point getOrigin();
};

