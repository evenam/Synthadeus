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

class Node : public Component
{
public:
	Node(Point origin, Point size);
	void setSize(Point origin, Point size);

	inline virtual void mouseEventHandler(Synthadeus* app, Point mousePosition, bool check, bool pressed, bool released) {};
	inline virtual void update() {};
	inline virtual Renderable* getRenderList() { return NULL; };
};

