////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Summation UI Node                                                        //
//   Everett Moser                                                            //
//   11-29-15                                                                 //
//                                                                            //
//   UI Node for summing up to 8 signals                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Node.h"
#include "AudioNode.h"
#include "Connector.h"
#include "SignalSummation.h"

class SummationNode : public Node, public AudioUINode
{
	// maximum number of connections
	const static int MAX_INPUTS = 8;

	// all of the possible connections to be summed
	InputConnector* inputs[MAX_INPUTS];

	// the output connection of the result of the sum
	OutputConnector* output;
	
	// the underlying summation graph node
	SignalSummation* summation;

public:

	// run time type information
	RTTI_MACRO(SummationNode);

	// create the summation node at a specific position
	SummationNode(Point position);

	// new input connected or disconnected in the array of inputs
	static void inputConnected(Synthadeus* app, Component* connector);

	// update the summation with the currently connected input nodes
	void updateConnected();

	// a link to the underlying graph node
	inline virtual AudioNode* getAudioNode() { assert(summation != NULL); return summation; }

	// get the renderable list associated with this node
	virtual Renderable* getRenderList();

	// free the summation we maintain before we get removed
	inline virtual void onDestroy() { delete summation; }
};

