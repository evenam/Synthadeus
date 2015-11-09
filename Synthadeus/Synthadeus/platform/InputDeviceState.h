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

class Button
{
public:
	inline bool check() { return isHeld && !isDebounced; };
	inline bool checkPressed() { return isPressed && !isDebounced; };
	inline bool checkReleased() { return isReleased && !isDebounced; };
	void update(bool isCurrentlyPressed);

	inline void debounce() { isDebounced = true; };
	Button();

private:
	bool isPressed, isHeld, isReleased, isDebounced;
};


class InputDeviceState : public Object
{
protected:
	Button leftMouse, rightMouse;

	Point mousePosition;

public:
	InputDeviceState();
	void update();
};

