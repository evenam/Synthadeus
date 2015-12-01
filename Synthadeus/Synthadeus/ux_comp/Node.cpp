#include "Node.h"
#include "Connector.h"
//generate node components 
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
//sets the size a node 
void Node::setSize(Point nodeOrigin, Point nodeSize)
{
	origin[0] = nodeOrigin[0];
	origin[1] = nodeOrigin[1];
	size[0] = nodeSize[0];
	size[1] = nodeSize[1];
}
//sets the color scheme
void Node::setColorScheme(unsigned int nodeFgColor, unsigned int nodeBgColor)
{
	fgColor = nodeFgColor;
	bgColor = nodeBgColor;
}
//handles the mouse events for interaction
void Node::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
	static Point diff;

	if (vMouse->left.checkPressed())
	{
		// mouse clicked
		interacting = true;
		diff = vMouse->instancePosition();
	}
	else if (vMouse->left.checkReleased())
	{
		// mouse released
		interacting = false;
		diff[0] = diff[1] = 0;
	}
	else if (vMouse->left.check() && interacting)
	{
		// mouse moving
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
				// callbacks as necessary
				InputConnector* input = dynamic_cast<InputConnector*>(child(i));
				OutputConnector* output = dynamic_cast<OutputConnector*>(child(i));
				if (input)
				{
					input->disconnect();
					input->callback(app, input);
				}
				else if (output)
				{
					for (int i = output->numConnectedComponents - 1; i >= 0; i--)
					{
						input = output->connectedComponents[i];
						input->disconnect();
						input->callback(app, input);
					}
				}

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
//get render list for this certain node
Renderable* Node::getRenderList()
{
	Renderable* rect = new RoundedRectangle(origin, size, fgColor, bgColor, 5.f, 5.f);
	return rect;
}
