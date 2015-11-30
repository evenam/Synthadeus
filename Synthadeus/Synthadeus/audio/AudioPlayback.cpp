#include "AudioPlayback.h"
#include "AudioOutputNode.h"
#include "MidiInterface.h"

AudioPlayback::AudioPlayback(AudioOutputNode* outputNode, InputDevice::Piano* virtualPiano)
	: initialized(false)
{
	// initialize piano, output node and stream
	vPiano = virtualPiano;
	node = outputNode;
	stream = NULL;

	// initialize all the positions and speeds of note playback
	for (int i = 0; i < InputDevice::Piano::TOTAL_KEYS; i++)
	{
		positions[i] = 0.f;
		speeds[i] = getFrequencyForNote(i) / AUDIO_TUNE_FREQUENCY;
	}
}

bool AudioPlayback::initialize()
{
	// initialize port audio
	Pa_Initialize();

#ifdef AUDIO_ASIO_BUILD
	// ASIO build, attempt to get an ASIO device before defaulting
	PaError err = paNoError;

	// ASIO channels to select
	int channelSelector[] = { 0, 1 };

	// fill out the stream info with the information for a potential ASIO stream
	PaAsioStreamInfo asioInfo;
	asioInfo.size = sizeof(PaAsioStreamInfo);
	asioInfo.hostApiType = paASIO;
	asioInfo.version = 1;
	asioInfo.flags = paAsioUseChannelSelectors;
	asioInfo.channelSelectors = channelSelector;

	// fill out the stream parameters
	PaStreamParameters params;
	params.channelCount = 2;
	params.device = AUDIO_DEVICE;
	params.sampleFormat = paFloat32;
	params.suggestedLatency = Pa_GetDeviceInfo(params.device)->defaultLowOutputLatency;
	params.hostApiSpecificStreamInfo = &asioInfo;

	// can we open the stream?
	err = Pa_OpenStream(&stream, NULL, &params, 44100, 64, paClipOff, AudioPlayback::AudioCallback, this);
	
	// if not, get the default one
	if (err != paNoError) {
		err = Pa_OpenDefaultStream(&stream, 0, AUDIO_CHANNELS, paFloat32, AUDIO_SAMPLE_RATE, AUDIO_FRAME_SIZE, AudioPlayback::AudioCallback, this); 
	}
#else
	// non-ASIO build, just use default device and default stream
	PaError err = paNoError;
	err = Pa_OpenDefaultStream(&stream, 0, AUDIO_CHANNELS, paFloat32, AUDIO_SAMPLE_RATE, AUDIO_FRAME_SIZE, AudioPlayback::AudioCallback, this);
#endif

	// sart the stream
	if (err == paNoError)
		err = Pa_StartStream(stream);

	// deliver errors
	if (err != paNoError)
	{
		DebugPrintf("  [AUDIO] Error: %s\n", Pa_GetErrorText(err));
		return false;
	}
	
	// success
	initialized = true;
	return true;
}

bool AudioPlayback::deinitialize()
{
	// regard as not initialized
	initialized = false;
	
	// stop and close the audio stream
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	
	// terminate port audio 
	Pa_Terminate();

	// success!
	return true;
}

int AudioPlayback::AudioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userdata)
{
	// assert the fill amount is equivalent to the calculated data
	assert(framesPerBuffer == AUDIO_FRAME_SIZE);

	// reference the output buffer and the input
	float *out = (float*)outputBuffer;
	
	// resolve the identity crisis
	AudioPlayback* myself = (AudioPlayback*)userdata;

	// we are using the piano within a thread, so make us threadsafe
	EnterCriticalSection(&myself->vPiano->pianoCriticalSection);

	// calculate the new output signals
	myself->updatePositions();
	myself->calculateSummedSignal();

	// fill the output buffers
	for (unsigned int i = 0; i < framesPerBuffer; i++)
	{
		*out++ = myself->summedSignal[2 * i];
		*out++ = myself->summedSignal[2 * i + 1];
	}

	// we are done with the piano
	LeaveCriticalSection(&myself->vPiano->pianoCriticalSection);

	// exit success!
	return 0;
}

void AudioPlayback::updatePositions()
{
	// iterate through keys
	for (int i = 0; i < InputDevice::Piano::TOTAL_KEYS; i++)
	{
		// check the piano's keystate
		if (vPiano->keys[MidiInterface::getOctaveValue(i)][MidiInterface::getNoteValue(i)].check())
		{
			// advance the positions
			positions[i] += speeds[i];
		}
		else
		{
			// reset the positions
			positions[i] = 0.f;
		}
	}
}


void AudioPlayback::calculateSummedSignal()
{
	// calculate each sample
	for (int j = 0; j < AUDIO_FRAME_SIZE; j++)
	{
		// initialize to 0.f
		summedSignal[2 * j] = 0.f;
		summedSignal[2 * j + 1] = 0.f;

		// determine all of the keys pressed
		for (int i = 0; i < vPiano->getNumKeysPressed(); i++)
		{
			// signal summation algorithm
			int currentNote = vPiano->getKey(i);
			summedSignal[2 * j] += node->getAudioNode()->lerpValueR(positions[currentNote]) / (float)vPiano->getNumKeysPressed();
			summedSignal[2 * j + 1] += node->getAudioNode()->lerpValueL(positions[currentNote]) / (float)vPiano->getNumKeysPressed();
			
			// advance the positions
			positions[currentNote] += speeds[currentNote];
		}
	}
}