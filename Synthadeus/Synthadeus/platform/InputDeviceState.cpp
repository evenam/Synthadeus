#include "InputDeviceState.h"

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
