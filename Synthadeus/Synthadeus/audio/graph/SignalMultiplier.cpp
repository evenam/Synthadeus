#include "SignalMultiplier.h"

void SignalMultiplier::calculateBuffer()
{
	bufferSize = POTENTIAL_NULL(input, getBufferSize(), 0);
	for (int i = 0; i < bufferSize; i++)
	{
		assert(bufferSize > 0);
		bufferL[i] = input->getBufferValueL(i) * value;
		bufferR[i] = input->getBufferValueR(i) * value;
	}
}

SignalMultiplier::SignalMultiplier(float signalValue, AudioNode * inputNode)
{
	value = signalValue;
	input = inputNode;
	calculateBuffer();
}

void SignalMultiplier::setInput(AudioNode * inputNode)
{
	input = inputNode;
}

void SignalMultiplier::setValue(float signalValue)
{
	value = signalValue;
}

void SignalMultiplier::recalculate()
{
	calculateBuffer();
}
