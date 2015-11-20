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
}

void Connector::setSize(Point connectorOrigin, Point connectorSize)
{
	origin[0] = connectorOrigin[0];
	origin[1] = connectorOrigin[1];
	size[0] = connectorSize[0];
	size[1] = connectorSize[1];
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
	return new RoundedRectangle(origin, size, color, (interacting? color : COLOR_NONE), radiusX, radiusY);
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
	if (vMouse->left.checkPressed() && !interacting)
	{
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

}

void OutputConnector::update()
{

}
