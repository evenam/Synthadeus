////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Oscillator Node                                                          //
//   Everett Moser                                                            //
//   11-23-15                                                                 //
//                                                                            //
//   An audio graph node for creating the fundemental audio oscillator        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AudioNode.h"

class Oscillator : public AudioNode
{
public:
	enum WAVEFORM { SINE, SAW, SQUARE };
	RTTI_MACRO(Oscillator);

private:
	AudioNode* frequencyMod;
	AudioNode* volumeMod;
	AudioNode* panningMod;

	float frequency;
	float volume;
	float panning;
	WAVEFORM waveform;

	int calculatePhase();
	void calcBuffer();

	float calcPanL(int sample);
	float calcPanR(int sample);
	float calcVolumeL(int sample);
	float calcVolumeR(int sample);
	float calcFrequencyL(int sample);
	float calcFrequencyR(int sample);

	inline float sawf(float theta) { return (-1.f / 3.14159f) * theta + 1.f; }
	inline float sqrf(float theta) { return 1.f - 2.f * (theta > 3.14159f ? 1.f : 0.f); }

public:
	Oscillator(WAVEFORM wave = SINE, float freq = 440.f, float vol = 1.f, float pan = 0.f,
		AudioNode* freqMod = NULL, AudioNode* volMod = NULL, AudioNode* panMod = NULL);

	void setFrequencyModulator(AudioNode* freqMod);
	void setVolumeModulator(AudioNode* volMod);
	void setPanningModulator(AudioNode* panMod);

	void setFrequency(float freq);
	void setVolume(float vol);
	void setPanning(float pan);
	void setWaveform(WAVEFORM wave);

	AudioNode* getFrequencyModulator();
	AudioNode* getPanningModulator();
	AudioNode* getVolumeModulator();

	WAVEFORM getWaveform();
	float getFrequency();
	float getPanning();
	float getVolume();

	virtual void recalculate();
};