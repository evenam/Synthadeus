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
	AudioNode* input;
	float value;

	void calculateBuffer();
public:
	RTTI_MACRO(SignalMultiplier);
	SignalMultiplier(float signalValue = 1.f, AudioNode* inputNode = NULL);

	void setInput(AudioNode* inputNode);
	void setValue(float signalValue);

	inline AudioNode* getInput() { return input; }
	inline float getValue() { return value; }

	virtual void recalculate();
};

