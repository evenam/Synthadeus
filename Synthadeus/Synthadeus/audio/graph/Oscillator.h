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
	
	// the kinds of waveforms we can have
	enum WAVEFORM { SINE, SAW, SQUARE };
	
	// tun time type information
	RTTI_MACRO(Oscillator);

private:

	// modulating parameters
	AudioNode* frequencyMod;
	AudioNode* volumeMod;
	AudioNode* panningMod;

	// constant parameters
	float frequency;
	float volume;
	float panning;

	// the waveform generated
	WAVEFORM waveform;

	// calculate the length needed to store the wave
	int calculatePhase();

	// calculate the buffer contents
	void calcBuffer();

	// calculate the left panning based on constant and modulated values
	float calcPanL(int sample);

	// calculate the right panning based on constant and modulated values
	float calcPanR(int sample);

	// calculate the left volume based on constant and modulated values
	float calcVolumeL(int sample);

	// calculate the right volume based on constant and modulated values
	float calcVolumeR(int sample);

	// calculate the left frequency based on constant and modulated values
	float calcFrequencyL(int sample);

	// calculate the right frequency based on constant and modulated values
	float calcFrequencyR(int sample);

	// saw generator function
	inline float sawf(float theta) { return (-1.f / 3.14159f) * theta + 1.f; }

	// square generator function
	inline float sqrf(float theta) { return 1.f - 2.f * (theta > 3.14159f ? 1.f : 0.f); }

public:

	// construct an oscillator, possibly specifying a certain number of the parameters
	Oscillator(WAVEFORM wave = SINE, float freq = 440.f, float vol = 1.f, float pan = 0.f,
		AudioNode* freqMod = NULL, AudioNode* volMod = NULL, AudioNode* panMod = NULL);

	// set a new frequency modulator
	void setFrequencyModulator(AudioNode* freqMod);

	// set a new volume modulator
	void setVolumeModulator(AudioNode* volMod);

	// set a new panning modulator
	void setPanningModulator(AudioNode* panMod);

	// set the new default frequency
	void setFrequency(float freq);

	// set the new default volume
	void setVolume(float vol);

	// set the new default panning
	void setPanning(float pan);

	// set the waveform
	void setWaveform(WAVEFORM wave);

	// get the current frequencyu modulator
	AudioNode* getFrequencyModulator();
	
	// get the current panning modulator
	AudioNode* getPanningModulator();

	// get the current volume modulator
	AudioNode* getVolumeModulator();

	// get the current waveform generated
	WAVEFORM getWaveform();

	// get the current default frequency
	float getFrequency();

	// get the current default panning 
	float getPanning();

	// get the current default volume
	float getVolume();

	// recalculate the buffers
	virtual void recalculate();
};