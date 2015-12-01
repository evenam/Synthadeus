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

// base node class
class Node : public Component
{
private:

	// size and location
	Point size;
	Point origin;

	// color scheme
	unsigned int fgColor;
	unsigned int bgColor;

	// relative mouse position to assist with dragging
	float relativeMouseX;
	float relativeMouseY;

	// if false, the node cannot be deleted by right clicking
	bool removeable;

public:

	// run time type information
	RTTI_MACRO(Node);

	// create a node with a size and color scheme
	Node(Point nodeOrigin, Point nodeSize, unsigned int nodeFgColor, unsigned int nodeBgColor, bool isRemoveable = true);
	
	// set the size of the node
	void setSize(Point nodeOrigin, Point nodeSize);

	// update the color scheme
	void setColorScheme(unsigned int nodeFgColor, unsigned int nodeBgColor);

	// handle the mouse events to allow for dragging
	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);

	// update the node every frame
	virtual void update();

	// generate the render list for this graph node
	virtual Renderable* getRenderList();

	// TODO: implement the graph traversal to maintain DAG status
	virtual bool canConnect() { return true; }
};

