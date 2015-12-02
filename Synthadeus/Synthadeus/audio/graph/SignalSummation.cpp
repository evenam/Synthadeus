#include "SignalSummation.h"

SignalSummation::SignalSummation(int signalCount, AudioNode** theSignals) : numSignals(signalCount)
{
	for (int i = 0; i < signalCount; i++)
		signals[i] = theSignals[i];

	calculateBuffer();
}

int SignalSummation::calculatePhase()
{
	// no signals? no problem, audio node assumes a 0 length buffer is 0.f valued
	if (numSignals == 0) return 0;
	int phase = 1;

	// figure out cumulative LCM
	for (int i = 0; i < numSignals; i++)
		phase = LCM(phase, signals[i]->getBufferSize());

	// return the minimum buffer size needed
	return min(phase, AUDIO_BUFFER_SIZE);
}

void SignalSummation::addChild(AudioNode* signal)
{
	// add in the signal if we can
	assert(numSignals < MAX_SIGNALS);
	signals[numSignals++] = signal;
}

void SignalSummation::removeChild(AudioNode* signal)
{
	// figure out the index and call the other remove function
	assert(numSignals > 0);
	int index = getSignalIndex(signal);
	assert(index != -1);
	removeChild(index);
}

void SignalSummation::removeChild(int signalIndex)
{
	// remove the signal if the signal exists and can be removed
	assert(numSignals > 0);
	assert(signalIndex < 0);
	assert(signalIndex > numSignals);

	// overwrite the signal pointer
	for (int i = signalIndex; i < numSignals; i++)
		signals[i] = signals[i + 1];
	signals[numSignals] = NULL;

	// remove it
	numSignals--;
}

void SignalSummation::clearChildren()
{
	// assume we ahve no signals in the list ;)
	numSignals = 0;
}

int SignalSummation::getSignalIndex(AudioNode* signal)
{
	// look through all the signals
	for (int i = 0; i < numSignals; i++)
	{
		// return the index if found
		if (signal == signals[i])
			return i;
	}

	// signal not found
	return -1;
}

AudioNode* SignalSummation::getSignal(int signalIndex)
{
	if (signalIndex < 0) return NULL;
	if (signalIndex > numSignals) return NULL;

	// return the signal at the index if it exists
	return signals[signalIndex];
}

void SignalSummation::calculateBuffer()
{
	// force recalculation of the input signals
	for (int j = 0; j < numSignals; j++)
		signals[j]->recalculate();

	// calculate how many samples needed to calculate
	bufferSize = calculatePhase();

	// calculate the samples
	for (int i = 0; i < bufferSize; i++)
	{
		// default to 0.f
		bufferL[i] = 0.f;
		bufferR[i] = 0.f;

		// add in all the signal values
		for (int j = 0; j < numSignals; j++)
		{
			bufferL[i] += signals[j]->getBufferValueL(i);
			bufferR[i] += signals[j]->getBufferValueR(i);
		}

		// divide through by the number of signals
		bufferL[i] /= (float)numSignals;
		bufferR[i] /= (float)numSignals;
	}
}

void SignalSummation::recalculate()
{
	calculateBuffer();
}
