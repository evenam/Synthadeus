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
	Slider *frequencySlider, *volumeSlider, *panningSlider;
	Button *btnSaw, *btnSquare, *btnSine;
	InputConnector *frequencyModulator, *volumeModulator, *panningModulator;
	OutputConnector *oscOutput;

	Oscillator* oscillator;

public:
	OscillatorNode(Point position);
	RTTI_MACRO(OscillatorNode);

	virtual Renderable* getRenderList();
	// callbacks for various functionality
	static void onFreqModChanged(Synthadeus* app, Component* me);
	static void onVolModChanged(Synthadeus* app, Component* me);
	static void onPanModChanged(Synthadeus* app, Component* me);
	static void onFrequencyChanged(Synthadeus* app, Component* me);
	static void onVolumeChanged(Synthadeus* app, Component* me);
	static void onPanningChanged(Synthadeus* app, Component* me);
	static void onSineClick(Synthadeus* app, Component* me);
	static void onSawClick(Synthadeus* app, Component* me);
	static void onSquareClick(Synthadeus* app, Component* me);

	virtual AudioNode* getAudioNode();
	void updateNodeConstants();

	void connectFrequency(AudioUINode* other);
	void connectVolume(AudioUINode* other);
	void connectPanning(AudioUINode* other);

	virtual inline void onDestroy() { delete oscillator; }
};

