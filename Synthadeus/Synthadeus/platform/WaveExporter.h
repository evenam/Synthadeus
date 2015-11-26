////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Wave File Exporting Module                                               //
//   Everett Moser                                                            //
//   11-25-15                                                                 //
//                                                                            //
//   Handles the process of creating and exporting a Waveform File            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#pragma once

//#include "Error.h"

#include <cassert>
#include <Windows.h>
#include <stdio.h>

#define SHIFT0(a) ((a) >> 24)
#define SHIFT1(a) ((a) >> 16)
#define SHIFT2(a) ((a) >> 8)
#define SHIFT3(a) (a)


class WaveExporter
{
private:
	// some useful masks to help load in some little endian numbers
	const static unsigned int   MASK32_3 = 0x000000FF;
	const static unsigned int   MASK32_2 = 0x0000FF00;
	const static unsigned int   MASK32_1 = 0x00FF0000;
	const static unsigned int   MASK32_0 = 0xFF000000;

	const static unsigned short MASK16_1 = 0x00FF;
	const static unsigned short MASK16_0 = 0xFF00;

	// size of the header
	//   RIFF(4) + RIFF_SIZE(4) + WAVE(4) + FMT(4) + FMT_SIZE(4) + FMT_CODE(2) + CHANNELS(2)
	// + RATE(4) + AVG(4) + ALIGN(2) + BITS(2) + DATA(4) + SIZE(4)
	const static short waveSize = 44;

	// info offsets [sizeof (Previous) + offet(previous)]
	const static int RIFF_OFFSET		= 0;
	const static int RIFF_SIZE_OFFSET	= 4 + RIFF_OFFSET;
	const static int WAVE_TYPE_OFFSET	= 4 + RIFF_SIZE_OFFSET;
	const static int FORMAT_OFFSET		= 4 + WAVE_TYPE_OFFSET;
	const static int FORMAT_SIZE_OFFSET = 4 + FORMAT_OFFSET;
	const static int FORMAT_CODE_OFFSET = 4 + FORMAT_SIZE_OFFSET;
	const static int CHANNELS_OFFSET	= 2 + FORMAT_CODE_OFFSET;
	const static int SAMPLE_RATE_OFFSET = 2 + CHANNELS_OFFSET;
	const static int AVERAGE_BBP_OFFSET = 4 + SAMPLE_RATE_OFFSET;
	const static int ALIGNMENT_OFFSET	= 4 + AVERAGE_BBP_OFFSET;
	const static int BIT_DEPTH_OFFSET	= 2 + ALIGNMENT_OFFSET;
	const static int WAVE_ID_OFFSET		= 2 + BIT_DEPTH_OFFSET;
	const static int WAVE_SIZE_OFFSET	= 4 + WAVE_ID_OFFSET;
	static_assert(WAVE_SIZE_OFFSET + 4 == waveSize, "Error, wave size incorrect. ");

	// wav header information
	const static char RIFF[4];
	const static char WAVE[4];
	const static char  FMT[4];

	// hold the non-constant information
	const static char DATA[4];
	short fmtCode;
	short channels;
	int sampleRate;
	int avgBps;
	short align;
	short bits;
	char rawHeaderData[waveSize];

	// sample conversion
	bool prepared;
	int nSamples;
	void* rawAudioData;

	// calculations
	inline int calcByteTotal() { return sizeof(short) * channels * nSamples; }
	inline int calcRiffSize() { return calcByteTotal() - 8 + waveSize; }
	inline int calcAlign() { return (channels * bits) / 8; }
	inline int calcAvgBps() { return sampleRate * align; }

	// misc
	bool successful;
	float* channel1, *channel2;
public:
	WaveExporter(int numAudioSamples, float* audioSamplesL, float* audioSamplesR);
	WaveExporter(int numAudioSamples, float* audioSamples);
	inline bool wasSuccessful() { return successful; }
	inline bool isPrepared() { return prepared; }

	void prepareExport();
	void saveWaveFile();
	void unprepareExport();
};

