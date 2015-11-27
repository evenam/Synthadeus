////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   A base node                                                              //
//   Everett Moser                                                            //
//   11-15-15                                                                 //
//                                                                            //
//   Basically a dragable                                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector2D.h"
#include "Renderables.h"
#include "Component.h"
#include "ButtonBase.h"
#include "InputDevice.h"

class Node : public Component
{
private:
	Point size;
	Point origin;
	unsigned int fgColor;
	unsigned int bgColor;

	float relativeMouseX;
	float relativeMouseY;

	bool removeable;

public:
	RTTI_MACRO(Node);

	Node(Point nodeOrigin, Point nodeSize, unsigned int nodeFgColor, unsigned int nodeBgColor, bool isRemoveable = true);
	void setSize(Point nodeOrigin, Point nodeSize);
	void setColorScheme(unsigned int nodeFgColor, unsigned int nodeBgColor);

	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);
	virtual void update();
	virtual Renderable* getRenderList();

	virtual bool canConnect() { return true; }
};

