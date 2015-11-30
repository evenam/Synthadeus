////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Bezier Envelope                                                          //
//   Everett Moser                                                            //
//   11-23-15                                                                 //
//                                                                            //
//   An audio graph node for creating an envelope with one of 2 exponentials  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AudioNode.h"

// !! UNDECORATED UNTIL IMPLEMENTATION !! \\
\\\\\\\\\\\\\\\\\\\\\\//////////////////////

class ExponentialEnvelope : public AudioNode
{
private:
	float length;
	float exponent;
	float minimumVolume;
	float maximumVolume;

	int calculatePhase();

	//float positiveExponentFunction(float t) { return -fpowf(t, ) }

public:
	RTTI_MACRO(ExponentialEnvelope);
	ExponentialEnvelope(float length, float exponent, AudioNode* lenMod, AudioNode* expMod);
	virtual void recalculate();
}