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
	virtual bool inView(float viewLeft, float viewTop, float viewRight, float viewBottom) { return true; }
	virtual void render(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette);
};

