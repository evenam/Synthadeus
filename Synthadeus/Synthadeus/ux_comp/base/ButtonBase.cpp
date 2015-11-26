#include "ButtonBase.h"

ButtonBase::ButtonBase()
	: isPressed(false), isHeld(false), isReleased(true), isDebounced(true), toggle(false)
{}

void ButtonBase::update(bool isCurrentlyPressed)
{
	// update for currenly held state
	if (isCurrentlyPressed)
	{
		// were we not pressed last update cycle?
		if (!isHeld)
		{
			isPressed = true;
			isHeld = true;
			isReleased = false;
		}

		// if we were, this is the default held state data
		else
		{
			isPressed = false;
			isHeld = true;
			isReleased = false;
		}
	}

	// update for currently released state
	else
	{
		// if we have been released last step
		if (isHeld)
		{
			isPressed = false;
			isHeld = false;
			isReleased = true;
		}

		// if we weren't, this is the default non-held state data
		else
		{
			isPressed = false;
			isHeld = false;
			isReleased = false;
		}
	}

	// reset debouncing if the button has been released
	if (!isCurrentlyPressed && !isReleased && isDebounced)
		isDebounced = false;
}

// special case where we want the button state, but we can only send press and release events
void ButtonBase::update()
{
	update(toggle);
}
