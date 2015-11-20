#include "Connector.h"
#include "Node.h"

bool Connector::isEarlierInGraph(Connector* testConnector)
{
	return false;
}

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

void Connector::setColor(unsigned int connectorColor)
{
	color = connectorColor;
}

void Connector::setParent(Node* connectorParent)
{
	parent = connectorParent;
}

InputConnector::InputConnector(Point connectorOrigin, Point connectorSize, unsigned int connectorColor, Node* connectorParent)
	: Connector(connectorOrigin, connectorSize, connectorParent, connectorColor)
{
	connectedComponent = NULL;
	connected = false;
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

	// top kek
	Renderable* circle = new RoundedRectangle(origin, size, color, (interacting? color : COLOR_NONE), radiusX, radiusY);

	if (isInputConnector() && isConnected())
	{
		Point myCenter(origin[0] + size[0] * 0.5, origin[0] + size[1] * 0.5);
		Point bezierMidPoint1((otherCoords[0] + myCenter[0]) * 0.5f, myCenter[1]);
		Point bezierMidPoint2((otherCoords[0] + myCenter[0]) * 0.5f, otherCoords[1]);
		Renderable* curve = new BezierCurve<4>(myCenter, bezierMidPoint1, bezierMidPoint2, otherCoords);
		circle->next = curve;
	}
	else if (interacting)
	{
		Point myCenter(origin[0] + size[0] * 0.5, origin[0] + size[1] * 0.5);
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

void InputConnector::disconnect()
{
	if (!connected) return;
	connectedComponent->disconnect(this);
	connected = false;
	connectedComponent = NULL;
}

void InputConnector::connect(OutputConnector* other)
{
	if (other == NULL) return;
	disconnect();
	other->connect(this);
	connected = true;
	connectedComponent = other;
}

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
		interacting = true;
	}
	if (vMouse->left.checkReleased() && interacting)
	{
		interacting = false;
		
	}
}

void InputConnector::update()
{
}

int OutputConnector::findConnectorInList(InputConnector* connector)
{
	for (int i = 0; i < numConnectedComponents; i++)
	{
		if (connectedComponents[i] == connector)
			return i;
	}
	return -1;
}

OutputConnector::OutputConnector(Point connectorOrigin, Point connectorSize, unsigned int connectorColor, Node* connectorParent)
	: Connector(connectorOrigin, connectorSize, connectorParent, connectorColor)
{
	numConnectedComponents = 0;
}

Node* OutputConnector::getConnectionParent(int index)
{
	if (index < 0) return NULL;
	if (index > numConnectedComponents) return NULL;

	return connectedComponents[index]->getParent();
}

void OutputConnector::disconnect(int index)
{
	if (index < 0) return;
	if (index >= numConnectedComponents) return;
	for (int i = index; i < numConnectedComponents; i++)
		connectedComponents[i] = connectedComponents[i + 1];
	numConnectedComponents--;
}

void OutputConnector::disconnect(InputConnector* other)
{
	int index = findConnectorInList(other);
	disconnect(index);
}

int OutputConnector::connect(InputConnector* other)
{
	if (numConnectedComponents >= MAX_CONNECTED_COMPONENTS) return -1;
	if (other == NULL) return -1;
	connectedComponents[numConnectedComponents] = other;
	return numConnectedComponents++;
}

InputConnector* OutputConnector::getConnected(int otherIndex)
{
	if (otherIndex >= numConnectedComponents) return NULL;
	if (otherIndex < 0) return NULL;
	return connectedComponents[otherIndex];
}

void OutputConnector::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
	if (numConnectedComponents == 0)
	{
		otherCoords[0] = vMouse->instancePosition()[0];
		otherCoords[1] = vMouse->instancePosition()[1];
	}

	if (vMouse->left.checkPressed() && !interacting)
	{
		interacting = true;
	}
	if (vMouse->left.checkReleased() && interacting)
	{
		interacting = false;

	}
}

void OutputConnector::update()
{

}
