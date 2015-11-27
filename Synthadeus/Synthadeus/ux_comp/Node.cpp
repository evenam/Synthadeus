#include "Node.h"

Node::Node(Point nodeOrigin, Point nodeSize, unsigned int nodeFgColor, unsigned int nodeBgColor, bool isRemoveable) : Component()
{
	origin[0] = nodeOrigin[0];
	origin[1] = nodeOrigin[1];
	size[0] = nodeSize[0];
	size[1] = nodeSize[1];
	fgColor = nodeFgColor;
	bgColor = nodeBgColor;
	setBoundingRectangle(origin, size);
	interacting = false;
	relativeMouseX = 0.f;
	relativeMouseY = 0.f;
	removeable = isRemoveable;
}

void Node::setSize(Point nodeOrigin, Point nodeSize)
{
	origin[0] = nodeOrigin[0];
	origin[1] = nodeOrigin[1];
	size[0] = nodeSize[0];
	size[1] = nodeSize[1];
}

void Node::setColorScheme(unsigned int nodeFgColor, unsigned int nodeBgColor)
{
	fgColor = nodeFgColor;
	bgColor = nodeBgColor;
}

void Node::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
	static Point diff;

	if (vMouse->left.checkPressed())
	{
		interacting = true;
		diff = vMouse->instancePosition();
	}
	else if (vMouse->left.checkReleased())
	{
		interacting = false;
		diff[0] = diff[1] = 0;
	}
	else if (vMouse->left.check() && interacting)
	{
		diff = vMouse->instancePosition() - diff;
		origin += diff;
		setBoundingRectangle(origin, size);
		diff = vMouse->instancePosition();
	}

	if (vMouse->right.checkReleased() && removeable)
	{
		if (Component::rectanglePointCollisionCheck(vMouse->instancePosition(), origin, size))
		{
			removeMe = true;
			int nChildren = getNumChildren();
			for (int i = 0; i < nChildren; i++)
			{
				// early call to break connections
				child(i)->onDestroy();
				child(i)->signalRemoval();
			}
		}
	}
}

void Node::update()
{
}

Renderable* Node::getRenderList()
{
	Renderable* rect = new RoundedRectangle(origin, size, fgColor, bgColor, 5.f, 5.f);
	return rect;
}
