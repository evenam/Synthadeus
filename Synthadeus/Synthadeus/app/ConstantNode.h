////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Constant UI Node                                                         //
//   Everett Moser                                                            //
//   11-29-15                                                                 //
//                                                                            //
//   A UI for constants to modifying signals                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Node.h"
#include "Connector.h"
#include "AudioConstant.h"
#include "Slider.h"

class ConstantNode : public Node, public AudioUINode
{
private:
	// audio graph constant node to maintain
	AudioConstant* constant;

	// a connection to the next node in the sequence
	OutputConnector* output;

	// a slider to adjust the constant node's value
	Slider* slider;

public:
	
	// create the node at a specific place
	ConstantNode(Point position);

	// generate the render list for the node
	virtual Renderable* getRenderList();

	// delete the graph node when it is no longer in use
	inline virtual void onDestroy() { delete constant; }

	// return the graph node which this UI node refers to
	virtual AudioNode* getAudioNode();

	// update the value of the contant to the value of the slider
	void updateValue();

	// slider changed callback
	static void onSliderChanged(Synthadeus* app, Component* me);
};

