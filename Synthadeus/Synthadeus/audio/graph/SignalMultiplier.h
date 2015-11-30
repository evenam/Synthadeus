////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Signal Multiplier                                                        //
//   Everett Moser                                                            //
//   11-29-15                                                                 //
//                                                                            //
//   Intensifies or diminishes a signal                                       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AudioNode.h"

class SignalMultiplier : public AudioNode
{
private:

	// the signal to intensify or diminish
	AudioNode* input;

	// the coefficient to diminish it by
	float value;

	// calculate the buffers
	void calculateBuffer();

public:

	// run time type information
	RTTI_MACRO(SignalMultiplier);

	// initialize the signal mulitplier with a potential value and input
	SignalMultiplier(float signalValue = 1.f, AudioNode* inputNode = NULL);

	// update to a new input source
	void setInput(AudioNode* inputNode);

	// set the multiplier coefficient to a new value
	void setValue(float signalValue);

	// get the current input signal
	inline AudioNode* getInput() { return input; }

	// get the current coefficient
	inline float getValue() { return value; }

	// recalculate the buffers
	virtual void recalculate();
};

