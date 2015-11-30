////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Summation UI Node                                                        //
//   Everett Moser                                                            //
//   11-19-15                                                                 //
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
	const static int MAX_INPUTS = 8;
	InputConnector* inputs[MAX_INPUTS];
	OutputConnector* output;
	SignalSummation* summation;

public:
	SummationNode(Point position);

	static void inputConnected(Synthadeus* app, Component* connector);
	void updateConnected();

	inline virtual AudioNode* getAudioNode() { assert(summation != NULL); return summation; }

	virtual Renderable* getRenderList();
	inline virtual void onDestroy() { delete summation; }
};

