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

class ExponentialEnvelope : public AudioNode
{
private:
	float length;
	float exponent;
	float minimumVolume;
	float maximumVolume;

	AudioNode* minimumModulator;
	AudioNode* maximumModulator;
	AudioNode* exponentModulator;
	AudioNode* lengthModulator;

	int calculatePhase();
	void calculateBuffer();

	float calcLengthL(int sample);
	float calcLengthR(int sample);

	float calcExponentL(int sample);
	float calcExponentR(int sample);

	float calcMinVolL(int sample);
	float calcMinVolR(int sample);

	float calcMaxVolL(int sample);
	float calcMaxVolR(int sample);

	//float positiveExponentFunction(float t) { return -fpowf(t, e) }

public:
	RTTI_MACRO(ExponentialEnvelope);
	ExponentialEnvelope(float len = 440.f, float exp = 1.f, float minVol = 0.f, float maxVol = 1.f, 
		AudioNode* lenMod = NULL, AudioNode* expMod = NULL, AudioNode* minMod = NULL, AudioNode* maxMod = NULL);

	inline float getMinimumVolume() { return minimumVolume; }
	inline float getMaximumVolume() { return maximumVolume; }
	inline float getExponent() { return exponent; }
	inline float getLength() { return length; }

	inline void setMinimumVolume(float minVolume) { minimumVolume = minVolume; }
	inline void setMaximumVolume(float maxVolume) { maximumVolume = maxVolume; }
	inline void setExponent(float exp) { exponent = exp; }
	inline void setLength(float len) { length = len; }

	inline AudioNode* getLengthMod() { return lengthModulator; }
	inline AudioNode* getExponentMod() { return exponentModulator; }
	inline AudioNode* getMinimumMod() { return minimumModulator; }
	inline AudioNode* getMaximumMod() { return maximumModulator; }

	inline void setLengthMod(AudioNode* lenMod) { lengthModulator = lenMod; }
	inline void setExponentMod(AudioNode* expMod) { exponentModulator = expMod; }
	inline void setMinimumMod(AudioNode* minMod) { minimumModulator = minMod; }
	inline void setMaximumMod(AudioNode* maxMod) { maximumModulator = maxMod; }

	virtual void recalculate();
};
