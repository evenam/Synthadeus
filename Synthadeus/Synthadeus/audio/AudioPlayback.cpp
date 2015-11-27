#include "AudioPlayback.h"
#include "AudioOutputNode.h"

AudioPlayback::AudioPlayback(AudioOutputNode* outputNode, InputDevice::Piano* virtualPiano)
{
	vPiano = virtualPiano;
	node = outputNode;
}

bool AudioPlayback::initialize()
{
	return true;
}

bool AudioPlayback::deinitialize()
{
	return true;
}