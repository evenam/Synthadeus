#include "ExponentialEnvelope.h"

int ExponentialEnvelope::calculatePhase()
{
	int phase = 1;
	phase = LCM(AUDIO_SAMPLE_RATE / length, POTENTIAL_NULL(lengthModulator, getBufferSize(), 1.f));
	return min(phase, AUDIO_SAMPLE_RATE);
}

void ExponentialEnvelope::calculateBuffer()
{
	POTENTIAL_NULL(lengthModulator, recalculate(), 0);
	POTENTIAL_NULL(exponentModulator, recalculate(), 0);
	POTENTIAL_NULL(minimumModulator, recalculate(), 0);
	POTENTIAL_NULL(maximumModulator, recalculate(), 0);

	bufferSize = calculatePhase();
	setMaxPosition(bufferSize);

	for (int i = 0; i < bufferSize; i++)
	{
		float minValL = calcMinVolL(i);
		float minValR = calcMinVolR(i);

		float totalValL = calcMaxVolL(i) - minValL;
		float totalValR = calcMaxVolR(i) - minValR;

		float expL = calcExponentL(i);
		float expR = calcExponentR(i);

		float xLenL = calcLengthL(i);
		float xLenR = calcLengthR(i);

		float valueL = fpowf((float)i / (float)bufferSize, expL);
		float valueR = fpowf((float)i / (float)bufferSize, expL);
	}
}

float ExponentialEnvelope::calcLengthL(int sample)
{
	return length + length * POTENTIAL_NULL(lengthModulator, getBufferValueL(sample), 0.f);
}

float ExponentialEnvelope::calcLengthR(int sample)
{
	return length + length * POTENTIAL_NULL(lengthModulator, getBufferValueR(sample), 0.f);
}

float ExponentialEnvelope::calcExponentL(int sample)
{
	return exponent + exponent * POTENTIAL_NULL(exponentModulator, getBufferValueR(sample), 0.f);
}

float ExponentialEnvelope::calcExponentR(int sample)
{
	return exponent + exponent * POTENTIAL_NULL(exponentModulator, getBufferValueR(sample), 0.f);
}

float ExponentialEnvelope::calcMinVolL(int sample)
{
	return (1 - POTENTIAL_NULL(minimumModulator, getBufferValueL(sample) * (1 - fabsf(minimumVolume)) + minimumVolume, minimumVolume)) * 0.5f;
}

float ExponentialEnvelope::calcMinVolR(int sample)
{
	return (1 - POTENTIAL_NULL(minimumModulator, getBufferValueR(sample) * (1 - fabsf(minimumVolume)) + minimumVolume, minimumVolume)) * 0.5f;
}

float ExponentialEnvelope::calcMaxVolL(int sample)
{
	return (1 - POTENTIAL_NULL(maximumModulator, getBufferValueL(sample) * (1 - fabsf(maximumVolume)) + maximumVolume, maximumVolume)) * 0.5f;
}

float ExponentialEnvelope::calcMaxVolR(int sample)
{
	return (1 - POTENTIAL_NULL(maximumModulator, getBufferValueR(sample) * (1 - fabsf(maximumVolume)) + maximumVolume, maximumVolume)) * 0.5f;
}

ExponentialEnvelope::ExponentialEnvelope(float len, float exp, float minVol, float maxVol, AudioNode * lenMod, AudioNode * expMod, AudioNode * minMod, AudioNode * maxMod)
	: length(len), exponent(exp), minimumVolume(minVol), maximumVolume(maxVol),
	lengthModulator(lenMod), exponentModulator(expMod), minimumModulator(minMod), maximumModulator(maxMod)
{
	calculateBuffer();
	moveToStart();
	setMaxPosition(bufferSize);
}

void ExponentialEnvelope::recalculate()
{
	calculateBuffer();
}