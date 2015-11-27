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
	InputDevice::Piano* vPiano;
	PmStream* midiIn;
	int msgFilter;

public:
	MidiInterface(InputDevice::Piano* virtualPiano);

	bool initialize();
	bool deinitialize();
	inline bool isInitialized() { return initialized; };
	static void ptMidiCallback(PtTimestamp timestamp, void* data);
};

