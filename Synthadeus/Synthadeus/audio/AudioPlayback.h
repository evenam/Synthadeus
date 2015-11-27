////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Audio Playback Mechanism                                                 //
//   Justin Ross                                                              //
//   11-20-15                                                                 //
//                                                                            //
//   Connects the Audio Graph to Port Audio, linearly resampling as needed    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "portaudio.h"
#include "pa_asio.h"

#include "Error.h"
#include "InputDevice.h"
#include "CFMaths.h"
#include "AudioDefines.h"

#pragma comment(lib, "portaudio_x86.lib")

class AudioOutputNode;

class AudioPlayback
{
private:
	AudioOutputNode* node;
	InputDevice::Piano* vPiano;

	bool initialized = false;

	// tuned for A4 to be 440 Hz
	inline float getFrequencyForNote(int note) { return AUDIO_TUNE_FREQUENCY * fpowf(1.0594631f, (note - AUDIO_TUNE_NOTE)); };

	float thetas[InputDevice::Piano::OCTAVES][InputDevice::Piano::KEYS];

public:
	AudioPlayback(AudioOutputNode* outputNode, InputDevice::Piano* virtualPiano);
	bool initialize();
	bool deinitialize();
	inline bool isInitialized() { return initialized; };
};