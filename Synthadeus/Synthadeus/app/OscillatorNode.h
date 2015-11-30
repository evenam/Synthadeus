////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   The Oscillator Node                                                      //
//   Everett Moser                                                            //
//   11-26-15                                                                 //
//                                                                            //
//   A placeable node which creates an oscillator in the audio graph          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Component.h"
#include "Node.h"
#include "Slider.h"
#include "Button.h"
#include "Connector.h"
#include "Oscillator.h"

class OscillatorNode : public Node, public AudioUINode
{
	// sliders to modify oscillator base values
	Slider *frequencySlider, *volumeSlider, *panningSlider;

	// buttons to modify the wave form type
	Button *btnSaw, *btnSquare, *btnSine;

	// connectors to the inputs for modulating oscillator parameters
	InputConnector *frequencyModulator, *volumeModulator, *panningModulator;

	// connection to the next node in the graph
	OutputConnector *oscOutput;

	// the oscillator node which this UI represents
	Oscillator* oscillator;

public:

	// run time type information
	RTTI_MACRO(OscillatorNode);

	// create the node at a specific point
	OscillatorNode(Point position);

	// get the render list for this node
	virtual Renderable* getRenderList();

	// callback for a new frequency modulation connection
	static void onFreqModChanged(Synthadeus* app, Component* me);

	// callback for a new volume modulation connection
	static void onVolModChanged(Synthadeus* app, Component* me);

	// callback for a new panning modulation connection
	static void onPanModChanged(Synthadeus* app, Component* me);

	// callback for a new frequency value
	static void onFrequencyChanged(Synthadeus* app, Component* me);

	// callback for a new volume value
	static void onVolumeChanged(Synthadeus* app, Component* me);

	// callback for a new panning value
	static void onPanningChanged(Synthadeus* app, Component* me);

	// callback for changing the waveform to sine
	static void onSineClick(Synthadeus* app, Component* me);

	// callback for changing the waveform to saw
	static void onSawClick(Synthadeus* app, Component* me);

	// callback for changing the waveform to square
	static void onSquareClick(Synthadeus* app, Component* me);

	// refers to the underlying oscillator
	virtual AudioNode* getAudioNode();

	// update the constant values from the sliders
	void updateNodeConstants();

	// update the frequency modulator connection 
	void connectFrequency(AudioUINode* other);

	// update the volume modulator connection 
	void connectVolume(AudioUINode* other);

	// update the panning modulator connection 
	void connectPanning(AudioUINode* other);

	// free the oscillator before we get deleted
	virtual inline void onDestroy() { delete oscillator; }
};

