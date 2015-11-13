#pragma once

#include "Renderable.h"
#include "Vector2D.h"

class BackgroundGrid : public Renderable
{
private:
	// grid variables
	Point gridOrigin, gridSize, gridCellSize;
	unsigned int gridColor, gridBackground;
public:
	RTTI_MACRO(BackgroundGrid);

	// initialize the grid
	BackgroundGrid(Point origin, Point size, Point cellSize, unsigned int lineColor, unsigned int bgkColor);

	// overrides from renderable
	virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette);
	virtual Point getOrigin();
};

