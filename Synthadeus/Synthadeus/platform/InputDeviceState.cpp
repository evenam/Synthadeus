#include "InputDeviceState.h"

Button::Button()
	: isPressed(false), isHeld(false), isReleased(true), isDebounced(true)
{}

void Button::update(bool isCurrentlyPressed)
{
	if (isCurrentlyPressed)
	{
		if (isPressed)
		{
			isPressed = false;
			isHeld = true;
			isReleased = false;
		}
		else
		{
			isPressed = true;
			isHeld = true;
			isReleased = false;
		}
	}
	else
	{
		if (isReleased)
		{
			isPressed = false;
			isHeld = false;
			isReleased = false;
		}
		else
		{
			isPressed = true;
			isHeld = false;
			isReleased = true;
		}
	}

	if (!isCurrentlyPressed && isDebounced)
		isDebounced = false;
}

InputDeviceState::InputDeviceState()
{

}


void InputDeviceState::update()
{
	CURSORINFO cursorInfo;
	GetCursorInfo(&cursorInfo);
	mousePosition.x = cursorInfo.ptScreenPos.x;
	mousePosition.y = cursorInfo.ptScreenPos.y;
	leftMouse.update((GetAsyncKeyState(VK_LBUTTON) ? true : false));
	leftMouse.update((GetAsyncKeyState(VK_RBUTTON) ? true : false));
}
