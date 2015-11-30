#include "MultiplierNode.h"
#include "Synthadeus.h"

MultiplierNode::MultiplierNode(Point position)
	: Node(position, Point(200.f, 65.f), COLOR_CYAN, COLOR_ABLACK)
{
	multiplier = new SignalMultiplier(2.f);
	output = new OutputConnector(Point(170.f, 35.f), Point(20.f, 20.f), COLOR_CYAN, this);
	addChild(output);
	input = new InputConnector(Point(10.f, 40.f), Point(15.f, 15.f), COLOR_CYAN, this, onInputChanged);
	addChild(input);
	slider = new Slider(Point(40.f, 40.f), Point(100.f, 15.f), COLOR_NONE, COLOR_CYAN, Slider::HORIZONTAL, -5.f, 5.f, 2.f, 0.1f, onSliderChanged);
	addChild(slider);
	updateValue();
}

Renderable* MultiplierNode::getRenderList()
{
	Renderable* nodeRenderables = Node::getRenderList();
	Renderable* titleText = new Text("Multiplier", getOrigin(), Point(200.f, 40.f), FONT_ARIAL20, COLOR_WHITE);
	nodeRenderables->next = titleText;
	return nodeRenderables;
}

AudioNode* MultiplierNode::getAudioNode()
{
	assert(multiplier != NULL);
	return multiplier;
}

void MultiplierNode::updateValue()
{
	float value = slider->getValue();
	multiplier->setValue(value);
	if (input->isConnected() > 0)
	{
		AudioUINode* other = dynamic_cast<AudioUINode*>(input->getConnectionParent());
		assert(other != NULL);
		multiplier->setInput(other->getAudioNode());
	}
	else
	{
		multiplier->setInput(NULL);
	}
}

void MultiplierNode::onSliderChanged(Synthadeus * app, Component * me)
{
	MultiplierNode* myself = dynamic_cast<MultiplierNode*>(me->getParent());
	myself->updateValue();
	app->recalculateAudioGraph();
}

void MultiplierNode::onInputChanged(Synthadeus * app, Component * me)
{
	MultiplierNode* myself = (MultiplierNode*)(me->getParent());
	DebugPrintf("Connected %s to %s\n", (((InputConnector*)me)->getConnectionParent() ? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"), myself->getClassName());
	myself->updateValue();
	app->recalculateAudioGraph();
}
