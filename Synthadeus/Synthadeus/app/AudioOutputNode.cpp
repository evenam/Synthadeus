#include "AudioOutputNode.h"
#include "Synthadeus.h"

AudioOutputNode::AudioOutputNode(Point audioOutputNodeOrigin)
	: Node(audioOutputNodeOrigin, Point(200.f, 60.f), COLOR_PINK, COLOR_ABLACK, false)
{
	// the input connector which will connect the node to the final point in the graph
	input = new InputConnector(Point(20.f, 20.f), Point(20.f, 20.f), COLOR_PINK, this, onConnected);
	addChild(input);

	// a default 0 to feed the audio playback mechanism
	defaultValue = new AudioConstant(0.f);
	
	// local reference to the final node
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
	// get the base renderables
	Renderable* nodeRenderables = Node::getRenderList();

	// create a snazzy title
	Text* outputText = new Text("Output Endpoint", Point(70.f, 10.f) + getOrigin(), Point(120.f, 40.f), FONT_ARIAL20, COLOR_WHITE);
	
	// append the title, return the list
	nodeRenderables->next = outputText;
	return nodeRenderables;
}

void AudioOutputNode::onConnected(Synthadeus * app, Component * me)
{
	// resolve the identity crisis
	AudioOutputNode* myself = (AudioOutputNode*)((InputConnector*)me)->getParent();

	// figure out who the culprit is
	AudioUINode* other = dynamic_cast<AudioUINode*>(((InputConnector*)me)->getConnectionParent());

	// update myself with the appropriate data to provide some nice audio playback
	DebugPrintf("Connecting %s to %s\n", me->getClassName(), (other? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"));
	myself->setOutputNode(other);

	// update the graph
	app->recalculateAudioGraph();
}

void AudioOutputNode::setOutputNode(AudioUINode* node)
{
	// update our local reference, NULL if we are disconnected
	if (node)
		outputNode = node->getAudioNode();
	else
		outputNode = NULL;
}
