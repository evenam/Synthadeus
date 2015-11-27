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

#include "AudioNode.h"
#include "Error.h"
#include "InputDevice.h"

#pragma comment(lib, "portaudio_x86.lib")

class AudioOutputNode;
typedef float(AudioOutputNode::*AudioGenerator)(float);

class AudioPlayback
{
private:
	AudioGenerator left, right;
	InputDevice::Piano* vPiano;

	// tuned for A4 to be 440 Hz
	inline float getFrequencyForNote(int note) { return 440.f * fpowf(1.0594631f, (note - 69)); };

	float thetas[InputDevice::Piano::OCTAVES][InputDevice::Piano::KEYS];

public:
	AudioPlayback(AudioGenerator leftGenerator, AudioGenerator rightGenerator, InputDevice::Piano* virtualPiano);
	void initialize();
	void deinitialize();
};