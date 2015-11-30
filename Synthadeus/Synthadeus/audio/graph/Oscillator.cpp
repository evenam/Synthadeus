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
	// calculate the potential modifiers from the modulators
	int freqMod = POTENTIAL_NULL(frequencyMod, getBufferSize(), 1.f);
	int volMod = POTENTIAL_NULL(volumeMod, getBufferSize(), 1.f);
	int panMod = POTENTIAL_NULL(panningMod, getBufferSize(), 1.f);
	int sampleMod = AUDIO_SAMPLE_RATE / frequency;

	// the LCM is a major optimization in terms of space requirements
	// it reduces the space by a factor of 10-10000x depending on the input nodes
	// also reduces subsequend calculations
	int phase = LCM(LCM(freqMod, volMod), LCM(panMod, sampleMod));

	// kids, keep on your harmonics and avoid relatively prime numbers
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
	// volume is the current volume adjusted by the volume modulator by that percent
	return POTENTIAL_NULL(volumeMod, getBufferValueL(sample) * 0.5 + 0.5 * volume, volume);
}

float Oscillator::calcVolumeR(int sample)
{
	// volume is the current volume adjusted by the volume modulator by that percent
	return POTENTIAL_NULL(volumeMod, getBufferValueR(sample) * 0.5 + 0.5 * volume, volume);
}

float Oscillator::calcFrequencyL(int sample)
{
	// frequency is calculated based upon the base and modulation can make it 0x to 2x the amount
	return frequency + frequency * POTENTIAL_NULL(frequencyMod, getBufferValueL(sample), 0.f);
}

float Oscillator::calcFrequencyR(int sample)
{
	// frequency is calculated based upon the base and modulation can make it 0x to 2x the amount
	return frequency + frequency * POTENTIAL_NULL(frequencyMod, getBufferValueR(sample), 0.f);
}

void Oscillator::calcBuffer()
{
	// recalc the potential inputs
	POTENTIAL_NULL(frequencyMod, recalculate(), 0);
	POTENTIAL_NULL(volumeMod, recalculate(), 0);
	POTENTIAL_NULL(panningMod, recalculate(), 0);

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

		// update theta (keep it in rotation)
		thetaL += 2 * PI * calcFrequencyL(i) / AUDIO_SAMPLE_RATE;
		thetaR += 2 * PI * calcFrequencyR(i) / AUDIO_SAMPLE_RATE;

		// cap it with some accuracy (more than the CFMATH method)
		while (thetaL > 2 * PI) thetaL -= 2 * PI;
		while (thetaR > 2 * PI) thetaR -= 2 * PI;
	}
}

void Oscillator::setFrequencyModulator(AudioNode* freqMod)
{
	// set new frequency modulator
	frequencyMod = freqMod;
}

void Oscillator::setVolumeModulator(AudioNode* volMod)
{
	// set new volume modulator
	volumeMod = volMod;
}

void Oscillator::setPanningModulator(AudioNode* panMod)
{
	// set new panning modulator
	panningMod = panMod;
}

void Oscillator::setVolume(float vol)
{
	// update the base volume
	volume = vol;
}

void Oscillator::setFrequency(float freq)
{
	// update the base frequency
	frequency = freq;
}

void Oscillator::setPanning(float pan)
{
	// update the base panning
	panning = pan;
}

void Oscillator::setWaveform(WAVEFORM wave)
{
	// set waveform to new waveform
	waveform = wave;
}

float Oscillator::getFrequency()
{
	// current frequency
	return frequency;
}

float Oscillator::getPanning()
{
	// current panning
	return panning;
}

float Oscillator::getVolume()
{
	// current volume
	return volume;
}

Oscillator::WAVEFORM Oscillator::getWaveform()
{
	// current waveform
	return waveform;
}

AudioNode* Oscillator::getFrequencyModulator()
{
	// current frequency modulator
	return frequencyMod;
}

AudioNode* Oscillator::getVolumeModulator()
{
	// current volume modulator
	return volumeMod;
}

AudioNode* Oscillator::getPanningModulator()
{
	// current panning modulator
	return panningMod;
}
