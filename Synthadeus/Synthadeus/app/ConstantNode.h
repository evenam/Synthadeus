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
	AudioConstant* constant;
	OutputConnector* output;
	Slider* slider;

public:
	ConstantNode(Point position);

	virtual Renderable* getRenderList();
	inline virtual void onDestroy() { delete constant; }

	virtual AudioNode* getAudioNode();

	void updateValue();
	static void onSliderChanged(Synthadeus* app, Component* me);
};

