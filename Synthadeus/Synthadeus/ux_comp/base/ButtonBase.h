////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Button Base                                                              //
//   Everett Moser                                                            //
//   11-14-5                                                                  //
//                                                                            //
//   Simple logic for a button based on held state                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

class ButtonBase
{
public:
	// state checks
	inline bool check() { return isHeld && !isDebounced; };
	inline bool checkPressed() { return isPressed && !isDebounced; };
	inline bool checkReleased() { return isReleased && !isDebounced; };

	// reset the button state, it must be pressed again to trigger bounced state
	inline void debounce() { isDebounced = true; };

	// construct button in debounced state
	ButtonBase();

	// update the state variables with the pressed status
	void update(bool isCurrentlyPressed);

private:
	// state variables
	bool isPressed, isHeld, isReleased, isDebounced;
};
