#include "AudioOutputNode.h"

AudioOutputNode::AudioOutputNode(Point audioOutputNodeOrigin)
	: Node(audioOutputNodeOrigin, Point(200.f, 60.f), COLOR_PINK, COLOR_ABLACK, false)
{
	input = new InputConnector(Point(20.f, 20.f), Point(20.f, 20.f), COLOR_PINK, this);
	addChild(input);

	defaultValue = new AudioConstant(0.f);
}

AudioNode* AudioOutputNode::getAudioNode()
{
	// default if we aren't connected
	if (input->isConnected() <= 0)
		return defaultValue;

	// else return the real one (once hooked up)
	return defaultValue;
}

Renderable * AudioOutputNode::getRenderList()
{
	Renderable* nodeRenderables = Node::getRenderList();
	Text* outputText = new Text("Output Endpoint", Point(70.f, 10.f) + getOrigin(), Point(120.f, 40.f), FONT_ARIAL20, COLOR_WHITE);
	nodeRenderables->next = outputText;
	return nodeRenderables;
}
