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

// components are 128-trees!
#define COMPONENT_MAX_CHILDREN 128

class Synthadeus;
class Component : public Object
{
private:
	// bounding rectangle
	Point origin, size;

	// the parent
	Component* parent;

	// sub-components
	Component* children[COMPONENT_MAX_CHILDREN];
	int numChildren;

	// find the component which is currently hogging events
	inline Component* handleCurrentlyInteracting(Synthadeus* app, InputDevice::Mouse* vMouse)
	{
		// if it's me, handle me and return
		if (interacting)
		{
			mouseEventHandler(app, vMouse);
			return this;
		}

		// else find a child element
		for (int i = 0; i < numChildren; i++)
		{
			// make sure the mouse is in the right position
			vMouse->instance(origin);
			Component* temporary = children[i]->handleCurrentlyInteracting(app, vMouse);
			vMouse->restore();

			// if handled, return the child
			if (temporary) return temporary;
		}

		// noone from this component down is currently interacting
		return NULL;
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

	// marked for removal?
	bool removeMe;

public:

	// initializes a component node with no children, not interacting, and present for future update cycles
	inline Component() { numChildren = 0; interacting = false; removeMe = false; }

	// the overrideable mouse event handler
	inline virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse) {};

	// the overrideable update cycle event
	inline virtual void update() {};

	// upon the destruction of this components we...
	inline virtual void onDestroy() {};

	// gereate the renderable list
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
	
	// check if a point is in the rectangle described
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

	// manually mark an object for deletion
	inline void signalRemoval()
	{
		// signal myself
		removeMe = true;

		// and signal the children, if they haven't been disposed of already
		for (int i = 0; i < numChildren; i++)
		{
			if (children[i] != NULL)
				children[i]->signalRemoval();
		}
	}

	// sweep portion of mark and sweep pseudo garbage collection
	inline void sweepDeletion()
	{
		Component* current = NULL;
		for (int i = numChildren - 1; i >= 0; i--)
		{
			// recuse before we destroy the child
			current = children[i];
			current->sweepDeletion();

			// destroy the child if signal'd
			if (children[i]->needsDeletion())
			{
				DebugPrintf("Deleting child %s\n", children[i]->getClassName());
				children[i]->onDestroy();
				removeChild(current);
				delete current;
			}
		}
	}

	// get the index-th child
	inline Component* child(int index)
	{
		return children[index];
	}

	// add a subcomponent child
	inline int addChild(Component* child)
	{
		assert(numChildren < COMPONENT_MAX_CHILDREN);

		// return the child index if it is already a child of this component
		for (int i = 0; i < numChildren; i++)
		{
			// component found
			if (children[i] == child)
				return i;
		}
		
		// insert the child and return the index
		children[numChildren] = child;
		child->parent = this;
		return numChildren++;
	}

	// remove a subcomponent child by reference
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
				child->parent = NULL;
				return;
			}
		}
	}

	// remove a subcomponent child by index
	inline void removeChild(int index)
	{
		// remove the child at the index, called responsible for managing memory
		// quicker because we do not need to search for the component
		children[index]->parent = NULL;
		for (int j = index; j < numChildren - 1; j++)
		{
			children[j] = children[j + 1];
		}
		numChildren--;
	}

	// query the current number of child component nodes
	inline int getNumChildren() { return numChildren; };

	// return whether we are currently interacting with the input system
	inline bool isInteracting()
	{
		return interacting;
	}

	// generate the render list for this component and all sub components
	inline Renderable* getRenderTree()
	{
		// returned list
		Renderable* thisList = getRenderList();

		// a child list to generate
		Renderable* thisChildList = NULL;

		// a pointer to the next position in the list
		Renderable* realCurrent = NULL;

		// get all child lists
		for (int i = 0; i < numChildren; i++)
		{
			Renderable* current = children[i]->getRenderTree();

			// assign the first item
			if (i == 0)
			{
				thisChildList = current;
				realCurrent = current;
			}
			else
			{
				// but append the second, third, etc. 
				while (realCurrent->next != NULL)
					realCurrent = realCurrent->next;
				realCurrent->next = current;
			}
		}

		// traverse the list tree to find the last child
		realCurrent = thisList;
		while (realCurrent->child)
			realCurrent = realCurrent->child;

		// append the children and return
		realCurrent->child = thisChildList;
		return thisList;
	}

	// call all the update events for this node and the children
	inline void updateTree()
	{
		// self update
		update();

		// children update
		for (int i = 0; i < numChildren; i++)
			children[i]->updateTree();
	}

	// see if me or a subcomponent is currently at the point specified
	inline Component* getComponentAtPoint(Point pt)
	{
		// if we dont pass the rectangle check, we are not on the point
		if (!rectanglePointCollisionCheck(pt, origin, size)) return NULL;

		// instance the origin
		pt += -1.f * origin;

		// search the children for a possible subcomponent collision
		for (int i = 0; i < numChildren; i++)
		{
			Component* childComp = children[i]->getComponentAtPoint(pt);
			if (childComp) return childComp;
		}
		
		// no child component found at the point, so it must be me
		return this;
	}

	// the absolute origin of this component to the base node
	inline Point getAbsoluteOrigin()
	{
		// if i have a parent, then tack on its origin
		if (parent)
			return parent->getAbsoluteOrigin() + origin;
		else
		// we are the base node, so based
			return Point(0.f, 0.f);
	}

	// see if we need deletion
	inline bool needsDeletion() { return removeMe; };

	// get the origin
	inline Point getOrigin() { return origin; }

	// get the size
	inline Point getSize() { return size; }

	// get the parent
	inline Component* getParent() { return parent; }
};

// generic callback function
typedef void(*ActionCallback)(Synthadeus* app, Component* myself);

// the default callback function
inline void DEFAULT_ACTION_CALLBACK(Synthadeus* app, Component* myself) {};
