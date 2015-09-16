#include <Windows.h>
#include "Error.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpwCmdLine, int nCmdShow)
{
	DebugLogging::initDebugLogger();
	DebugPrintf("Testing logging....\n");
	MessageBox(NULL, "Hello, world!", "Synthadeus", MB_OK);
	assert(!"Testing assertion...");
	DebugLogging::finishDebugLogger();
	return 0;
}