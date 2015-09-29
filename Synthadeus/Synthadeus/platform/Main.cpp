#include <Windows.h>
#include "Error.h"
#include "Window.h"
#include "RenderThread.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpwCmdLine, int nCmdShow)
{
	// intialize subcomponents
	DebugLogging::initDebugLogger();

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		CoUninitialize();
	}

	// uninitialize subcomponents and 
	DebugLogging::finishDebugLogger();
	Thread::assertAllThreadsHaveTerminated();
	Object::AssertNoAbandonObjects();
	return 0;
}