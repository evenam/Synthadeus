#include "MultiplierNode.h"
#include "Synthadeus.h"

MultiplierNode::MultiplierNode(Point position)
	: Node(position, Point(200.f, 65.f), COLOR_CYAN, COLOR_ABLACK)
{
	// create the underlying signal multiplier
	multiplier = new SignalMultiplier(2.f);

	// create the output connection and add it to the component list
	output = new OutputConnector(Point(170.f, 35.f), Point(20.f, 20.f), COLOR_CYAN, this);
	addChild(output);

	// create the input connection and add it to the component list
	input = new InputConnector(Point(10.f, 40.f), Point(15.f, 15.f), COLOR_CYAN, this, onInputChanged);
	addChild(input);

	// create the value-modifying slider and add it to the component list
	slider = new Slider(Point(40.f, 40.f), Point(100.f, 15.f), COLOR_NONE, COLOR_CYAN, Slider::HORIZONTAL, -5.f, 5.f, 2.f, 0.1f, onSliderChanged);
	addChild(slider);

	// update the UI to reflect the actual values
	updateValue();
}

Renderable* MultiplierNode::getRenderList()
{
	// get base renderables list
	Renderable* nodeRenderables = Node::getRenderList();

	// create the title
	Renderable* titleText = new Text("Multiplier", getOrigin(), Point(200.f, 40.f), FONT_ARIAL20, COLOR_WHITE);

	// append the title to the list and return the result
	nodeRenderables->next = titleText;
	return nodeRenderables;
}

AudioNode* MultiplierNode::getAudioNode()
{
	// return the idiot proof'd audio node
	assert(multiplier != NULL);
	return multiplier;
}

void MultiplierNode::updateValue()
{
	// get the slider value
	float value = slider->getValue();

	// update the multiplier value
	multiplier->setValue(value);

	if (input->isConnected() > 0)
	{
		// hook up the input connection if we are connected
		AudioUINode* other = dynamic_cast<AudioUINode*>(input->getConnectionParent());
		assert(other != NULL);
		multiplier->setInput(other->getAudioNode());
	}
	else
	{
		// else we disconnect the nodes
		multiplier->setInput(NULL);
	}
}

void MultiplierNode::onSliderChanged(Synthadeus * app, Component * me)
{
	// resolve the identity crisis
	MultiplierNode* myself = dynamic_cast<MultiplierNode*>(me->getParent());

	// update myself and the graph
	myself->updateValue();
	app->recalculateAudioGraph();
}

void MultiplierNode::onInputChanged(Synthadeus * app, Component * me)
{
	// resolve the identity crisis
	MultiplierNode* myself = (MultiplierNode*)(me->getParent());

	// update myself and the graph
	DebugPrintf("Connected %s to %s\n", (((InputConnector*)me)->getConnectionParent() ? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"), myself->getClassName());
	myself->updateValue();
	app->recalculateAudioGraph();
}
