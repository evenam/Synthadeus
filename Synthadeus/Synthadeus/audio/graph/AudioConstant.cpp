#include "AudioConstant.h"

AudioConstant::AudioConstant(float val) : value(val)
{
	// only one value, only one buffer position
	bufferL[0] = bufferR[0] = value;
	bufferSize = 1;
	setMaxPosition(1);
}

void AudioConstant::setValue(float val)
{
	// update the value
	value = val;
}

void AudioConstant::recalculate()
{
	// same as constructor: one value, one position
	bufferL[0] = bufferR[0] = value;
	bufferSize = 1;
	setMaxPosition(1);
}
