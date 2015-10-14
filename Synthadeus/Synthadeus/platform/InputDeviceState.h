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
#include "Mutex.h"

class InputDeviceState : public Object
{
protected:
	// classception
	class Button
	{
	public:
		enum ButtonState { Released, Pressed };
		Button(ButtonState state = Released) {};
		
		bool check() { return true; };
		bool checkPressed() { return true; };
		bool checkReleased() { return true; };
		void update(ButtonState status) {};

		void debounce();
		void setState(bool pressed, bool released, bool current);

	private:
		ButtonState state;
	} buttons[256];
	Point mousePosition;

	Mutex lock;

public:
	InputDeviceState() {};
};

