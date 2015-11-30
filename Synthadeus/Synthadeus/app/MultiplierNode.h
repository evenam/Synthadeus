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
	SignalMultiplier* multiplier;
	OutputConnector* output;
	InputConnector* input;
	Slider* slider;

public:
	MultiplierNode(Point position);

	virtual Renderable* getRenderList();
	inline virtual void onDestroy() { delete multiplier; }

	virtual AudioNode* getAudioNode();

	void updateValue();
	static void onSliderChanged(Synthadeus* app, Component* me);
	static void onInputChanged(Synthadeus* app, Component* me);
};