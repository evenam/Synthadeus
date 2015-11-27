#include "AudioPlayback.h"
#include "AudioOutputNode.h"
#include "MidiInterface.h"

AudioPlayback::AudioPlayback(AudioOutputNode* outputNode, InputDevice::Piano* virtualPiano)
{
	vPiano = virtualPiano;
	node = outputNode;
	stream = NULL;
	initialized = false;
}

bool AudioPlayback::initialize()
{
	Pa_Initialize();
#ifdef AUDIO_ASIO_BUILD
	// ASIO build, attempt to get an ASIO device before defaulting
	
	PaError err = paNoError;
	int channelSelector[] = { 0, 1 };

	PaAsioStreamInfo asioInfo;
	asioInfo.size = sizeof(PaAsioStreamInfo);
	asioInfo.hostApiType = paASIO;
	asioInfo.version = 1;
	asioInfo.flags = paAsioUseChannelSelectors;
	asioInfo.channelSelectors = channelSelector;

	PaStreamParameters params;
	params.channelCount = 2;
	params.device = AUDIO_DEVICE;
	params.sampleFormat = paFloat32;
	params.suggestedLatency = Pa_GetDeviceInfo(params.device)->defaultLowOutputLatency;
	params.hostApiSpecificStreamInfo = &asioInfo;

	err = Pa_OpenStream(&stream, NULL, &params, 44100, 64, paClipOff, AudioPlayback::AudioCallback, this);
	/* Open an audio I/O stream. */
	if (err != paNoError) {
		err = Pa_OpenDefaultStream(&stream, 0, AUDIO_CHANNELS, paFloat32, AUDIO_SAMPLE_RATE, AUDIO_FRAME_SIZE, AudioPlayback::AudioCallback, this); 
	}
#else
	// non-ASIO build, just use default device
	PaError err = paNoError;
	err = Pa_OpenDefaultStream(&stream, 0, AUDIO_CHANNELS, paFloat32, AUDIO_SAMPLE_RATE, AUDIO_FRAME_SIZE, AudioPlayback::AudioCallback, this);
#endif
	if (err == paNoError)
		err = Pa_StartStream(stream);

	if (err != paNoError)
	{
		DebugPrintf("  [AUDIO] Error: %s\n", Pa_GetErrorText(err));
		return false;
	}
	
	initialized = true;
	return true;
}

bool AudioPlayback::deinitialize()
{
	initialized = false;
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
	return true;
}

int AudioPlayback::AudioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userdata)
{
	//if (!initialized) return;
	assert(framesPerBuffer == AUDIO_FRAME_SIZE);
	float *out = (float*)outputBuffer;
	unsigned int i;
	(void)inputBuffer; /* Prevent unused variable warning. */
	
	AudioPlayback* myself = (AudioPlayback*)userdata;
	myself->updatePositions();
	myself->calculateSummedSignal();
	for (i = 0; i < framesPerBuffer; i++)
	{
		*out++ = myself->summedSignal[2 * i];
		*out++ = myself->summedSignal[2 * i + 1];
	}

	return 0;
}

void AudioPlayback::updatePositions()
{
	for (int i = 0; i < InputDevice::Piano::TOTAL_KEYS; i++)
	{
		if (vPiano->keys[MidiInterface::getOctaveValue(i)][MidiInterface::getNoteValue(i)].check())
		{
			float speed = getFrequencyForNote(i) / 440.f;
			positions[i] += speed;
			//if (positions[i] > node->getNumSamples())
			//	positions[i] -= (float)node->getNumSamples();
		}
		else
			positions[i] = 0.f;
	}
}


void AudioPlayback::calculateSummedSignal()
{
	for (int j = 0; j < AUDIO_FRAME_SIZE; j++)
	{
		summedSignal[2 * j] = 0.f;
		summedSignal[2 * j + 1] = 0.f;
		//for (int i = 0; i < vPiano->getNumKeysPressed(); i++)
		if (vPiano->getNumKeysPressed() > 0)
		{
			summedSignal[2 * j] = node->getAudioNode()->getBufferAtPositionL();
			summedSignal[2 * j + 1] = node->getAudioNode()->getBufferAtPositionR();
		}
		else
		{
			node->getAudioNode()->moveToStart();
		}
	}
}