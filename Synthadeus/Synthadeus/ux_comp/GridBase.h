////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Base Grid for Main View                                                  //
//   Everett Moser                                                            //
//   11-10-15                                                                 //
//                                                                            //
//   Draws a grid which serves as the base component in the tree              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Component.h"

class CommandMenu;
class GridBase : public Component
{
private:

	// position and size
	Point origin;
	Point size;

	// color
	unsigned int fgColor;
	unsigned int bgColor;

	// menu which may need deleting at some point
	CommandMenu* menu;

public:

	// runtime type information
	RTTI_MACRO(GridBase);

	// construct a grid, just like the renderable
	GridBase(Point gridOrigin, Point gridSize, unsigned int gridForeground, unsigned int gridBackground);

	// adjust the size
	void setSize(Point gridOrigin, Point gridSize);

	// handle a mouse event, which could make a menu
	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);

	// the update cycle function
	virtual void update();

	// generate the overall render list for all components, since this is the base
	virtual Renderable* getRenderList();
};

