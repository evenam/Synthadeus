#include "OscillatorNode.h"
#include "Synthadeus.h"

OscillatorNode::OscillatorNode(Point position)
	: Node(position, Point(300.f, 190.f), COLOR_YELLOW, COLOR_ABLACK)
{
	// create and add the frequency slider
	frequencySlider = new Slider(Point(10.f, 65.f), Point(100.f, 15.f), COLOR_NONE, COLOR_CORNFLOWERBLUE, Slider::HORIZONTAL, 0.25f, 1000.f, 440.f, 0.25f, onFrequencyChanged);
	addChild(frequencySlider);

	// create and add the frequency input connector
	frequencyModulator = new InputConnector(Point(10.f, 40.f), Point(15.f, 15.f), COLOR_CORNFLOWERBLUE, this, onFreqModChanged);
	addChild(frequencyModulator);

	// create and add the volume slider
	volumeSlider = new Slider(Point(10.f, 115.f), Point(100.f, 15.f), COLOR_NONE, COLOR_ORANGE, Slider::HORIZONTAL, -1.f, 1.f, 1.f, 0.001f, onVolumeChanged);
	addChild(volumeSlider);

	// create and add the volume input connector
	volumeModulator = new InputConnector(Point(10.f, 90.f), Point(15.f, 15.f), COLOR_ORANGE, this, onVolModChanged);
	addChild(volumeModulator);

	// create and add the panning slider
	panningSlider = new Slider(Point(10.f, 165.f), Point(100.f, 15.f), COLOR_NONE, COLOR_CYAN, Slider::HORIZONTAL, -1.f, 1.f, 0.f, 0.001f, onPanningChanged);
	addChild(panningSlider);

	// create and add the panning input connector
	panningModulator = new InputConnector(Point(10.f, 140.f), Point(15.f, 15.f), COLOR_CYAN, this, onPanModChanged);
	addChild(panningModulator);

	// create and add the output connector
	oscOutput = new OutputConnector(Point(270.f, 90.f), Point(20.f, 20.f), COLOR_RED, this);
	addChild(oscOutput);

	// create and add the buttons to alter the waveform
	btnSine = new Button(Point(120.f, 60.f), Point(100.f, 30.f), COLOR_ABLACK, COLOR_MAGENTA, "Sine", FONT_ARIAL11, onSineClick);
	addChild(btnSine);
	btnSaw = new Button(Point(120.f, 105.f), Point(100.f, 30.f), COLOR_ABLACK, COLOR_MAGENTA, "Saw", FONT_ARIAL11, onSawClick);
	addChild(btnSaw);
	btnSquare = new Button(Point(120.f, 150.f), Point(100.f, 30.f), COLOR_ABLACK, COLOR_MAGENTA, "Square", FONT_ARIAL11, onSquareClick);
	addChild(btnSquare);

	// create the underlying oscillator to this "large" UI
	oscillator = new Oscillator();
}

Renderable * OscillatorNode::getRenderList()
{
	// get the base set of renderables
	Renderable* nodeRenderables = Node::getRenderList();

	/// create some titles
	Renderable* titleText = new Text("Oscillator", getOrigin(), Point(300.f, 40.f), FONT_ARIAL20, COLOR_WHITE);
	Renderable* frequencyText = new Text("Frequency", getOrigin() + Point(35.f, 40.f), Point(65.f, 15.f), FONT_ARIAL11, COLOR_WHITE);
	Renderable* volumeText = new Text("Volume", getOrigin() + Point(35.f, 90.f), Point(65.f, 15.f), FONT_ARIAL11, COLOR_WHITE);
	Renderable* panningText = new Text("Panning", getOrigin() + Point(35.f, 140.f), Point(65.f, 15.f), FONT_ARIAL11, COLOR_WHITE);
	Renderable* outputText = new Text("Output", getOrigin() + Point(220.f, 90.f), Point(50.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	
	// waveform title is set to the actual value of the oscillator waveform
	Renderable* waveformText = NULL;
	assert(oscillator != NULL);
	if (oscillator->getWaveform() == Oscillator::SINE)
		waveformText = new Text("Sine", getOrigin() + Point(120.f, 40.f), Point(100.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	else if (oscillator->getWaveform() == Oscillator::SAW)
		waveformText = new Text("Saw", getOrigin() + Point(120.f, 40.f), Point(100.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	else if (oscillator->getWaveform() == Oscillator::SQUARE)
		waveformText = new Text("Square", getOrigin() + Point(120.f, 40.f), Point(100.f, 20.f), FONT_ARIAL11, COLOR_WHITE);
	
	// idiot test
	assert(waveformText != NULL);

	// construct the list
	nodeRenderables->next = titleText;
	titleText->next = frequencyText;
	frequencyText->next = volumeText;
	volumeText->next = panningText;
	panningText->next = outputText;
	outputText->next = waveformText;
	
	// return the result
	return nodeRenderables;
}

void OscillatorNode::onFreqModChanged(Synthadeus * app, Component * me)
{
	// resolve the idenitity crisis
	OscillatorNode* myself = (OscillatorNode*)(me->getParent());

	// figure out the culprit
	AudioUINode* other = dynamic_cast<AudioUINode*>(((InputConnector*)me)->getConnectionParent());

	// apply the connection and update
	myself->connectFrequency(other);
	DebugPrintf("Connected %s to %s\n",(((InputConnector*)me)->getConnectionParent() ? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"), myself->getClassName());
	app->recalculateAudioGraph();
}

void OscillatorNode::onVolModChanged(Synthadeus * app, Component * me)
{
	// resolve the idenitity crisis
	OscillatorNode* myself = (OscillatorNode*)(me->getParent());

	// figure out the culprit
	AudioUINode* other = dynamic_cast<AudioUINode*>(((InputConnector*)me)->getConnectionParent());

	// apply the connection and update
	myself->connectVolume(other);
	DebugPrintf("Connected %s to %s\n", (((InputConnector*)me)->getConnectionParent() ? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"), myself->getClassName());
	app->recalculateAudioGraph();
}

void OscillatorNode::onPanModChanged(Synthadeus * app, Component * me)
{
	// resolve the idenitity crisis
	OscillatorNode* myself = (OscillatorNode*)(me->getParent());

	// figure out the culprit
	AudioUINode* other = dynamic_cast<AudioUINode*>(((InputConnector*)me)->getConnectionParent());

	// apply the connection and update
	myself->connectPanning(other);
	DebugPrintf("Connected %s to %s\n", (((InputConnector*)me)->getConnectionParent() ? ((InputConnector*)me)->getConnectionParent()->getClassName() : "NULL"), myself->getClassName());
	app->recalculateAudioGraph();
}

void OscillatorNode::onFrequencyChanged(Synthadeus * app, Component * me)
{
	// resolve the idenitity crisis
	OscillatorNode* myself = dynamic_cast<OscillatorNode*>(me->getParent());

	// apply the changes and update
	myself->updateNodeConstants();
	app->recalculateAudioGraph();
}

void OscillatorNode::onVolumeChanged(Synthadeus * app, Component * me)
{
	// resolve the idenitity crisis
	OscillatorNode* myself = dynamic_cast<OscillatorNode*>(me->getParent());

	// apply the changes and update
	myself->updateNodeConstants();
	app->recalculateAudioGraph();
}

void OscillatorNode::onPanningChanged(Synthadeus * app, Component * me)
{
	// resolve the idenitity crisis
	OscillatorNode* myself = dynamic_cast<OscillatorNode*>(me->getParent());

	// apply the changes and update
	myself->updateNodeConstants();
	app->recalculateAudioGraph();
}

void OscillatorNode::onSineClick(Synthadeus * app, Component * me)
{
	// resolve the idenitity crisis
	OscillatorNode* myself = (OscillatorNode*)me;

	// apply the changes and update
	((Oscillator*)(myself->getAudioNode()))->setWaveform(Oscillator::SINE);
	app->recalculateAudioGraph();
}

void OscillatorNode::onSawClick(Synthadeus * app, Component * me)
{
	// resolve the idenitity crisis
	OscillatorNode* myself = (OscillatorNode*)me;

	// apply the changes and update
	((Oscillator*)(myself->getAudioNode()))->setWaveform(Oscillator::SAW);
	app->recalculateAudioGraph();
}

void OscillatorNode::onSquareClick(Synthadeus * app, Component * me)
{
	// resolve the idenitity crisis
	OscillatorNode* myself = (OscillatorNode*)me;

	// apply the changes and update
	((Oscillator*)(myself->getAudioNode()))->setWaveform(Oscillator::SQUARE);
	app->recalculateAudioGraph();
}

AudioNode* OscillatorNode::getAudioNode()
{
	// return the idiot proof'd underlying oscillators
	assert(oscillator != NULL);
	return oscillator;
}

void OscillatorNode::updateNodeConstants()
{
	// get the slider values
	float frequency = frequencySlider->getValue();
	float volume = volumeSlider->getValue();
	float panning = panningSlider->getValue();

	// update the oscillator values
	oscillator->setFrequency(frequency);
	oscillator->setVolume(volume);
	oscillator->setPanning(panning);
}

void OscillatorNode::connectFrequency(AudioUINode * other)
{
	// update if this is a new connection
	if (other)
		oscillator->setFrequencyModulator(other->getAudioNode());

	// else update the disconnect
	else
		oscillator->setFrequencyModulator(NULL);
}

void OscillatorNode::connectVolume(AudioUINode * other)
{
	// update if this is a new connection
	if (other)
		oscillator->setVolumeModulator(other->getAudioNode());

	// else update the disconnect
	else
		oscillator->setVolumeModulator(NULL);
}

void OscillatorNode::connectPanning(AudioUINode * other)
{
	// update if this is a new connection
	if (other)
		oscillator->setPanningModulator(other->getAudioNode());

	// else update the disconnect
	else
		oscillator->setPanningModulator(NULL);
}

