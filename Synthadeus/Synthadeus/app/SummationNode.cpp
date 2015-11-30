#include "SummationNode.h"

SummationNode::SummationNode(Point position)
	: Node(position, Point(150.f, 260.f), COLOR_GREEN, COLOR_ABLACK)
{
	// add in the connectors
	const Point origin(20.f, 60.f);
	const Point offset(0.f, 25.f);
	for (int i = 0; i < MAX_INPUTS; i++)
	{
		inputs[i] = new InputConnector(origin + (i * offset), Point(15.f, 15.f), COLOR_YELLOW, this, inputConnected);
		addChild(inputs[i]);
	}

	output = new OutputConnector(Point(120.f, 100.f), Point(20.f, 20.f), COLOR_CORNFLOWERBLUE, this);
	addChild(output);

	summation = new SignalSummation();
}

void SummationNode::inputConnected(Synthadeus * app, Component * connector)
{
}

void SummationNode::updateConnected()
{
}

Renderable * SummationNode::getRenderList()
{
	Renderable* nodeRenderList = Node::getRenderList();
	Renderable* titleText = new Text("Summation", getOrigin(), Point(150.f, 40.f), FONT_ARIAL20, COLOR_WHITE);
	Renderable* inputText = new Text("Inputs", getOrigin() + Point(10.f, 40.f), Point(30.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	Renderable* outputText = new Text("Output", getOrigin() + Point(110.f, 80.f), Point(40.f, 20.f), FONT_ARIAL11, COLOR_WHITE);

	nodeRenderList->next = titleText;
	titleText->next = inputText;
	inputText->next = outputText;
	return nodeRenderList;
}
