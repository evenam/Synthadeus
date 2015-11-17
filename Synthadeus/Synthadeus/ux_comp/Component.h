////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   An inteface for interactable components                                  //
//   Everett Moser                                                            //
//   11-10-15                                                                 //
//                                                                            //
//   This provides a way to build component trees                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Object.h"
#include "Vector2D.h"
#include "Renderable.h"
#include "InputDevice.h"

#define COMPONENT_MAX_CHILDREN 16

class Synthadeus;
class Component : public Object
{
private:
	// bounding rectangle
	Point origin, size;

	// sub-components
	Component* children[COMPONENT_MAX_CHILDREN];
	int numChildren;

	inline Component* handleCurrentlyInteracting(Synthadeus* app, InputDevice::Mouse* vMouse)
	{
		if (interacting)
		{
			mouseEventHandler(app, vMouse);
			return this;
		}

		for (int i = 0; i < numChildren; i++)
		{
			vMouse->instance(origin);
			Component* temporary = children[i]->handleCurrentlyInteracting(app, vMouse);
			vMouse->restore();
			if (temporary) return temporary;
		}
		return NULL;
	}

	inline Component* getComponentAtPoint(Point pt)
	{
		assert(!"implement this this " __FUNCSIG__);
	}

protected:
	// set the bounds of this component
	inline void setBoundingRectangle(Point rectOrigin, Point rectSize)
	{
		// origin point
		origin[0] = rectOrigin[0];
		origin[1] = rectOrigin[1];

		// size
		size[0] = rectSize[0];
		size[1] = rectSize[1];
	}

	// are we interacting with input?
	bool interacting;

public:
	inline Component() { numChildren = 0; interacting = false; }
	inline virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse) {};
	inline virtual void update() {};
	inline virtual Renderable* getRenderList() { return NULL; };

	// depth first event handling
	inline bool handleMouseInput(Synthadeus* app, InputDevice::Mouse* vMouse)
	{
		// interact with the current object, if one
		Component* currentlyInteracting = NULL;
		if (currentlyInteracting = handleCurrentlyInteracting(app, vMouse))
			return true;

		// if the mouse isn't over us, we do not care
		if (!rectanglePointCollisionCheck(vMouse->instancePosition(), origin, size)) return false;

		// see if a child needs to handle this event
		for (int i = numChildren - 1; i >= 0; i--)
		{

			// the event was handled
			vMouse->instance(origin);
			bool handled = (children[i]->handleMouseInput(app, vMouse));
			vMouse->restore();
			if (handled) return true;
		}

		// no child has handled the event, handle it ourselves
		mouseEventHandler(app, vMouse);
		return true;
	}
	
	inline static bool rectanglePointCollisionCheck(Point point, Point rectOrigin, Point rectSize)
	{
		// determine the relative mouse point to the collision rectangle
		Point relativePoint(point[0] - rectOrigin[0], point[1] - rectOrigin[1]);
		
		// separated axis check
		if (relativePoint[0] < 0.f) return false;
		if (relativePoint[1] < 0.f) return false;
		if (relativePoint[0] > rectSize[0]) return false;
		if (relativePoint[1] > rectSize[1]) return false;

		// all axes are good, collision occured
		return true;
	}

	// get the index-th child
	inline Component* child(int index)
	{
		return children[index];
	}

	inline int addChild(Component* child)
	{
		// return the child index if it is already a child of this component
		for (int i = 0; i < numChildren; i++)
		{
			// component found
			if (children[i] == child)
				return i;
		}
		
		// insert the child and return the index
		children[numChildren] = child;
		return numChildren++;
	}

	inline void removeChild(Component* child)
	{
		// check all of the children
		for (int i = 0; i < numChildren; i++)
		{
			// child has been found
			if (children[i] == child)
			{
				// remove it, called responsible for managing memory
				for (int j = i; j < numChildren - 1; j++)
				{
					children[j] = children[j + 1];
				}

				// item removed, no need to continue as adding a child will not have duplicates
				numChildren--;
				return;
			}
		}
	}

	inline void removeChild(int index)
	{
		// remove the child at the index, called responsible for managing memory
		// much quicker because we do not need to search for the component
		for (int j = index; j < numChildren - 1; j++)
		{
			children[j] = children[j + 1];
		}
		numChildren--;
	}

	// return whether we are currently interacting with the input system
	inline bool isInteracting()
	{
		return interacting;
	}

	inline Renderable* getRenderTree()
	{
		Renderable* thisList = getRenderList();
		Renderable* thisChildList = NULL;
		Renderable* realCurrent = NULL;
		for (int i = 0; i < numChildren; i++)
		{
			Renderable* current = children[i]->getRenderTree();
			if (i == 0)
			{
				thisChildList = current;
				realCurrent = current;
			}
			else
			{
				while (realCurrent->next != NULL)
					realCurrent = realCurrent->next;
				realCurrent->next = current;
			}
		}

		thisList->child = thisChildList;
		return thisList;
	}

	inline void updateTree()
	{
		update();
		for (int i = 0; i < numChildren; i++)
			children[i]->updateTree();
	}
};