////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Connection UI Component                                                  //
//   Everett Moser                                                            //
//   11-19-15                                                                 //
//                                                                            //
//   A connection site for a node on the GUI                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "Renderables.h"

class Node;
class InputConnector;
class OutputConnector;

class Connector : public Component
{
protected:
	Point origin;
	Point size;
	unsigned int color;
	Node* parent;
	Point otherCoords;

	bool isEarlierInGraph(Connector* testConnector);

public:
	Connector(Point connectorOrigin, Point connectorSize, Node* connectorParent, unsigned int connectorColor);
	void setSize(Point connectorOrigin, Point connectorSize);
	void setColor(unsigned int connectorColor);
	void setParent(Node* connectorParent);
	Node* getParent();
	virtual int isConnected() = 0;
	virtual bool isOutputConnector() = 0;
	virtual bool isInputConnector() = 0;

	inline virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse) {};
	inline virtual void update() {};
	virtual Renderable* getRenderList();
};

class InputConnector : public Connector
{
private:
	friend class OutputConnector;
	OutputConnector* connectedComponent;
	bool connected;
public:
	RTTI_MACRO(InputConnector);
	InputConnector(Point connectorOrigin, Point connectorSize, unsigned int connectorColor, Node* connectorParent = NULL);
	Node* getConnectionParent();
	virtual inline int isConnected() { return (connected ? 1 : 0); }
	void disconnect();
	void connect(OutputConnector* other);
	OutputConnector* getConnected();
	virtual inline bool isOutputConnector() { return false; }
	virtual inline bool isInputConnector() { return true; }

	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);
	virtual void update();
};

class OutputConnector : public Connector
{
	friend class InputConnector;
	const static int MAX_CONNECTED_COMPONENTS = 16;
	InputConnector* connectedComponents[MAX_CONNECTED_COMPONENTS];
	int numConnectedComponents;

public:
	RTTI_MACRO(OutputConnector);
	OutputConnector(Point connectorOrigin, Point connectorSize, unsigned int connectorColor, Node* connectorParent = NULL);
	Node* getConnectionParent(int index);
	virtual inline int isConnected() { return numConnectedComponents; }
	void disconnect(InputConnector* other);
	void disconnect(int otherIndex);
	int connect(InputConnector* other);
	InputConnector* getConnected(int otherIndex);
	int findConnectorInList(InputConnector* connector);

	virtual inline bool isOutputConnector() { return true; }
	virtual inline bool isInputConnector() { return false; }

	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);
	virtual void update();
};
