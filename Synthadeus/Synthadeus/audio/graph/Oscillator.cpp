#include "Oscillator.h"

Oscillator::Oscillator(WAVEFORM wave, float freq, float vol, float pan, AudioNode* freqMod, AudioNode* volMod, AudioNode* panMod)
	: waveform(wave), frequency(freq), volume(vol), panning(pan), frequencyMod(freqMod), volumeMod(volMod), panningMod(panMod)
{
	// fill out the node buffer
	calcBuffer();

	// reset play point
	moveToStart();

	// set max play point to loop back from the start
	setMaxPosition(getBufferSize());
}

int Oscillator::calculatePhase()
{
	int freqMod = POTENTIAL_NULL(frequencyMod, getBufferSize(), 1.f);
	int volMod = POTENTIAL_NULL(volumeMod, getBufferSize(), 1.f);
	int panMod = POTENTIAL_NULL(panningMod, getBufferSize(), 1.f);
	int sampleMod = AUDIO_SAMPLE_RATE / frequency;

	// the LCM is a major optimization in terms of space requirements
	// it reduces the space by a factor of 10-10000x depending on the input nodes
	int phase = LCM(LCM(freqMod, volMod), LCM(panMod, sampleMod));
	return phase;
}

void Oscillator::recalculate()
{
	// wrapper for non-virtual function (we cannot call this from the constructor
	calcBuffer();
}

float Oscillator::calcPanL(int sample)
{
	// the panning value is centered at 'pannng' and fluctates with panning mod.
	// left panning = (1 + panning value) / 2 (i.e. a bigger value pans it to the left)
	return (1 + POTENTIAL_NULL(panningMod, getBufferValueL(sample) * (1 - fabsf(panning)) + panning, panning)) * 0.5f;
}

float Oscillator::calcPanR(int sample)
{
	// the panning value is centered at 'pannng' and fluctates with panning mod.
	// left panning = (1 - panning value) / 2 (i.e. a smaller value pans it to the right)
	return (1 - POTENTIAL_NULL(panningMod, getBufferValueR(sample) * (1 - fabsf(panning)) + panning, panning)) * 0.5f;
}

float Oscillator::calcVolumeL(int sample)
{
	return POTENTIAL_NULL(volumeMod, getBufferValueL(sample) * 0.5 + 0.5 * volume, volume);
}

float Oscillator::calcVolumeR(int sample)
{
	return POTENTIAL_NULL(volumeMod, getBufferValueR(sample) * 0.5 + 0.5 * volume, volume);
}

float Oscillator::calcFrequencyL(int sample)
{
	return frequency + frequency * POTENTIAL_NULL(frequencyMod, getBufferValueL(sample), 0.f);
}

float Oscillator::calcFrequencyR(int sample)
{
	return frequency + frequency * POTENTIAL_NULL(frequencyMod, getBufferValueR(sample), 0.f);
}

void Oscillator::calcBuffer()
{
	// flesh out the new audio buffers
	bufferSize = calculatePhase();

	// reset loop point
	setMaxPosition(bufferSize);

	// frequency is really just how fast theta changes
	float thetaL = 0.f;
	float thetaR = 0.f;

	// calculate each sample
	for (int i = 0; i < bufferSize; i++)
	{
		// A = Vol * sin( 2*PI*Freq )
		float panL = calcPanL(i);
		float panR = calcPanR(i);

		// volume with respect to panning
		float pannedVolumeL = calcVolumeL(i) * panL;
		float pannedVolumeR = calcVolumeR(i) * panR;

		// calculate the function and adjust by volume and panning
		if (waveform == SINE)
		{
			bufferL[i] = fsinf(thetaL) * pannedVolumeL;
			bufferR[i] = fsinf(thetaR) * pannedVolumeR;
		}
		else if (waveform == SAW)
		{
			bufferL[i] = sawf(thetaL) * pannedVolumeL;
			bufferR[i] = sawf(thetaR) * pannedVolumeR;
		}
		else if (waveform == SQUARE)
		{
			bufferL[i] = sqrf(thetaL) * pannedVolumeL;
			bufferR[i] = sqrf(thetaR) * pannedVolumeR;
		}

		// update theta
		thetaL += 2 * 3.14159f * calcFrequencyL(i) / AUDIO_SAMPLE_RATE;
		thetaR += 2 * 3.14159f * calcFrequencyR(i) / AUDIO_SAMPLE_RATE;

		while (thetaL > 2 * 3.14159f) thetaL -= 2 * 3.14159f;
		while (thetaR > 2 * 3.14159f) thetaR -= 2 * 3.14159f;
	}
}

// Recalculate after each modification

void Oscillator::setFrequencyModulator(AudioNode* freqMod)
{
	frequencyMod = freqMod;
	recalculate();
}

void Oscillator::setVolumeModulator(AudioNode* volMod)
{
	volumeMod = volMod;
	recalculate();
}

void Oscillator::setPanningModulator(AudioNode* panMod)
{
	panningMod = panMod;
	recalculate();
}

void Oscillator::setVolume(float vol)
{
	volume = vol;
	recalculate();
}

void Oscillator::setFrequency(float freq)
{
	frequency = freq;
	recalculate();
}

void Oscillator::setPanning(float pan)
{
	panning = pan;
	recalculate();
}

void Oscillator::setWaveform(WAVEFORM wave)
{
	waveform = wave;
	recalculate();
}

float Oscillator::getFrequency()
{
	return frequency;
}

float Oscillator::getPanning()
{
	return panning;
}

float Oscillator::getVolume()
{
	return volume;
}

Oscillator::WAVEFORM Oscillator::getWaveform()
{
	return waveform;
}

AudioNode* Oscillator::getFrequencyModulator()
{
	return frequencyMod;
}

AudioNode* Oscillator::getVolumeModulator()
{
	return volumeMod;
}

AudioNode* Oscillator::getPanningModulator()
{
	return panningMod;
}
