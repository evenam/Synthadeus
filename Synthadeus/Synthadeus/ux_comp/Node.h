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

class Node : public Component
{
private:
	ButtonBase btnLogicUnit;
	Point size;
	Point origin;


public:
	Node(Point origin, Point size);
	void setSize(Point origin, Point size);

	virtual void mouseEventHandler(Synthadeus* app, Point mousePosition, bool check, bool pressed, bool released);
	virtual void update();
	virtual Renderable* getRenderList();
};

