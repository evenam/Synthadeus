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

	// mouse class
	class Mouse
	{
	public:
		
		// mouse buttons
		ButtonBase left, right;

		// mouse wheel delta
		int scrollDelta;

		// the mouse position in relative coordinates
		inline Point instancePosition() { return position - currentInstance; }

		// absolute mouse position
		Point position;

		// move the relative origin
		void instance(Point p);

		// restore the relative origin
		void restore();

		// initialize the mouse with an empty instance stack
		inline Mouse() : currentInstance(0.f, 0.f) { instanceSize = 0; scrollDelta = 0; }

	private:

		// maximum number of instances allowed
		enum { NUM_INSTANCES = 16 };

		// the stack of all the instances aquired
		Point instances[NUM_INSTANCES];
		int instanceSize;

		// the current mouse instance location
		Point currentInstance;

	} vMouse;

	// a virtual piano which we can "play"
	struct Piano
	{
		// for thread safety when updating midi in the midi thread
		CRITICAL_SECTION pianoCriticalSection;

		// allow direct access from the input device
		friend class InputDevice;

		// the virtual piano keys
		const static int OCTAVES = 10;
		enum { C, CS, D, DS, E, F, FS, G, GS, A, AS, B, KEYS};
		ButtonBase keys[OCTAVES][KEYS];

		// total number of keys currently pressed (helps with signal summation later)
		inline int getNumKeysPressed() { return numKeysPressed; };

		// get a key that is currenly pressed
		inline int getKey(int index) { assert(index >= 0 && index <= numKeysPressed); return keyStack[index]; }

		// total number of keys on this magnificent keyboard
		const static int TOTAL_KEYS = 12 * OCTAVES + KEYS;

	private:

		// a stack of keys which are currently being pressed
		int numKeysPressed;
		int keyStack[TOTAL_KEYS];
		
	} vPiano;


	// keeps track of the non-piano keyboard commands
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

