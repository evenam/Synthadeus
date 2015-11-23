#include "AudioConstant.h"

AudioConstant::AudioConstant(float val) : value(val)
{
	bufferL[0] = bufferR[0] = value;
	bufferSize = 1;
}

void AudioConstant::setValue(float val)
{
	value = val;
	recalculate();
}

void AudioConstant::recalculate()
{
	bufferL[0] = bufferR[0] = value;
	bufferSize = 1;
}