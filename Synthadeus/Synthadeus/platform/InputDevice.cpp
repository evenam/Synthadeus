#include "InputDevice.h"

InputDevice::InputDevice()
{
	// set the mouse position to some default
	vMouse.position[0] = 0.f;
	vMouse.position[1] = 0.f;

	// debounce mouse buttons
	vMouse.left.debounce();
	vMouse.right.debounce();

	// debounce arrow keys
	vController.up.debounce();
	vController.down.debounce();
	vController.left.debounce();
	vController.right.debounce();

	// debounce the enter key
	vController.center.debounce();
	vController.quit.debounce();
}


void InputDevice::update()
{
	// async query mouse buttons
	vMouse.left.update((GetAsyncKeyState(VK_LBUTTON) ? true : false));
	vMouse.right.update((GetAsyncKeyState(VK_RBUTTON) ? true : false));

	// async query arrow keys
	vController.up.update((GetAsyncKeyState(VK_UP) ? true : false));
	vController.down.update((GetAsyncKeyState(VK_DOWN) ? true : false));
	vController.left.update((GetAsyncKeyState(VK_LEFT) ? true : false));
	vController.right.update((GetAsyncKeyState(VK_RIGHT) ? true : false));

	// async query the enter key
	vController.center.update((GetAsyncKeyState(VK_RETURN) ? true : false));

	// escape is the quit key
	//vController.quit.update((GetAsyncKeyState(VK_ESCAPE) ? true : false));
}

void InputDevice::Mouse::instance(Point p)
{
	assert(instanceSize < NUM_INSTANCES);
	instances[instanceSize][0] = currentInstance[0];
	instances[instanceSize][1] = currentInstance[1];
	currentInstance[0] += p[0];
	currentInstance[1] += p[1];
	instanceSize++;
}

void InputDevice::Mouse::restore()
{
	assert(instanceSize > 0);
	instanceSize--;

	currentInstance[0] = instances[instanceSize][0];
	currentInstance[1] = instances[instanceSize][1];

	if (instanceSize == 0)
		assert(currentInstance[0] == 0.f && currentInstance[1] == 0.f);
}
