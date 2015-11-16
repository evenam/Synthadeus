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

class InputDeviceState : public Object
{
public:
	RTTI_MACRO(InputDeviceState);

	// mouse data members
	ButtonBase leftMouse, rightMouse;
	Point mousePosition;
	
	// arrow keys
	ButtonBase arrowUp, arrowDown, arrowLeft, arrowRight;

	// enter key
	ButtonBase enterKey;

	// set up the initial device
	InputDeviceState();

	// update the device
	void update();
};

