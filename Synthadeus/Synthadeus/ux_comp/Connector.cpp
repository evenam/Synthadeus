#include "Connector.h"
#include "Node.h"
#include "Synthadeus.h"

Connector::HighlightType Connector::currentHighlight = Connector::NONE;

Connector::Connector(Point connectorOrigin, Point connectorSize, Node* connectorParent, unsigned int connectorColor)
{
	origin[0] = connectorOrigin[0];
	origin[1] = connectorOrigin[1];
	size[0] = connectorSize[0];
	size[1] = connectorSize[1];
	parent = connectorParent;
	color = connectorColor;
	setBoundingRectangle(origin, size);
}
//set the size of connector 
void Connector::setSize(Point connectorOrigin, Point connectorSize)
{
	otherCoords[0] = 0.f;
	otherCoords[1] = 0.f;
	origin[0] = connectorOrigin[0];
	origin[1] = connectorOrigin[1];
	size[0] = connectorSize[0];
	size[1] = connectorSize[1];
	setBoundingRectangle(origin, size);
}

//set connector color 
void Connector::setColor(unsigned int connectorColor)
{
	color = connectorColor;
}
//set connector parent
void Connector::setParent(Node* connectorParent)
{
	parent = connectorParent;
}

InputConnector::InputConnector(Point connectorOrigin, Point connectorSize, unsigned int connectorColor, Node* connectorParent, ActionCallback actioncCallback)
	: Connector(connectorOrigin, connectorSize, connectorParent, connectorColor)
{
	connectedComponent = NULL;
	connected = false;
	callback = actioncCallback;
}

Node* Connector::getParent()
{
	return parent;
}

Renderable* Connector::getRenderList()
{
	float radiusX, radiusY;
	radiusX = size[0] * 0.5f;
	radiusY = size[1] * 0.5f;
	bool shouldHighlight = false;
	if (Connector::currentHighlight == INPUT && isInputConnector()) shouldHighlight = true;
	if (Connector::currentHighlight == OUTPUT && isOutputConnector()) shouldHighlight = true;

	// top kek
	Renderable* circle = new RoundedRectangle(origin, size, (shouldHighlight ? COLOR_WHITE : color), (interacting? color : ((isConnected() > 0) ? COLOR_WHITE : COLOR_NONE)), radiusX, radiusY);

	if (isInputConnector() && isConnected() || interacting)
	{
		Point myCenter(origin[0] + size[0] * 0.5, origin[1] + size[1] * 0.5);
		Point bezierMidPoint1((otherCoords[0] + myCenter[0]) * 0.5f, myCenter[1]);
		Point bezierMidPoint2((otherCoords[0] + myCenter[0]) * 0.5f, otherCoords[1]);
		Renderable* curve = new BezierCurve<4>(myCenter, bezierMidPoint1, bezierMidPoint2, otherCoords);
		circle->next = curve;
	}

	return circle;
}

Node* InputConnector::getConnectionParent()
{
	if (connectedComponent && connected) return connectedComponent->getParent();
	return NULL;
}
//connector has been removed 
void InputConnector::disconnect()
{
	if (!connected) return;
	connectedComponent->disconnect(this);
	connected = false;
	connectedComponent = NULL;
}
//connection is destroyed
void InputConnector::onDestroy()
{
	disconnect();
	connectedComponent = NULL;
	connected = 0;
}
//output connection occurs
void InputConnector::connect(OutputConnector* other)
{
	if (other == NULL) return;
	disconnect();
	other->connect(this);
	connected = true;
	connectedComponent = other;
}
//mouse events for left and right checks that are pressed
void InputConnector::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
	if (!connected)
	{
		otherCoords[0] = vMouse->instancePosition()[0];
		otherCoords[1] = vMouse->instancePosition()[1];
	}

	if (vMouse->left.checkPressed() && !interacting)
	{
		disconnect();
		callback(app, this);
		interacting = true;
		Connector::currentHighlight = Connector::OUTPUT;
		}
	if (vMouse->left.checkReleased() && interacting)
	{
		interacting = false;
		Connector::currentHighlight = Connector::NONE;
		Component* other = app->findComponentAtLocation(vMouse->position);
		if (other && (_strcmpi(other->getClassName(), OutputConnector::nameString()) == 0))
		{
			connect((OutputConnector*)other);
			callback(app, this);
		}
	}

	if (vMouse->right.checkReleased())
	{
		onDestroy(); // shortcut to remove the connection
		callback(app, this);
	}
}
//updates the connection
void InputConnector::update()
{
	if (connected && connectedComponent)
	{
		otherCoords[0] = connectedComponent->getAbsoluteOrigin()[0] + connectedComponent->size[0] * 0.5f - getAbsoluteOrigin()[0] + origin[0];
		otherCoords[1] = connectedComponent->getAbsoluteOrigin()[1] + connectedComponent->size[1] * 0.5f - getAbsoluteOrigin()[1] + origin[1];
	}
}
//find connector in the list
int OutputConnector::findConnectorInList(InputConnector* connector)
{
	for (int i = 0; i < numConnectedComponents; i++)
	{
		if (connectedComponents[i] == connector)
			return i;
	}
	return -1;
}
//connector components
OutputConnector::OutputConnector(Point connectorOrigin, Point connectorSize, unsigned int connectorColor, Node* connectorParent)
	: Connector(connectorOrigin, connectorSize, connectorParent, connectorColor)
{
	numConnectedComponents = 0;
}
//get the parent connection 
Node* OutputConnector::getConnectionParent(int index)
{
	if (index < 0) return NULL;
	if (index > numConnectedComponents) return NULL;

	return connectedComponents[index]->getParent();
}
//checking connector for a disconnection
void OutputConnector::disconnect(int index)
{
	if (index < 0) return;
	if (index >= numConnectedComponents) return;
	for (int i = index; i < numConnectedComponents; i++)
		connectedComponents[i] = connectedComponents[i + 1];
	numConnectedComponents--;
}
//index for found connector
void OutputConnector::disconnect(InputConnector* other)
{
	int index = findConnectorInList(other);
	disconnect(index);
}
//connector is destroyed
void OutputConnector::onDestroy()
{
	for (int i = numConnectedComponents - 1; i >= 0; i--)
	{
		connectedComponents[i]->disconnect();
		connectedComponents[i] = NULL;
	}
	numConnectedComponents = 0;
}

int OutputConnector::connect(InputConnector* other)
{
	if (numConnectedComponents >= MAX_CONNECTED_COMPONENTS) return -1;
	if (other == NULL) return -1;
	if (findConnectorInList(other) >= 0) return -1;
	connectedComponents[numConnectedComponents] = other;
	DebugPrintf("Connecting %s (input) to %s (output)\n", getParent()->getClassName(), other->getParent()->getClassName());
	return numConnectedComponents++;
}

InputConnector* OutputConnector::getConnected(int otherIndex)
{
	if (otherIndex >= numConnectedComponents) return NULL;
	if (otherIndex < 0) return NULL;
	return connectedComponents[otherIndex];
}
//mouse events for left and right check presses
void OutputConnector::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
	otherCoords[0] = vMouse->instancePosition()[0];
	otherCoords[1] = vMouse->instancePosition()[1];

	if (vMouse->left.checkPressed() && !interacting)
	{
		interacting = true;
		Connector::currentHighlight = Connector::INPUT;
	}
	if (vMouse->left.checkReleased() && interacting)
	{
		interacting = false;
		Connector::currentHighlight = Connector::NONE;
		Component* other = app->findComponentAtLocation(vMouse->position);
		if (other && (_strcmpi(other->getClassName(), InputConnector::nameString()) == 0))
		{
			((InputConnector*)other)->connect(this);
			((InputConnector*)other)->callback(app, other);
			assert(((InputConnector*)other)->isConnected() == 1);
		}
	}

	if (vMouse->right.checkReleased())
	{
		for (int i = numConnectedComponents - 1; i >= 0; i--)
		{
			InputConnector* other = connectedComponents[i];
			other->disconnect();
			other->callback(app, other);
			connectedComponents[i] = NULL;
		}
		numConnectedComponents = 0;
	}
}

void OutputConnector::update()
{
}
