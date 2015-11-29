#include "AudioOutputNode.h"

AudioOutputNode::AudioOutputNode(Point audioOutputNodeOrigin)
	: Node(audioOutputNodeOrigin, Point(200.f, 60.f), COLOR_PINK, COLOR_CORNFLOWERBLUE, false)
{
	input = new InputConnector(Point(20.f, 20.f), Point(20.f, 20.f), COLOR_PINK, this);
	addChild(input);

	testOscillator = new Oscillator(Oscillator::SAW, 440.f, 1.f, 0.f, new Oscillator(Oscillator::SINE, 1.f, 1.f, 0.f));
}

AudioNode* AudioOutputNode::getAudioNode()
{
	return testOscillator;
}

Renderable * AudioOutputNode::getRenderList()
{
	Renderable* nodeRenderables = Node::getRenderList();
	Text* outputText = new Text("Output Endpoint", Point(70.f, 10.f) + getOrigin(), Point(120.f, 40.f), FONT_ARIAL20, COLOR_WHITE);
	nodeRenderables->next = outputText;
	return nodeRenderables;
}
