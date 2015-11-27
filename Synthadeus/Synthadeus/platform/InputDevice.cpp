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
	vController.waveExport.debounce();

	// reset the piano 
	vPiano.numKeysPressed = 0;
	for (int i = 0; i < Piano::OCTAVES; i++)
	{
		for (int j = 0; j < Piano::KEYS; j++)
		{
			vPiano.keys[i][j].debounce();
		}
	}
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
	vController.quit.update((GetAsyncKeyState(VK_ESCAPE) ? true : false));

	// waveExport is the F5 key
	vController.waveExport.update((GetAsyncKeyState(VK_F5) ? true : false));

	// the virtual piano keyboard keys octave 5/6... Q-->] is white keys, 1-->= is black keys (trust me)
	vPiano.keys[5][Piano::C].update((GetAsyncKeyState('Q') ? true : false));
	vPiano.keys[5][Piano::CS].update((GetAsyncKeyState('2') ? true : false));
	vPiano.keys[5][Piano::D].update((GetAsyncKeyState('W') ? true : false));
	vPiano.keys[5][Piano::DS].update((GetAsyncKeyState('3') ? true : false));
	vPiano.keys[5][Piano::E].update((GetAsyncKeyState('E') ? true : false));
	vPiano.keys[5][Piano::F].update((GetAsyncKeyState('R') ? true : false));
	vPiano.keys[5][Piano::FS].update((GetAsyncKeyState('4') ? true : false));
	vPiano.keys[5][Piano::G].update((GetAsyncKeyState('T') ? true : false));
	vPiano.keys[5][Piano::GS].update((GetAsyncKeyState('5') ? true : false));
	vPiano.keys[5][Piano::A].update((GetAsyncKeyState('Y') ? true : false));
	vPiano.keys[5][Piano::AS].update((GetAsyncKeyState('6') ? true : false));
	vPiano.keys[5][Piano::B].update((GetAsyncKeyState('U') ? true : false));
	vPiano.keys[6][Piano::C].update((GetAsyncKeyState('I') ? true : false));
	vPiano.keys[6][Piano::CS].update((GetAsyncKeyState('9') ? true : false));
	vPiano.keys[6][Piano::D].update((GetAsyncKeyState('O') ? true : false));
	vPiano.keys[6][Piano::DS].update((GetAsyncKeyState('0') ? true : false));
	vPiano.keys[6][Piano::E].update((GetAsyncKeyState('P') ? true : false));
	vPiano.keys[6][Piano::F].update((GetAsyncKeyState(VK_OEM_4) ? true : false));
	vPiano.keys[6][Piano::FS].update((GetAsyncKeyState(VK_OEM_PLUS) ? true : false));
	vPiano.keys[6][Piano::G].update((GetAsyncKeyState(VK_OEM_6) ? true : false));

	// the virtual piano keyboard keys octave 4... Q-->] is white keys, 1-->= is black keys (trust me)
	vPiano.keys[4][Piano::C].update((GetAsyncKeyState('Z') ? true : false));
	vPiano.keys[4][Piano::CS].update((GetAsyncKeyState('S') ? true : false));
	vPiano.keys[4][Piano::D].update((GetAsyncKeyState('X') ? true : false));
	vPiano.keys[4][Piano::DS].update((GetAsyncKeyState('D') ? true : false));
	vPiano.keys[4][Piano::E].update((GetAsyncKeyState('C') ? true : false));
	vPiano.keys[4][Piano::F].update((GetAsyncKeyState('V') ? true : false));
	vPiano.keys[4][Piano::FS].update((GetAsyncKeyState('G') ? true : false));
	vPiano.keys[4][Piano::G].update((GetAsyncKeyState('B') ? true : false));
	vPiano.keys[4][Piano::GS].update((GetAsyncKeyState('H') ? true : false));
	vPiano.keys[4][Piano::A].update((GetAsyncKeyState('N') ? true : false));
	vPiano.keys[4][Piano::AS].update((GetAsyncKeyState('J') ? true : false));
	vPiano.keys[4][Piano::B].update((GetAsyncKeyState('M') ? true : false));

	// determine keypresses for the piano (makes DPS easier later)
	vPiano.numKeysPressed = 0;
	for (int i = 0; i < Piano::OCTAVES; i++)
	{
		for (int j = 0; j < Piano::KEYS; j++)
		{
			vPiano.numKeysPressed += (vPiano.keys[i][j].check() ? 1 : 0);
		}
	}
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
