#include "GridBase.h"
#include "Renderables.h"
#include "CommandMenu.h"
//grid components 
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
//sets grid sizes 
void GridBase::setSize(Point gridOrigin, Point gridSize)
{
	origin[0] = gridOrigin[0];
	origin[1] = gridOrigin[1];
	size[0] = gridSize[0];
	size[1] = gridSize[1];
	setBoundingRectangle(origin, size);
	menu = NULL;
}
//handles mouse events 
void GridBase::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
	if (menu)
	{
		if (vMouse->right.checkReleased() || vMouse->left.checkReleased())
		{
			menu->signalRemoval();
			menu = NULL;
		}
	}
	if (vMouse->right.checkReleased() && (menu == NULL))
	{
		vMouse->instance(origin);
		assert(menu == NULL);
		menu = new CommandMenu(vMouse->instancePosition());
		vMouse->restore();
		addChild(menu);
		vMouse->right.debounce();
	}
}

void GridBase::update()
{
	// nothing
}
//render list for components
Renderable* GridBase::getRenderList()
{
	return new BackgroundGrid(origin, size, Point(32.f, 32.f), fgColor, bgColor);
}
