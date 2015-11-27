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

#pragma comment(lib, "portmidi.lib")

#pragma once

class MidiInterface
{
private:
	bool initialized;
	PmStream* midiIn;
	int msgFilter;
	bool notes[InputDevice::Piano::OCTAVES][InputDevice::Piano::KEYS];

public:
	MidiInterface();

	bool initialize();
	bool deinitialize();
	inline bool isInitialized() { return initialized; };
	static void ptMidiCallback(PtTimestamp timestamp, void* data);

	bool check(int octave, int note);
	inline static int getNoteValue(int key) { return key % 12; };
	inline static int getOctaveValue(int key) { return key / 12; };
	inline static int getKeyValue(int octave, int note) { return 12 * octave + note; };
};

