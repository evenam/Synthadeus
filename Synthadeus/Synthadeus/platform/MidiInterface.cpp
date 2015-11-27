#include "MidiInterface.h"
#include "Error.h"

MidiInterface::MidiInterface(InputDevice::Piano * virtualPiano)
{
	vPiano = virtualPiano;
	initialized = false;
	midiIn = NULL;
	msgFilter = 0;
}

bool MidiInterface::initialize()
{
	initialized = false;
	PmError pmErr = pmNoError;
	PtError ptErr = ptNoError;

	pmErr = Pm_Initialize();
	if (pmErr != pmNoError)
		return false;

	ptErr = Pt_Start(1, MidiInterface::ptMidiCallback, this);
	if (ptErr != -ptNoError)
		return false;

	int defaultDevice = 0;
	int numDevices = 0;
	for (int i = 0; i < Pm_CountDevices(); i++) {
		const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
		if (info->input)
		{
			// found a midi device
			DebugPrintf("%d: %s, %s\n", i, info->interf, info->name);
			if (numDevices == 0)
				defaultDevice = i;
			numDevices++;
		}
	}

	// initialized no devices successfully, so initialized is false but we return success
	if (numDevices <= 0)
		return true;

	pmErr = Pm_OpenInput(&midiIn, defaultDevice, NULL, 512, NULL, NULL);
	if (pmErr)
		return false;

	pmErr = Pm_SetFilter(midiIn, msgFilter);
	if (pmErr)
		return false;

	initialized = true;
	return true;
}

bool MidiInterface::deinitialize()
{
	initialized = true;
	if (midiIn)
		Pm_Close(midiIn);
	Pt_Stop();
	Pm_Terminate();

	initialized = false;
	return true;
}

void MidiInterface::ptMidiCallback(PtTimestamp timestamp, void* userdata)
{
	if (!((MidiInterface*)userdata)->isInitialized()) return;
	PmEvent event;
	ZeroMemory(&event, sizeof(PmEvent));
	int count;
	PmStream* midiInStream = (((MidiInterface*)userdata)->midiIn);
	count = Pm_Read(midiInStream, &event, 1);
	if (count < 0)
	{
		PmError err = (PmError)count;
		DebugPrintf("[MIDI] ERROR: %s\n", Pm_GetErrorText(err));
		assert(!"MIDI error.");
	}
	else if (count > 0)
	{
		DebugPrintf("Received midi message\n");
	}
}
