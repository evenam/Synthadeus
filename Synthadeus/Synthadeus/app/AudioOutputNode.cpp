#include "AudioOutputNode.h"
#include "Synthadeus.h"

AudioOutputNode::AudioOutputNode(Point audioOutputNodeOrigin)
	: Node(audioOutputNodeOrigin, Point(200.f, 60.f), COLOR_PINK, COLOR_ABLACK, false)
{
	input = new InputConnector(Point(20.f, 20.f), Point(20.f, 20.f), COLOR_PINK, this, onConnected);
	addChild(input);

	defaultValue = new AudioConstant(0.f);
	outputNode = NULL;
}

AudioNode* AudioOutputNode::getAudioNode()
{
	// default if we aren't connected
	if (input->isConnected() > 0)
	{
		return outputNode;
	}

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

void AudioOutputNode::onConnected(Synthadeus * app, Component * me)
{
	AudioOutputNode* myself = (AudioOutputNode*)((InputConnector*)me)->getParent();
	AudioUINode* other = dynamic_cast<AudioUINode*>(((InputConnector*)me)->getConnectionParent());
	DebugPrintf("Connecting %s to %s\n", me->getClassName(), (other? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"));
	myself->setOutputNode(other);
	app->recalculateAudioGraph();
}

void AudioOutputNode::setOutputNode(AudioUINode * node)
{
	if (node)
		outputNode = node->getAudioNode();
	else
		outputNode = NULL;
}
