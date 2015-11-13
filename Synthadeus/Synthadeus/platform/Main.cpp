#include "Error.h"
#include "CFMaths.h"
#include "Synthadeus.h"

// program entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpwCmdLine, int nCmdShow)
{
	// intialize subcomponents
	DebugLogging::initDebugLogger();
	CFMaths::init();

	// set up heap
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// initialize with COM
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		// run the application
		Synthadeus synthesizer;
		synthesizer.run();

		// uninitialize COM
		CoUninitialize();
	}

	// uninitialize subcomponents and make sure we have cleaned up
	Object::AssertNoAbandonObjects();
	DebugLogging::finishDebugLogger();

	// exit success!
	return EXIT_SUCCESS;
}