#include "InputDeviceState.h"

Button::Button()
	: isPressed(false), isHeld(false), isReleased(true), isDebounced(true)
{}

void Button::update(bool isCurrentlyPressed)
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
	if (!isCurrentlyPressed && isDebounced)
		isDebounced = false;
}

InputDeviceState::InputDeviceState()
{
	// set the mouse position to some default
	mousePosition[0] = 0.f;
	mousePosition[1] = 0.f;

	// debounce mouse buttons
	leftMouse.debounce();
	rightMouse.debounce();

	// debounce arrow keys
	arrowUp.debounce();
	arrowDown.debounce();
	arrowLeft.debounce();
	arrowRight.debounce();

	// debounce the enter key
	enterKey.debounce();
}


void InputDeviceState::update()
{
	// get the cursor position
	CURSORINFO cursorInfo;
	GetCursorInfo(&cursorInfo);
	mousePosition.x = cursorInfo.ptScreenPos.x;
	mousePosition.y = cursorInfo.ptScreenPos.y;

	// async query mouse buttons
	leftMouse.update((GetAsyncKeyState(VK_LBUTTON) ? true : false));
	rightMouse.update((GetAsyncKeyState(VK_RBUTTON) ? true : false));

	// async query arrow keys
	arrowUp.update((GetAsyncKeyState(VK_UP) ? true : false));
	arrowDown.update((GetAsyncKeyState(VK_DOWN) ? true : false));
	arrowLeft.update((GetAsyncKeyState(VK_LEFT) ? true : false));
	arrowRight.update((GetAsyncKeyState(VK_RIGHT) ? true : false));

	// async query the enter key
	enterKey.update((GetAsyncKeyState(VK_RETURN) ? true : false));
}
