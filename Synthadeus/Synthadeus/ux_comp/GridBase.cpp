#include "GridBase.h"
#include "Renderables.h"
#include "CommandMenu.h"
//grid components 
GridBase::GridBase(Point gridOrigin, Point gridSize, unsigned int gridForeground, unsigned int gridBackground) : Component()
{
	//Creates the background grid
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
	//Sets the gridbase size
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
	//Mouse event Handler for the right-click Menu
	
	//Checks if menu exists, if it does then we check if left or right mouse button was pressed.
	//If it is, then the menu is removed.
	if (menu)
	{
		if (vMouse->right.checkReleased() || vMouse->left.checkReleased())
		{
			menu->signalRemoval();
			menu = NULL;
		}
	}
	
	//If menu doesn't exist and right mouse button is pressed, create a new menu.
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
	//Returns a linked list of renderables
	return new BackgroundGrid(origin, size, Point(32.f, 32.f), fgColor, bgColor);
}
