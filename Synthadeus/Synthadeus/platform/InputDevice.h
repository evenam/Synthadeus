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

class InputDevice : public Object
{
public:
	RTTI_MACRO(InputDevice);

	// mouse data members

	class Mouse
	{
	public:
		ButtonBase left, right;
		inline Point instancePosition() { return position - currentInstance; }
		Point position;

		void instance(Point p);
		void restore();
		inline Mouse() : currentInstance(0.f, 0.f) { instanceSize = 0; }
	private:
		enum { NUM_INSTANCES = 16 };
		Point instances[NUM_INSTANCES];
		int instanceSize;
		Point currentInstance;
	} vMouse;

	struct Piano
	{
	} vPiano;

	struct Controller
	{
		// arrow keys
		ButtonBase up, down, left, right;

		// enter key
		ButtonBase center;

		// escape key
		ButtonBase quit;
	} vController;

	// set up the initial device
	InputDevice();

	// update the device
	void update();
};

