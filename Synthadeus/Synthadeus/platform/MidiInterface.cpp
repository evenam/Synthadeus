#include "MidiInterface.h"
#include "Error.h"

#define MIDI_OFF_NOTE   0x80
#define MIDI_ON_NOTE    0x90

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
	initialized = false;
	if (midiIn)
		Pm_Close(midiIn);
	Pt_Stop();
	Pm_Terminate();
	return true;
}

void MidiInterface::ptMidiCallback(PtTimestamp timestamp, void* data)
{
	if (!((MidiInterface*)data)->isInitialized()) return;
	PmEvent event;
	ZeroMemory(&event, sizeof(PmEvent));
	int count;
	PmStream* midiInStream = (((MidiInterface*)data)->midiIn);
	count = Pm_Read(midiInStream, &event, 1);
	if (count < 0)
	{
		PmError err = (PmError)count;
		DebugPrintf("  [MIDI] ERROR: %s\n", Pm_GetErrorText(err));
		assert(!"  [MIDI] An error has occurred. See the logs.");
	}
	else if (count > 0)
	{
		PmMessage msg = event.message;
		int command = Pm_MessageStatus(msg), note = Pm_MessageData1(msg);
		if (command == MIDI_ON_NOTE)
			DebugPrintf("  [MIDI] toggle on %d \n", note);
		else if (command == MIDI_OFF_NOTE)
			DebugPrintf("  [MIDI] toggle off %d \n", note);
	}
}
