#include "SummationNode.h"
#include "Synthadeus.h"

SummationNode::SummationNode(Point position)
	: Node(position, Point(150.f, 260.f), COLOR_GREEN, COLOR_ABLACK)
{
	// add in the connectors systematically
	const Point origin(20.f, 60.f);
	const Point offset(0.f, 25.f);
	for (int i = 0; i < MAX_INPUTS; i++)
	{
		inputs[i] = new InputConnector(origin + (i * offset), Point(15.f, 15.f), COLOR_YELLOW, this, inputConnected);
		addChild(inputs[i]);
	}

	// add the output connector
	output = new OutputConnector(Point(120.f, 100.f), Point(20.f, 20.f), COLOR_CORNFLOWERBLUE, this);
	addChild(output);

	// create internal summation
	summation = new SignalSummation();
}

void SummationNode::inputConnected(Synthadeus * app, Component * connector)
{
	// resolve the identity crisis
	SummationNode* myself = (SummationNode*)connector->getParent();

	// update myself and recalculate the graph
	myself->updateConnected();
	app->recalculateAudioGraph();
}

void SummationNode::updateConnected()
{
	// clear the children to start from scratch
	summation->clearChildren();

	// add in each connected component
	for (int i = 0; i < MAX_INPUTS; i++)
	{
		if (inputs[i]->isConnected() > 0)
		{
			AudioUINode* uiNode = dynamic_cast<AudioUINode*>(inputs[i]->getConnectionParent());
			assert(uiNode != NULL);

			// actually the audio nodes
			summation->addChild(uiNode->getAudioNode());
		}
	}
}

Renderable * SummationNode::getRenderList()
{
	// generate the baseclass renderables
	Renderable* nodeRenderList = Node::getRenderList();

	// add in some titles
	Renderable* titleText = new Text("Summation", getOrigin(), Point(150.f, 40.f), FONT_ARIAL20, COLOR_WHITE);
	Renderable* inputText = new Text("Inputs", getOrigin() + Point(10.f, 35.f), Point(30.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	Renderable* outputText = new Text("Output", getOrigin() + Point(110.f, 80.f), Point(40.f, 20.f), FONT_ARIAL11, COLOR_WHITE);

	// construct the list
	nodeRenderList->next = titleText;
	titleText->next = inputText;
	inputText->next = outputText;

	// return the final list
	return nodeRenderList;
}
