////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Audio Graph Constant Node                                                //
//   Everett Moser                                                            //
//   11-23-15                                                                 //
//                                                                            //
//   A constant audio buffer                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Node.h"
#include "Connector.h"
#include "Slider.h"
#include "SignalMultiplier.h"

class MultiplierNode : public Node, public AudioUINode
{
private:
	
	// reference to the multiplier node to maintain
	SignalMultiplier* multiplier;

	// the connection to the next node in the graph
	OutputConnector* output;

	// the input signal to apply the multiplier to
	InputConnector* input;

	// adjust the multiplier value
	Slider* slider;

public:

	// run time type information
	RTTI_MACRO(MultiplierNode);

	// create a node at a location
	MultiplierNode(Point position);

	// get the render list for this node
	virtual Renderable* getRenderList();

	// remove the multiplier this node maintains
	inline virtual void onDestroy() { delete multiplier; }

	// get the node this UI component represents
	virtual AudioNode* getAudioNode();

	// update the multiplier value of the audio node
	void updateValue();

	// callback for the slider being changed
	static void onSliderChanged(Synthadeus* app, Component* me);

	// callback for a new input connection
	static void onInputChanged(Synthadeus* app, Component* me);
};