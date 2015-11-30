#include "ConstantNode.h"
#include "Synthadeus.h"

ConstantNode::ConstantNode(Point position)
	: Node(position, Point(160.f, 65.f), COLOR_CORNFLOWERBLUE, COLOR_ABLACK)
{
	constant = new AudioConstant(0.f);
	output = new OutputConnector(Point(130.f, 35.f), Point(20.f, 20.f), COLOR_CORNFLOWERBLUE, this);
	addChild(output);
	slider = new Slider(Point(10.f, 40.f), Point(100.f, 15.f), COLOR_ABLACK, COLOR_CORNFLOWERBLUE, Slider::HORIZONTAL, -1.f, 1.f, 0.f, 0.1f, onSliderChanged);
	addChild(slider);
	updateValue();
}

Renderable* ConstantNode::getRenderList()
{
	Renderable* nodeRenderables = Node::getRenderList();
	Renderable* titleText = new Text("Constant", getOrigin(), Point(160.f, 40.f), FONT_ARIAL20, COLOR_WHITE);
	nodeRenderables->next = titleText;
	return nodeRenderables;
}

AudioNode* ConstantNode::getAudioNode()
{
	assert(constant != NULL);
	return constant;
}

void ConstantNode::updateValue()
{
	float value = slider->getValue();
	constant->setValue(value);
}

void ConstantNode::onSliderChanged(Synthadeus * app, Component * me)
{
	ConstantNode* myself = dynamic_cast<ConstantNode*>(me->getParent());
	myself->updateValue();
	app->recalculateAudioGraph();
}
