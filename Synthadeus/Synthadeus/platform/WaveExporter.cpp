#include "WaveExporter.h"

const char WaveExporter::RIFF[4] = {'R', 'I', 'F', 'F'};
const char WaveExporter::WAVE[4] = {'W', 'A', 'V', 'E'};
const char WaveExporter::FMT[4]  = {'f', 'm', 't', ' '};
const char WaveExporter::DATA[4] = {'d', 'a', 't', 'a'};
#define AUDIO_SAMPLES 44100

WaveExporter::WaveExporter(int numAudioSamples, float * audioSamplesL, float * audioSamplesR)
{
	channels = 2;
	nSamples = numAudioSamples;
	sampleRate = AUDIO_SAMPLES;
	prepared = false;
	successful = false;
	channel1 = audioSamplesL;
	channel2 = audioSamplesR;
}

WaveExporter::WaveExporter(int numAudioSamples, float * audioSamples)
{
	channels = 1;
	nSamples = numAudioSamples;
	sampleRate = AUDIO_SAMPLES;
	prepared = false;
	successful = false;
	channel1 = audioSamples;
}

void WaveExporter::prepareExport()
{
	// calculate some values for the headers
	bits = 32;
	fmtCode = 1; // WAVE_PCM
	align = calcAlign();
	avgBps = calcAvgBps();
	prepared = true;

	// create header data
	//char* rawHeaderData = new char(waveSize);

	// riff chunk
	rawHeaderData[RIFF_OFFSET + 0] = RIFF[0];
	rawHeaderData[RIFF_OFFSET + 1] = RIFF[1];
	rawHeaderData[RIFF_OFFSET + 2] = RIFF[2];
	rawHeaderData[RIFF_OFFSET + 3] = RIFF[3];

	// riff size chunk
	int riffSize = calcRiffSize();
	rawHeaderData[RIFF_SIZE_OFFSET + 3] = SHIFT0(MASK32_0 & riffSize);
	rawHeaderData[RIFF_SIZE_OFFSET + 2] = SHIFT1(MASK32_1 & riffSize);
	rawHeaderData[RIFF_SIZE_OFFSET + 1] = SHIFT2(MASK32_2 & riffSize);
	rawHeaderData[RIFF_SIZE_OFFSET + 0] = SHIFT3(MASK32_3 & riffSize);

	// wave type chunk
	rawHeaderData[WAVE_TYPE_OFFSET + 0] = WAVE[0];
	rawHeaderData[WAVE_TYPE_OFFSET + 1] = WAVE[1];
	rawHeaderData[WAVE_TYPE_OFFSET + 2] = WAVE[2];
	rawHeaderData[WAVE_TYPE_OFFSET + 3] = WAVE[3];

	// format chunk
	rawHeaderData[FORMAT_OFFSET + 0] = FMT[0];
	rawHeaderData[FORMAT_OFFSET + 1] = FMT[1];
	rawHeaderData[FORMAT_OFFSET + 2] = FMT[2];
	rawHeaderData[FORMAT_OFFSET + 3] = FMT[3];

	// format size chunk (16 for PCM)
	int fmtSize = 16;
	rawHeaderData[FORMAT_SIZE_OFFSET + 3] = SHIFT0(fmtSize & MASK32_0);
	rawHeaderData[FORMAT_SIZE_OFFSET + 2] = SHIFT1(fmtSize & MASK32_1);
	rawHeaderData[FORMAT_SIZE_OFFSET + 1] = SHIFT2(fmtSize & MASK32_2);
	rawHeaderData[FORMAT_SIZE_OFFSET + 0] = SHIFT3(fmtSize & MASK32_3);

	// format code chunk
	short fmtCode = 1;
	rawHeaderData[FORMAT_CODE_OFFSET + 1] = SHIFT2(fmtCode & MASK16_0);
	rawHeaderData[FORMAT_CODE_OFFSET + 0] = SHIFT3(fmtCode & MASK16_1);

	// channels chunk
	rawHeaderData[CHANNELS_OFFSET + 1] = SHIFT2(channels & MASK16_0);
	rawHeaderData[CHANNELS_OFFSET + 0] = SHIFT3(channels & MASK16_1);

	// sample rate chunk
	rawHeaderData[SAMPLE_RATE_OFFSET + 3] = SHIFT0(sampleRate & MASK32_0);
	rawHeaderData[SAMPLE_RATE_OFFSET + 2] = SHIFT1(sampleRate & MASK32_1);
	rawHeaderData[SAMPLE_RATE_OFFSET + 1] = SHIFT2(sampleRate & MASK32_2);
	rawHeaderData[SAMPLE_RATE_OFFSET + 0] = SHIFT3(sampleRate & MASK32_3);

	// average bits per sample chunk
	rawHeaderData[AVERAGE_BBP_OFFSET + 3] = SHIFT0(avgBps & MASK32_0);
	rawHeaderData[AVERAGE_BBP_OFFSET + 2] = SHIFT1(avgBps & MASK32_1);
	rawHeaderData[AVERAGE_BBP_OFFSET + 1] = SHIFT2(avgBps & MASK32_2);
	rawHeaderData[AVERAGE_BBP_OFFSET + 0] = SHIFT3(avgBps & MASK32_3);

	// bit depth chunk
	rawHeaderData[BIT_DEPTH_OFFSET + 1] = SHIFT2(bits & MASK16_0);
	rawHeaderData[BIT_DEPTH_OFFSET + 0] = SHIFT3(bits & MASK16_1);

	// align chunk
	rawHeaderData[ALIGNMENT_OFFSET + 1] = SHIFT2(align & MASK16_0);
	rawHeaderData[ALIGNMENT_OFFSET + 0] = SHIFT3(align & MASK16_1);

	// data chunk
	rawHeaderData[WAVE_ID_OFFSET + 0] = DATA[0];
	rawHeaderData[WAVE_ID_OFFSET + 1] = DATA[1];
	rawHeaderData[WAVE_ID_OFFSET + 2] = DATA[2];
	rawHeaderData[WAVE_ID_OFFSET + 3] = DATA[3];

	// data size chunk
	int dataSize = calcByteTotal();
	rawHeaderData[WAVE_SIZE_OFFSET + 3] = SHIFT0(MASK32_0 & dataSize);
	rawHeaderData[WAVE_SIZE_OFFSET + 2] = SHIFT1(MASK32_1 & dataSize);
	rawHeaderData[WAVE_SIZE_OFFSET + 1] = SHIFT2(MASK32_2 & dataSize);
	rawHeaderData[WAVE_SIZE_OFFSET + 0] = SHIFT3(MASK32_3 & dataSize);

	// flesh out the audio samples data
	if (channels == 1)
	{
		rawAudioData = new short[nSamples];
		for (int i = 0; i < nSamples; i++)
		{
			((short*)rawAudioData)[i] = (short)(32768.f * channel1[i]);
		}
	}
	else
	{
		rawAudioData = new short[nSamples * 2];
		for (int i = 0; i < nSamples; i ++)
		{
			((short*)rawAudioData)[2 * i] = (short)(32768.f * channel1[i]);
			((short*)rawAudioData)[2 * i + 1] = (short)(32768.f * channel2[i]);
		}
	}

	//for (int i = 0; i < 11; i++)
		printf("%S ", rawHeaderData);

	// we good
	prepared = true;
}

void WaveExporter::saveWaveFile()
{
	assert(prepared);

	// set up the open file structure
	OPENFILENAME filename;
	char fileNameBuffer[1024];
	ZeroMemory(fileNameBuffer, 1024);
	ZeroMemory(&filename, sizeof(OPENFILENAME));

	// fill out some data to help the users save the file
	filename.lpstrFile = fileNameBuffer;
	filename.lStructSize = sizeof(OPENFILENAME);
	filename.nMaxFile = 1024;
	filename.lpstrFilter = "Waveform Audio File (.wav)\0*.wav\0All Files\0*.*\0";
	filename.nFilterIndex = 1;
	filename.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;

	// set the current directory to the home directory
	SetCurrentDirectory("%USERPROFILE%");
	successful = false;
	if (GetSaveFileName(&filename))
	{
		// export the file 
		FILE* f;
		fopen_s(&f, filename.lpstrFile, "wb");
		fwrite(rawHeaderData, 1, waveSize, f);
		fwrite(rawAudioData, 2, nSamples * channels, f);
		fclose(f);
		successful = true;
	}
}

void WaveExporter::unprepareExport()
{
	if (prepared)
	{
		delete[] rawAudioData;
		//delete[] rawHeaderData;
		prepared = false;
	}
}
