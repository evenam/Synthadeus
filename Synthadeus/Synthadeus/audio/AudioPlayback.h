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

// easy macro to get the default device
#define AUDIO_DEVICE (Pa_GetHostApiInfo(Pa_HostApiTypeIdToHostApiIndex(paASIO))->defaultOutputDevice)

class AudioOutputNode;
class AudioPlayback
{
private:
	// the audio endpoint in the graph
	AudioOutputNode* node;

	// reference to the virtual piano
	InputDevice::Piano* vPiano;

	// the audio stream to play data from
	PaStream* stream;

	// are we ready to play audio?
	bool initialized;

	// tuned for C5 to be 440 Hz (see audio defines)
	inline float getFrequencyForNote(int note) { return AUDIO_TUNE_FREQUENCY * fpowf(1.0594631f, (note - AUDIO_TUNE_NOTE)); };

	// positions and speeds of playback
	float positions[InputDevice::Piano::TOTAL_KEYS];
	float speeds[InputDevice::Piano::TOTAL_KEYS];

	// holds both left and right audio
	float summedSignal[AUDIO_FRAME_SIZE * 2];

public:
	
	// create us with a link to the endpoint and a virtual piano
	AudioPlayback(AudioOutputNode* outputNode, InputDevice::Piano* virtualPiano);

	// initialize the audio playback mechanism
	bool initialize();

	// deinitialize the audio playback mechanism
	bool deinitialize();

	// check wether we have been initialized or not
	inline bool isInitialized() { return initialized; };

	// callback so we can feed the driver more audio data
	static int AudioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userdata);
	
	// update the positions relative to the speeds
	void updatePositions();

	// calculate the fed signal for multiple keys pressed at once
	void calculateSummedSignal();
};