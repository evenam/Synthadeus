#include "ConstantNode.h"
#include "Synthadeus.h"

ConstantNode::ConstantNode(Point position)
	: Node(position, Point(160.f, 65.f), COLOR_CORNFLOWERBLUE, COLOR_ABLACK)
{
	// create the underlying constant node
	constant = new AudioConstant(0.f);

	// create the output connection point and add it to my component list
	output = new OutputConnector(Point(130.f, 35.f), Point(20.f, 20.f), COLOR_CORNFLOWERBLUE, this);
	addChild(output);

	// create and add the slider which adjusts the value of the constant
	slider = new Slider(Point(10.f, 40.f), Point(100.f, 15.f), COLOR_ABLACK, COLOR_CORNFLOWERBLUE, Slider::HORIZONTAL, -1.f, 1.f, 0.f, 0.1f, onSliderChanged);
	addChild(slider);

	// update the UI to reflect the actual values
	updateValue();
}

Renderable* ConstantNode::getRenderList()
{
	// aquire the base renderable list
	Renderable* nodeRenderables = Node::getRenderList();

	// generate a title
	Renderable* titleText = new Text("Constant", getOrigin(), Point(160.f, 40.f), FONT_ARIAL20, COLOR_WHITE);

	// append the title to the list, returning the result
	nodeRenderables->next = titleText;
	return nodeRenderables;
}

AudioNode* ConstantNode::getAudioNode()
{
	// return the idiot proof'd constant
	assert(constant != NULL);
	return constant;
}

void ConstantNode::updateValue()
{
	// pass the value from the slider to the node
	float value = slider->getValue();
	constant->setValue(value);
}

void ConstantNode::onSliderChanged(Synthadeus * app, Component * me)
{
	// resolve the identity crisis
	ConstantNode* myself = dynamic_cast<ConstantNode*>(me->getParent());

	// update myself and recalculate the graph
	myself->updateValue();
	app->recalculateAudioGraph();
}
