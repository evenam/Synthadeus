#pragma once

#include "AudioNode.h"

// Exponential envelopes go from volume1 to volume2 for duration
// head is the s before it kicks in, tail is the s before it resets
// equation: from t=0 to t=head, value=volume1
// equation: from t=head to t=tail, 
// equation: from t=duration to t=tail, value=volume2
class BezierEnvelope : public AudioNode
{
private:
	float volume1;
	float volume2;
	float head;
	float duration;
	float tail;
	float exp;

	float bezier3(float t); // 3 point bezier curve
	float lerp(float t); // lerp X and Y in the "curve box"

	int calculatePhase();

public:
	// TODO: implement
	BezierEnvelope(float volume1, float volume2, float head, float duration, float tail, float exp, AudioNode* expModulator);
	virtual void recalculate();