#include "MidiInterface.h"
#include "Error.h"

// flag masks to determine 
#define MIDI_OFF_NOTE   0x80
#define MIDI_ON_NOTE    0x90

MidiInterface::MidiInterface()
{
	// initialize all variables to the pre-initialization state
	initialized = false;
	midiIn = NULL;
	msgFilter = 0;

	// toggle all notes off
	for (int i = 0; i < InputDevice::Piano::OCTAVES; i++)
	{
		for (int j = 0; j < InputDevice::Piano::KEYS; j++)
		{
			notes[i][j] = false;
		}
	}
}

bool MidiInterface::initialize()
{
	// assume not initialized until this function returns successfully
	initialized = false;

	// potential audio error returns
	PmError pmErr = pmNoError;
	PtError ptErr = ptNoError;

	// initialize portmidi
	pmErr = Pm_Initialize();
	if (pmErr != pmNoError)
		return false;

	// start a 1ms callback for querying midi events
	ptErr = Pt_Start(1, MidiInterface::ptMidiCallback, this);
	if (ptErr != -ptNoError)
		return false;

	// get the number of midi devices and use the first input device found
	int defaultDevice = 0;
	int numDevices = 0;
	for (int i = 0; i < Pm_CountDevices(); i++) 
	{
		// get the device info
		const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
		
		// is this an input device?
		if (info->input)
		{
			// found a midi device
			DebugPrintf("%d: %s, %s\n", i, info->interf, info->name);

			// set the first input device found to be the one Synthadeus uses
			if (numDevices == 0)
				defaultDevice = i;
			numDevices++;
		}
	}

	// initialized no devices successfully, so initialized is false but we return success
	if (numDevices <= 0)
		return true;

	// open the midi input stream
	pmErr = Pm_OpenInput(&midiIn, defaultDevice, NULL, 512, NULL, NULL);
	if (pmErr)
		return false;

	// apply midi message filter
	pmErr = Pm_SetFilter(midiIn, msgFilter);
	if (pmErr)
		return false;

	// success!
	initialized = true;
	return true;
}

bool MidiInterface::deinitialize()
{
	// just assume not initialized
	initialized = false;

	// close the midi device if we opened one
	if (midiIn)
		Pm_Close(midiIn);

	// stop the callback and terminate the porttime module
	Pt_Stop();
	
	// exit portmidi
	Pm_Terminate();

	// success!
	return true;
}

void MidiInterface::ptMidiCallback(PtTimestamp timestamp, void* data)
{
	// if not fully initialized, then nothing to do
	if (!((MidiInterface*)data)->isInitialized()) return;

	// create a new midi event
	PmEvent event;
	ZeroMemory(&event, sizeof(PmEvent));

	// get the stream from the data
	PmStream* midiInStream = (((MidiInterface*)data)->midiIn);

	// read in 'count' messages
	int count;
	count = Pm_Read(midiInStream, &event, 1);

	// a negative count means there was an error
	if (count < 0)
	{
		// log the error
		PmError err = (PmError)count;
		DebugPrintf("  [MIDI] ERROR: %s\n", Pm_GetErrorText(err));
		assert(!"  [MIDI] An error has occurred. See the logs.");
	}
	else if (count > 0)
	{
		// get the message
		PmMessage msg = event.message;

		// translate the message into a command and a note value
		int command = Pm_MessageStatus(msg), note = Pm_MessageData1(msg);

		// a key on the midi controller was pressed
		if (command == MIDI_ON_NOTE)
		{
			// toggle the key state boolean to true
			DebugPrintf("  [MIDI] toggle on %d \n", note);
			((MidiInterface*)data)->notes[getOctaveValue(note)][getNoteValue(note)] = true;
		}

		//a key on the midi controller was released
		else if (command == MIDI_OFF_NOTE)
		{
			// toggle the key state boolean to false
			DebugPrintf("  [MIDI] toggle off %d \n", note);
			((MidiInterface*)data)->notes[getOctaveValue(note)][getNoteValue(note)] = false;
		}
	}
}

bool MidiInterface::check(int octave, int note)
{
	// check the key state if it's a valid key
	assert(note >= 0 && note <= InputDevice::Piano::KEYS);
	assert(octave >= 0 && octave <= InputDevice::Piano::OCTAVES);
	return notes[octave][note];
}
