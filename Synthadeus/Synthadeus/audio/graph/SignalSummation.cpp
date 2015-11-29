#include "SignalSummation.h"


SignalSummation::SignalSummation(int signalCount, AudioNode** theSignals) : numSignals(signalCount)
{
	for (int i = 0; i < signalCount; i++)
		signals[i] = theSignals[i];
}

int SignalSummation::calculatePhase()
{
	if (numSignals == 0) return 0;
	int phase = 1;
	for (int i = 0; i < numSignals; i++)
		phase = LCM(phase, signals[i]->getBufferSize());
	return phase;
}

void SignalSummation::addChild(AudioNode* signal)
{
	assert(numSignals < MAX_SIGNALS);
	signals[numSignals++] = signal;
}

void SignalSummation::removeChild(AudioNode* signal)
{
	assert(numSignals > 0);
	int index = getSignalIndex(signal);
	assert(index != -1);
	removeChild(index);
}

void SignalSummation::removeChild(int signalIndex)
{
	assert(numSignals > 0);
	assert(signalIndex < 0);
	assert(signalIndex > numSignals);
	for (int i = signalIndex; i < numSignals; i++)
		signals[i] = signals[i + 1];
	numSignals--;
}

int SignalSummation::getSignalIndex(AudioNode* signal)
{
	for (int i = 0; i < numSignals; i++)
	{
		if (signal == signals[i])
			return i;
	}
	return -1;
}

AudioNode* SignalSummation::getSignal(int signalIndex)
{
	if (signalIndex < 0) return NULL;
	if (signalIndex > numSignals) return NULL;
	return signals[signalIndex];
}

void SignalSummation::recalculate()
{
	for (int j = 0; j < numSignals; j++)
		signals[j]->recalculate();

	bufferSize = calculatePhase();
	for (int i = 0; i < bufferSize; i++)
	{
		bufferL[i] = 0.f;
		bufferR[i] = 0.f;
		for (int j = 0; j < numSignals; j++)
		{
			bufferL[i] += signals[j]->getBufferValueL(i);
			bufferR[i] += signals[j]->getBufferValueR(i);
		}

		bufferL[i] /= (float)numSignals;
		bufferR[i] /= (float)numSignals;
	}
}
