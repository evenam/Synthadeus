#include "OscillatorNode.h"
#include "Synthadeus.h"

OscillatorNode::OscillatorNode(Point position)
	: Node(position, Point(300.f, 190.f), COLOR_YELLOW, COLOR_ABLACK)
{
	frequencySlider = new Slider(Point(10.f, 65.f), Point(100.f, 15.f), COLOR_NONE, COLOR_CORNFLOWERBLUE, Slider::HORIZONTAL, 0.25f, 1000.f, 440.f, 0.25f, onFrequencyChanged);
	addChild(frequencySlider);
	frequencyModulator = new InputConnector(Point(10.f, 40.f), Point(15.f, 15.f), COLOR_CORNFLOWERBLUE, this, onFreqModChanged);
	addChild(frequencyModulator);
	volumeSlider = new Slider(Point(10.f, 115.f), Point(100.f, 15.f), COLOR_NONE, COLOR_ORANGE, Slider::HORIZONTAL, -1.f, 1.f, 1.f, 0.001f, onVolumeChanged);
	addChild(volumeSlider);
	volumeModulator = new InputConnector(Point(10.f, 90.f), Point(15.f, 15.f), COLOR_ORANGE, this, onVolModChanged);
	addChild(volumeModulator);
	panningSlider = new Slider(Point(10.f, 165.f), Point(100.f, 15.f), COLOR_NONE, COLOR_CYAN, Slider::HORIZONTAL, -1.f, 1.f, 0.f, 0.001f, onPanningChanged);
	addChild(panningSlider);
	panningModulator = new InputConnector(Point(10.f, 140.f), Point(15.f, 15.f), COLOR_CYAN, this, onPanModChanged);
	addChild(panningModulator);
	oscOutput = new OutputConnector(Point(270.f, 90.f), Point(20.f, 20.f), COLOR_RED, this);
	addChild(oscOutput);
	btnSine = new Button(Point(120.f, 60.f), Point(100.f, 30.f), COLOR_ABLACK, COLOR_MAGENTA, "Sine", FONT_ARIAL11, onSineClick);
	addChild(btnSine);
	btnSaw = new Button(Point(120.f, 105.f), Point(100.f, 30.f), COLOR_ABLACK, COLOR_MAGENTA, "Saw", FONT_ARIAL11, onSawClick);
	addChild(btnSaw);
	btnSquare = new Button(Point(120.f, 150.f), Point(100.f, 30.f), COLOR_ABLACK, COLOR_MAGENTA, "Square", FONT_ARIAL11, onSquareClick);
	addChild(btnSquare);

	oscillator = new Oscillator();
}

Renderable * OscillatorNode::getRenderList()
{
	Renderable* nodeRenderables = Node::getRenderList();
	Renderable* titleText = new Text("Oscillator", getOrigin(), Point(300.f, 40.f), FONT_ARIAL20, COLOR_WHITE);
	Renderable* frequencyText = new Text("Frequency", getOrigin() + Point(35.f, 40.f), Point(65.f, 15.f), FONT_ARIAL11, COLOR_WHITE);
	Renderable* volumeText = new Text("Volume", getOrigin() + Point(35.f, 90.f), Point(65.f, 15.f), FONT_ARIAL11, COLOR_WHITE);
	Renderable* panningText = new Text("Panning", getOrigin() + Point(35.f, 140.f), Point(65.f, 15.f), FONT_ARIAL11, COLOR_WHITE);
	Renderable* outputText = new Text("Output", getOrigin() + Point(220.f, 90.f), Point(50.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	Renderable* waveformText = NULL;
	assert(oscillator != NULL);
	if (oscillator->getWaveform() == Oscillator::SINE)
		waveformText = new Text("Sine", getOrigin() + Point(120.f, 40.f), Point(100.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	else if (oscillator->getWaveform() == Oscillator::SAW)
		waveformText = new Text("Saw", getOrigin() + Point(120.f, 40.f), Point(100.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	else if (oscillator->getWaveform() == Oscillator::SQUARE)
		waveformText = new Text("Square", getOrigin() + Point(120.f, 40.f), Point(100.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	
	assert(waveformText != NULL);
	nodeRenderables->next = titleText;
	titleText->next = frequencyText;
	frequencyText->next = volumeText;
	volumeText->next = panningText;
	panningText->next = outputText;
	outputText->next = waveformText;
	
	return nodeRenderables;
}

void OscillatorNode::onFreqModChanged(Synthadeus * app, Component * me)
{
	OscillatorNode* myself = (OscillatorNode*)(me->getParent());
	AudioUINode* other = dynamic_cast<AudioUINode*>(((InputConnector*)me)->getConnectionParent());
	myself->connectFrequency(other);
	DebugPrintf("Connected %s to %s\n",(((InputConnector*)me)->getConnectionParent() ? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"), myself->getClassName());
	app->recalculateAudioGraph();
}

void OscillatorNode::onVolModChanged(Synthadeus * app, Component * me)
{
	OscillatorNode* myself = (OscillatorNode*)(me->getParent());
	AudioUINode* other = dynamic_cast<AudioUINode*>(((InputConnector*)me)->getConnectionParent());
	myself->connectVolume(other);
	DebugPrintf("Connected %s to %s\n", (((InputConnector*)me)->getConnectionParent() ? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"), myself->getClassName());
	myself->oscillator->recalculate();
	app->recalculateAudioGraph();
}

void OscillatorNode::onPanModChanged(Synthadeus * app, Component * me)
{
	OscillatorNode* myself = (OscillatorNode*)(me->getParent());
	AudioUINode* other = dynamic_cast<AudioUINode*>(((InputConnector*)me)->getConnectionParent());
	myself->connectPanning(other);
	DebugPrintf("Connected %s to %s\n", (((InputConnector*)me)->getConnectionParent() ? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"), myself->getClassName());
	app->recalculateAudioGraph();
}

void OscillatorNode::onFrequencyChanged(Synthadeus * app, Component * me)
{
	OscillatorNode* myself = dynamic_cast<OscillatorNode*>(me->getParent());
	myself->updateNodeConstants();
	myself->oscillator->recalculate();
	app->recalculateAudioGraph();
}

void OscillatorNode::onVolumeChanged(Synthadeus * app, Component * me)
{
	OscillatorNode* myself = dynamic_cast<OscillatorNode*>(me->getParent());
	myself->updateNodeConstants();
	app->recalculateAudioGraph();
}

void OscillatorNode::onPanningChanged(Synthadeus * app, Component * me)
{
	OscillatorNode* myself = dynamic_cast<OscillatorNode*>(me->getParent());
	myself->updateNodeConstants();
	app->recalculateAudioGraph();
}

void OscillatorNode::onSineClick(Synthadeus * app, Component * me)
{
	OscillatorNode* myself = (OscillatorNode*)me;
	((Oscillator*)(myself->getAudioNode()))->setWaveform(Oscillator::SINE);
	app->recalculateAudioGraph();
}

void OscillatorNode::onSawClick(Synthadeus * app, Component * me)
{
	OscillatorNode* myself = (OscillatorNode*)me;
	((Oscillator*)(myself->getAudioNode()))->setWaveform(Oscillator::SAW);
	app->recalculateAudioGraph();
}

void OscillatorNode::onSquareClick(Synthadeus * app, Component * me)
{
	OscillatorNode* myself = (OscillatorNode*)me;
	((Oscillator*)(myself->getAudioNode()))->setWaveform(Oscillator::SQUARE);
	app->recalculateAudioGraph();
}

AudioNode* OscillatorNode::getAudioNode()
{
	assert(oscillator != NULL);
	return oscillator;
}

void OscillatorNode::updateNodeConstants()
{
	float frequency = frequencySlider->getValue();
	float volume = volumeSlider->getValue();
	float panning = panningSlider->getValue();
	oscillator->setFrequency(frequency);
	oscillator->setVolume(volume);
	oscillator->setPanning(panning);
}

void OscillatorNode::connectFrequency(AudioUINode * other)
{
	AudioNode* otherNode = other->getAudioNode();
	oscillator->setFrequencyModulator(otherNode);
}

void OscillatorNode::connectVolume(AudioUINode * other)
{
	AudioNode* otherNode = other->getAudioNode();
	oscillator->setVolumeModulator(otherNode);
}

void OscillatorNode::connectPanning(AudioUINode * other)
{
	AudioNode* otherNode = other->getAudioNode();
	oscillator->setPanningModulator(otherNode);
}

