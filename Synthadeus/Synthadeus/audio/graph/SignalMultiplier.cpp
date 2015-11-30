#include "SignalMultiplier.h"

void SignalMultiplier::calculateBuffer()
{
	// buffer size is the same as the input
	bufferSize = POTENTIAL_NULL(input, getBufferSize(), 0);

	// if there is input, multiply the sample into this node's buffer
	for (int i = 0; i < bufferSize; i++)
	{
		assert(bufferSize > 0);
		bufferL[i] = input->getBufferValueL(i) * value;
		bufferR[i] = input->getBufferValueR(i) * value;
	}
}

SignalMultiplier::SignalMultiplier(float signalValue, AudioNode * inputNode)
{
	// update the initial value and input
	value = signalValue;
	input = inputNode;

	// initial buffer calculation
	calculateBuffer();
}

void SignalMultiplier::setInput(AudioNode * inputNode)
{
	// set a new input node
	input = inputNode;
}

void SignalMultiplier::setValue(float signalValue)
{
	// set a new multiplication coefficient
	value = signalValue;
}

void SignalMultiplier::recalculate()
{
	// recalculate the buffer with the member function
	calculateBuffer();
}
