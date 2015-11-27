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

#define AUDIO_DEVICE (Pa_GetHostApiInfo(Pa_HostApiTypeIdToHostApiIndex(paASIO))->defaultOutputDevice)

class AudioOutputNode;

class AudioPlayback
{
private:
	AudioOutputNode* node;
	InputDevice::Piano* vPiano;

	PaStream* stream;

	bool initialized;

	// tuned for A4 to be 440 Hz
	inline float getFrequencyForNote(int note) { return AUDIO_TUNE_FREQUENCY * fpowf(1.0594631f, (note - AUDIO_TUNE_NOTE)); };
	float thetas[InputDevice::Piano::TOTAL_KEYS];

public:
	AudioPlayback(AudioOutputNode* outputNode, InputDevice::Piano* virtualPiano);
	bool initialize();
	bool deinitialize();
	inline bool isInitialized() { return initialized; };
	static int AudioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userdata);
	void updateTheta(int key);
};