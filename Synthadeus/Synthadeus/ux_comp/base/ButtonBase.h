////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Button Base                                                              //
//   Everett Moser                                                            //
//   11-14-15                                                                 //
//                                                                            //
//   Simple logic for a button based on held state or serial events           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

class ButtonBase
{
public:
	// state check
	inline bool check() { return isHeld && !isDebounced; };

	// pressed this update cycle?
	inline bool checkPressed() { return isPressed && !isDebounced; };

	// released this update cycle?
	inline bool checkReleased() { return isReleased && !isDebounced; };

	// reset the button state, it must be pressed again to trigger bounced state
	inline void debounce() { isDebounced = true; };

	// construct button in debounced state
	ButtonBase();

	// update the state variables with the pressed status
	void update(bool isCurrentlyPressed);

	// update the state variables with the event variables
	void update();

	// trigger a pressed event (untested)
	inline void press() { toggle = true; };

	// trigger a released event (untested)
	inline void release() { toggle = false; };

private:
	// state variables
	bool isPressed, isHeld, isReleased, isDebounced;

	// serial event state variable (untested)
	bool toggle;
};
