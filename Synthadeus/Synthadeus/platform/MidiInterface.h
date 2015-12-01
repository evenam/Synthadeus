////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Input Status Class                                                       //
//   Everett Moser                                                            //
//   10-5-15                                                                  //
//                                                                            //
//   A class to hold the status of all input devices                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "InputDevice.h"

#include "PortMidi.h"
#include "PortTime.h"

// we need portmidi
#pragma comment(lib, "portmidi.lib")

#pragma once

class MidiInterface
{
private:

	// the status of whether or not we are fully initialized
	bool initialized;

	// midi input stream from portmidi
	PmStream* midiIn;

	// default message filter should be 0
	int msgFilter;

	// current pressed status of the midi keys
	bool notes[InputDevice::Piano::OCTAVES][InputDevice::Piano::KEYS];

public:

	// simply initializes the variables
	MidiInterface();

	// starts portmidi monitoring the midi controller if there is one
	bool initialize();

	// stops portmidi from monitoring the controller and shuts portmidi down
	bool deinitialize();

	// the initialization status, false if no midi controller is connected
	inline bool isInitialized() { return initialized; };

	// callback function for when they keys are pressed
	static void ptMidiCallback(PtTimestamp timestamp, void* data);

	// returns the state of the current midi note
	bool check(int octave, int note);

	// determine the C, CS, D, ..., A, AS, B value of a note
	inline static int getNoteValue(int key) { return key % 12; };

	// determine what octave (12 half-step) range the key is in
	inline static int getOctaveValue(int key) { return key / 12; };

	// takes a note (C, CS, D, ..., A, AS, B) value and an octave range value and makes a midi note value
	inline static int getKeyValue(int octave, int note) { return 12 * octave + note; };
};

