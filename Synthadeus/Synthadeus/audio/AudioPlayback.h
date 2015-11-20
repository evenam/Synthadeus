#pragma once

#include "portaudio.h"
#include "pa_asio.h"

#include "AudioNode.h"

#pragma comment(lib, "portaudio_x86.lib")

class AudioPlayback
{
private:
public:
	AudioPlayback(int noteRangeStart, int noteRangeEnd);
	void initialize();
	void beginStream();



	void endStream();
	void deinitialize();
	~AudioPlayback();
};