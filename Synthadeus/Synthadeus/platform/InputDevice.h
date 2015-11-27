////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Input Status Class                                                       //
//   Everett Moser                                                            //
//   10-5-15                                                                  //
//                                                                            //
//   A class to hold the status of all input devices                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Error.h"
#include "Object.h"
#include "Vector2D.h"
#include "ButtonBase.h"

class MidiInterface;
class InputDevice : public Object
{
public:
	RTTI_MACRO(InputDevice);

	// mouse data members

	class Mouse
	{
	public:
		ButtonBase left, right;
		int scrollDelta;
		inline Point instancePosition() { return position - currentInstance; }
		Point position;

		void instance(Point p);
		void restore();
		inline Mouse() : currentInstance(0.f, 0.f) { instanceSize = 0; scrollDelta = 0; }
	private:
		enum { NUM_INSTANCES = 16 };
		Point instances[NUM_INSTANCES];
		int instanceSize;
		Point currentInstance;
	} vMouse;

	struct Piano
	{
		CRITICAL_SECTION pianoCriticalSection;
		friend class InputDevice;
		const static int OCTAVES = 10;
		enum { C, CS, D, DS, E, F, FS, G, GS, A, AS, B, KEYS};
		ButtonBase keys[OCTAVES][KEYS];
		inline int getNumKeysPressed() { return numKeysPressed; };
		inline int getKey(int index) { assert(index >= 0 && index <= numKeysPressed); return keyStack[index]; }
		const static int TOTAL_KEYS = 12 * OCTAVES + KEYS;
	private:
		int numKeysPressed;
		int keyStack[TOTAL_KEYS];
	} vPiano;

	struct Controller
	{
		// arrow keys
		ButtonBase up, down, left, right;

		// enter key
		ButtonBase center;

		// escape key
		ButtonBase quit;

		// export key
		ButtonBase waveExport;
	} vController;

	// set up the initial device
	InputDevice();

	// update the device
	void update(MidiInterface* midi);
};

