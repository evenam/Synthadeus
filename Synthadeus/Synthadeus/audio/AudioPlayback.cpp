#include "AudioPlayback.h"
#include "AudioOutputNode.h"
#include "MidiInterface.h"

AudioPlayback::AudioPlayback(AudioOutputNode* outputNode, InputDevice::Piano* virtualPiano)
{
	vPiano = virtualPiano;
	node = outputNode;
	stream = NULL;
	initialized = false;
	for (int i = 0; i < InputDevice::Piano::TOTAL_KEYS; i++)
	{
		positions[i] = 0.f;
		speeds[i] = getFrequencyForNote(i) / AUDIO_TUNE_FREQUENCY;
	}
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
	EnterCriticalSection(&myself->vPiano->pianoCriticalSection);
	myself->updatePositions();
	myself->calculateSummedSignal();
	for (i = 0; i < framesPerBuffer; i++)
	{
		*out++ = myself->summedSignal[2 * i];
		*out++ = myself->summedSignal[2 * i + 1];
	}
	LeaveCriticalSection(&myself->vPiano->pianoCriticalSection);

	return 0;
}

void AudioPlayback::updatePositions()
{
	for (int i = 0; i < InputDevice::Piano::TOTAL_KEYS; i++)
	{
		if (vPiano->keys[MidiInterface::getOctaveValue(i)][MidiInterface::getNoteValue(i)].check())
		{
			positions[i] += speeds[i];
		}
	}
}


void AudioPlayback::calculateSummedSignal()
{
	for (int j = 0; j < AUDIO_FRAME_SIZE; j++)
	{
		summedSignal[2 * j] = 0.f;
		summedSignal[2 * j + 1] = 0.f;
		for (int i = 0; i < vPiano->getNumKeysPressed(); i++)
		{
			int currentNote = vPiano->getKey(i);
			//DebugPrintf("Position: %d\n", positions[currentNote]);
			summedSignal[2 * j] += node->getAudioNode()->lerpValueL(positions[currentNote]) / (float)vPiano->getNumKeysPressed();
			summedSignal[2 * j + 1] += node->getAudioNode()->lerpValueL(positions[currentNote]) / (float)vPiano->getNumKeysPressed();
			positions[currentNote] += speeds[currentNote];
		}
	}
}