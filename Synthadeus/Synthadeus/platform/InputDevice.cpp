#include "InputDevice.h"
#include "MidiInterface.h"

static_assert(InputDevice::Piano::KEYS * InputDevice::Piano::OCTAVES + InputDevice::Piano::KEYS == InputDevice::Piano::TOTAL_KEYS, "Improper key alignment.");

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
	InitializeCriticalSection(&vPiano.pianoCriticalSection);
	EnterCriticalSection(&vPiano.pianoCriticalSection);
	vPiano.numKeysPressed = 0;
	for (int i = 0; i < Piano::OCTAVES; i++)
	{
		for (int j = 0; j < Piano::KEYS; j++)
		{
			vPiano.keys[i][j].debounce();
		}
	}
	LeaveCriticalSection(&vPiano.pianoCriticalSection);
}


void InputDevice::update(MidiInterface* midi)
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

	// idiot test
	assert(midi != NULL);

	// midi update for lower half ( up to C4 )
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < Piano::KEYS; j++)
		{
			vPiano.keys[i][j].update(midi->check(i, j));
		}
	}

	// the virtual piano keyboard keys octave 5... Q-->E and ,-->/ is white keys, L-->; and 2-->3 is black keys (trust me) these ones have two keys and a midi
	vPiano.keys[5][Piano::C].update(midi->check(5, Piano::C) || (GetAsyncKeyState('Q') ? true : false) || (GetAsyncKeyState(VK_OEM_COMMA) ? true : false));
	vPiano.keys[5][Piano::CS].update(midi->check(5, Piano::CS) || (GetAsyncKeyState('2') ? true : false) || (GetAsyncKeyState('L') ? true : false));
	vPiano.keys[5][Piano::D].update(midi->check(5, Piano::D) || (GetAsyncKeyState('W') ? true : false) || (GetAsyncKeyState(VK_OEM_PERIOD) ? true : false));
	vPiano.keys[5][Piano::DS].update(midi->check(5, Piano::DS) || (GetAsyncKeyState('3') ? true : false) || (GetAsyncKeyState(VK_OEM_1) ? true : false));
	vPiano.keys[5][Piano::E].update(midi->check(5, Piano::E) || (GetAsyncKeyState('E') ? true : false) || (GetAsyncKeyState(VK_OEM_2) ? true : false));

	// the virtual piano keyboard keys octave 5/6... R-->] is white keys, 5-->= is black keys (trust me)
	vPiano.keys[5][Piano::F].update(midi->check(5, Piano::F) || (GetAsyncKeyState('R') ? true : false));
	vPiano.keys[5][Piano::FS].update(midi->check(5, Piano::FS) || (GetAsyncKeyState('4') ? true : false));
	vPiano.keys[5][Piano::G].update(midi->check(5, Piano::G) || (GetAsyncKeyState('T') ? true : false));
	vPiano.keys[5][Piano::GS].update(midi->check(5, Piano::GS) || (GetAsyncKeyState('5') ? true : false));
	vPiano.keys[5][Piano::A].update(midi->check(5, Piano::A) || (GetAsyncKeyState('Y') ? true : false));
	vPiano.keys[5][Piano::AS].update(midi->check(5, Piano::AS) || (GetAsyncKeyState('6') ? true : false));
	vPiano.keys[5][Piano::B].update(midi->check(5, Piano::B) || (GetAsyncKeyState('U') ? true : false));
	vPiano.keys[6][Piano::C].update(midi->check(6, Piano::C) || (GetAsyncKeyState('I') ? true : false));
	vPiano.keys[6][Piano::CS].update(midi->check(6, Piano::CS) || (GetAsyncKeyState('9') ? true : false));
	vPiano.keys[6][Piano::D].update(midi->check(6, Piano::D) || (GetAsyncKeyState('O') ? true : false));
	vPiano.keys[6][Piano::DS].update(midi->check(6, Piano::DS) || (GetAsyncKeyState('0') ? true : false));
	vPiano.keys[6][Piano::E].update(midi->check(6, Piano::E) || (GetAsyncKeyState('P') ? true : false));
	vPiano.keys[6][Piano::F].update(midi->check(6, Piano::F) || (GetAsyncKeyState(VK_OEM_4) ? true : false));
	vPiano.keys[6][Piano::FS].update(midi->check(6, Piano::FS) || (GetAsyncKeyState(VK_OEM_PLUS) ? true : false));
	vPiano.keys[6][Piano::G].update(midi->check(6, Piano::G) || (GetAsyncKeyState(VK_OEM_6) ? true : false));

	// the virtual piano keyboard keys octave 4... Q-->] is white keys, 1-->= is black keys (trust me)
	vPiano.keys[4][Piano::C].update(midi->check(4, Piano::C) || (GetAsyncKeyState('Z') ? true : false));
	vPiano.keys[4][Piano::CS].update(midi->check(4, Piano::CS) || (GetAsyncKeyState('S') ? true : false));
	vPiano.keys[4][Piano::D].update(midi->check(4, Piano::D) || (GetAsyncKeyState('X') ? true : false));
	vPiano.keys[4][Piano::DS].update(midi->check(4, Piano::DS) || (GetAsyncKeyState('D') ? true : false));
	vPiano.keys[4][Piano::E].update(midi->check(4, Piano::E) || (GetAsyncKeyState('C') ? true : false));
	vPiano.keys[4][Piano::F].update(midi->check(4, Piano::F) || (GetAsyncKeyState('V') ? true : false));
	vPiano.keys[4][Piano::FS].update(midi->check(4, Piano::FS) || (GetAsyncKeyState('G') ? true : false));
	vPiano.keys[4][Piano::G].update(midi->check(4, Piano::G) || (GetAsyncKeyState('B') ? true : false));
	vPiano.keys[4][Piano::GS].update(midi->check(4, Piano::GS) || (GetAsyncKeyState('H') ? true : false));
	vPiano.keys[4][Piano::A].update(midi->check(4, Piano::A) || (GetAsyncKeyState('N') ? true : false));
	vPiano.keys[4][Piano::AS].update(midi->check(4, Piano::AS) || (GetAsyncKeyState('J') ? true : false));
	vPiano.keys[4][Piano::B].update(midi->check(4, Piano::B) || (GetAsyncKeyState('M') ? true : false));

	// midi update for upper half
	vPiano.keys[6][Piano::GS].update(midi->check(6, Piano::GS));
	vPiano.keys[6][Piano::A].update(midi->check(6, Piano::A));
	vPiano.keys[6][Piano::AS].update(midi->check(6, Piano::AS));
	vPiano.keys[6][Piano::B].update(midi->check(6, Piano::B));
	for (int i = 7; i < Piano::OCTAVES; i++)
	{
		for (int j = 0; j < Piano::KEYS; j++)
		{
			vPiano.keys[i][j].update(midi->check(i, j));
		}
	}

	// determine keypresses for the piano (makes DPS easier later) and keep track of the keystack
	vPiano.numKeysPressed = 0;
	for (int i = 0; i < Piano::OCTAVES; i++)
	{
		for (int j = 0; j < Piano::KEYS; j++)
		{
			if (vPiano.keys[i][j].check())
				vPiano.keyStack[vPiano.numKeysPressed++] = MidiInterface::getKeyValue(i, j);
		}
	}

	// visual look at the virtual keyboard
	if (vPiano.getNumKeysPressed() > 0)
	{
		DebugPrintf("  [vPiano] Pressed: ");
		for (int i = 0; i < vPiano.numKeysPressed; i++)
		{
			DebugPrintf("%d ", vPiano.keyStack[i]);
		}
		DebugPrintf("\n");
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
