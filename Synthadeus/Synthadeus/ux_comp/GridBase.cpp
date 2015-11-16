#include "GridBase.h"
#include "Renderables.h"

GridBase::GridBase(Point gridOrigin, Point gridSize, unsigned int gridForeground, unsigned int gridBackground) : Component()
{
	origin[0] = gridOrigin[0];
	origin[1] = gridOrigin[1];
	size[0] = gridSize[0];
	size[1] = gridSize[1];
	fgColor = gridForeground;
	bgColor = gridBackground;
	setBoundingRectangle(origin, size);
}

void GridBase::setSize(Point gridOrigin, Point gridSize)
{
	origin[0] = gridOrigin[0];
	origin[1] = gridOrigin[1];
	size[0] = gridSize[0];
	size[1] = gridSize[1];
	setBoundingRectangle(origin, size);
}

void GridBase::mouseEventHandler(Synthadeus* app, Point mousePosition, bool check, bool pressed, bool released)
{
	// nothing
}

void GridBase::update()
{
	// nothing
}

Renderable* GridBase::getRenderList()
{
	return new BackgroundGrid(origin, size, Point(32.f, 32.f), fgColor, bgColor);
}