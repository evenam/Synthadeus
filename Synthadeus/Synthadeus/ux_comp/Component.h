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

#define COMPONENT_MAX_CHILDREN 16

class Component : public Object
{
private:
	// bounding rectangle
	Point origin, size;

	// sub-components
	Component* children[COMPONENT_MAX_CHILDREN];
	int numChildren;

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
	virtual void onMouseInput(void* TBD, Point mousePosition, bool check, bool pressed, bool released) = 0;

	// depth first event handling
	inline bool handleMouseInput(void* TBD, Point mousePosition, bool check, bool pressed, bool released)
	{
		// we currently want to hande input regardless
		if (interacting)
		{
			onMouseInput(TBD, mousePosition, check, pressed, released);
			return true;
		}

		// if the mouse isn't over us, we do not care
		if (!rectanglePointCollisionCheck(mousePosition, origin, size)) return false;

		// determine relative mouse position
		Point relativePoint(mousePosition[0] - origin[0], mousePosition[1] - origin[1]);

		// see if a child needs to handle this event
		for (int i = 0; i < numChildren; i++)
		{
			// the event was handled
			if (handleMouseInput(TBD, relativePoint, check, pressed, released)) return true;
		}

		// no child has handled the event, handle it ourselves
		onMouseInput(TBD, relativePoint, check, pressed, released);
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
};