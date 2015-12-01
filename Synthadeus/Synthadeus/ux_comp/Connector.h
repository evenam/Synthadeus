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

// base connector
class Connector : public Component
{
protected:

	// position and size
	Point origin;
	Point size;

	// color
	unsigned int color;

	// parent to determine connections
	Node* parent;

	// other coordinates to draw pretty bezier curves
	Point otherCoords;

	// relating to highlighting valid connectable nodes
	enum HighlightType { INPUT, OUTPUT, NONE };
	static HighlightType currentHighlight;

public:

	// construct the connector with parental information, geometric information, and a color
	Connector(Point connectorOrigin, Point connectorSize, Node* connectorParent, unsigned int connectorColor);

	// set the connector size
	void setSize(Point connectorOrigin, Point connectorSize);

	// set the connector color
	void setColor(unsigned int connectorColor);

	// change parents (adoption!)
	void setParent(Node* connectorParent);

	// the current parent set (who's your daddy?)
	Node* getParent();

	// number of nodes connected to me
	virtual int isConnected() = 0;

	// are we an output connector? we can have multiple connections from an output cunnector
	virtual bool isOutputConnector() = 0;

	// are we an input connector? we can only accept a single input in an input connector
	virtual bool isInputConnector() = 0;

	// empty event handler
	inline virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse) {};

	// empty update cycle function
	inline virtual void update() {};

	// render the nodes (the base class handles both input/output cases via tight coupling)
	virtual Renderable* getRenderList();
};

// the input connector handles a connection since it only has one other node it can be connected to. simplicity
class InputConnector : public Connector
{
	// nodes can access the private members, specifically the action callback
	friend class Node;

	// this makes things much easier to work with and less code to write since these two classes are so closely related
	friend class OutputConnector;

private:

	// the component we are connected to 
	OutputConnector* connectedComponent;

	// whether or not we are connected
	bool connected;

	// when the connection status changes, this get called
	ActionCallback callback;

public:

	// run time type information
	RTTI_MACRO(InputConnector);

	// make an input connector with standard parameters, and the connected callback
	InputConnector(Point connectorOrigin, Point connectorSize, unsigned int connectorColor, Node* connectorParent = NULL, ActionCallback actionCallbackFunction = DEFAULT_ACTION_CALLBACK);
	
	// get the parent we are connected to
	Node* getConnectionParent();

	// returns the number of connections
	virtual inline int isConnected() { return (connected ? 1 : 0); }
	
	// remove the current connection if there is one
	void disconnect();

	// create a connection
	void connect(OutputConnector* other);

	// the output node we are connected to
	inline OutputConnector* getConnected() { return connectedComponent; }

	// we are an input connector
	virtual inline bool isOutputConnector() { return false; }

	// so we return positive for input connector test
	virtual inline bool isInputConnector() { return true; }

	// handle the mouse event to assist in creating connections
	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);

	// the update cycle function
	virtual void update();

	// override destroy to remove connections before this is are removed
	virtual void onDestroy();
};

class OutputConnector : public Connector
{
	// makes life easier since the node needs as much data as possible from its connectors
	friend class Node;

	// these classes are ever so slightly different
	friend class InputConnector;

	// the list of connected components
	const static int MAX_CONNECTED_COMPONENTS = 16;
	InputConnector* connectedComponents[MAX_CONNECTED_COMPONENTS];
	int numConnectedComponents;

public:

	// run time type informtation
	RTTI_MACRO(OutputConnector);

	// construct and output connector just like an ordinaty connector, no callback
	OutputConnector(Point connectorOrigin, Point connectorSize, unsigned int connectorColor, Node* connectorParent = NULL);

	// find the parent of the connected node for the connection at index
	Node* getConnectionParent(int index);

	// returns the number of connections intact
	virtual inline int isConnected() { return numConnectedComponents; }

	// remove a connection between this and an input connector by reference, if it exists
	void disconnect(InputConnector* other);

	// remove the connection at an index if it exists
	void disconnect(int otherIndex);

	// creates a connection between nodes
	int connect(InputConnector* other);

	// get the connector associated with the connection at index in the list
	InputConnector* getConnected(int otherIndex);

	// determine the index of a connector in the active connection list
	int findConnectorInList(InputConnector* connector);

	// positive test for being an output connector
	virtual inline bool isOutputConnector() { return true; }

	// negative test for being an input connector
	virtual inline bool isInputConnector() { return false; }

	// handle a mouse event to assist in making connections
	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);

	// the update cycle function
	virtual void update();

	// kill connections before we are freed
	virtual void onDestroy();
};
