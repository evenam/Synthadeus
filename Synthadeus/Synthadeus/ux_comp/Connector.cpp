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

}

void InputConnector::update()
{

}

Renderable* InputConnector::getRenderList()
{
	return NULL;
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

}

void OutputConnector::disconnect(InputConnector* other)
{

}

int OutputConnector::connect(InputConnector* other)
{
	return 0;
}

InputConnector* OutputConnector::getConnected(int otherIndex)
{
	return NULL;
}

void OutputConnector::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{

}

void OutputConnector::update()
{

}

Renderable* OutputConnector::getRenderList()
{
	return NULL;
}
