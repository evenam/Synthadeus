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

class GridBase : public Component
{
private:
	Point origin;
	Point size;
	unsigned int fgColor;
	unsigned int bgColor;

public:
	RTTI_MACRO(GridBase);

	GridBase(Point gridOrigin, Point gridSize, unsigned int gridForeground, unsigned int gridBackground);
	void setSize(Point gridOrigin, Point gridSize);

	virtual void mouseEventHandler(Synthadeus* app, Point mousePosition, bool check, bool pressed, bool released);
	virtual void update();
	virtual Renderable* getRenderList();
};

