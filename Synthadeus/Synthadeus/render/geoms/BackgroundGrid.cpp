#include "BackgroundGrid.h"

BackgroundGrid::BackgroundGrid(Point origin, Point size, Point cellSize, unsigned int lineColor, unsigned int bkgColor)
	: gridOrigin(origin), gridSize(size), gridCellSize(cellSize), gridColor(lineColor), gridBackground(bkgColor)
{
	gridOrigin.x = origin.x;
	gridOrigin.y = origin.y;
	gridSize.x = size.x;
	gridSize.y = size.y;
	gridCellSize.x = cellSize.x;
	gridCellSize.y = cellSize.y;
}

void BackgroundGrid::render(Render2D* render2d, ID2D1HwndRenderTarget * renderTarget, ID2D1SolidColorBrush ** colorPalette, IDWriteTextFormat** fontPalette)
{
	// fill background
	float p1x, p1y, p2x, p2y;
	Point instanceOrigin = render2d->getInstance();
	p1x = gridOrigin[0] + instanceOrigin[0];
	p1y = gridOrigin[1] + instanceOrigin[1];
	p2x = gridOrigin[0] + gridSize[0] + instanceOrigin[0];
	p2y = gridOrigin[1] + gridSize[1] + instanceOrigin[1];
	renderTarget->FillRectangle(D2D1::RectF(p1x, p1y, p2x, p2y), colorPalette[gridBackground]);

	// vertical lines
	for (int i = gridCellSize[0]; i < gridSize[0]; i += gridCellSize[0])
	{
		p1x = gridOrigin[0] + (float)i + instanceOrigin[0]; p2x = gridOrigin[0] +    (float)i + instanceOrigin[0];
		p1y = gridOrigin[1]            + instanceOrigin[1]; p2y = gridOrigin[1] + gridSize[1] + instanceOrigin[1];
		renderTarget->DrawLine(D2D1::Point2F(p1x, p1y),
			D2D1::Point2F(p2x, p2y), colorPalette[gridColor], 0.5f);
	}

	// horizontal lines
	for (int j = gridCellSize[1]; j < gridSize[1]; j += gridCellSize[1])
	{
		p1y = (float)j + gridOrigin[1] + instanceOrigin[1]; p2y =      (float)j + gridOrigin[1]  + instanceOrigin[1];
		p1x = gridOrigin[0]            + instanceOrigin[0]; p2x = gridOrigin[0] + gridSize[0]    + instanceOrigin[0];
		renderTarget->DrawLine(D2D1::Point2F(p1x, p1y),
			D2D1::Point2F(p2x, p2y), colorPalette[gridColor], 0.5f);
	}
}

Point BackgroundGrid::getOrigin()
{
	return gridOrigin;
}
