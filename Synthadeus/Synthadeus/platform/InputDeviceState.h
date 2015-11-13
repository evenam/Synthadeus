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

class Button
{
	// we cannot directly update buttons, but the InputStateDevice can, so we friend it
	friend class InputDeviceState;

public:
	// state checks
	inline bool check() { return isHeld && !isDebounced; };
	inline bool checkPressed() { return isPressed && !isDebounced; };
	inline bool checkReleased() { return isReleased && !isDebounced; };

	// reset the button state, it must be pressed again to trigger bounced state
	inline void debounce() { isDebounced = true; };

	// construct button in debounced state
	Button();

private:
	// state variables
	bool isPressed, isHeld, isReleased, isDebounced;

	// update the state variables with the pressed status
	void update(bool isCurrentlyPressed);
};


class InputDeviceState : public Object
{
public:
	RTTI_MACRO(InputDeviceState);

	// mouse data members
	Button leftMouse, rightMouse;
	Point mousePosition;
	
	// arrow keys
	Button arrowUp, arrowDown, arrowLeft, arrowRight;

	// enter key
	Button enterKey;

	// set up the initial device
	InputDeviceState();

	// update the device
	void update();
};

