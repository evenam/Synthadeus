#pragma once

#include <Windows.h>

#define WINDOW_DEFAULT_WIDTH 640
#define WINDOW_DEFAULT_HEIGHT 480

// preliminary skeleton for a window class

class Window
{
private:
	void handleMessage(UINT msg); // one cycle of the event loop, eventually we will run this on a separate thread ro two
	HWND hWnd;

public:

	Window(int wndWidth = WINDOW_DEFAULT_HEIGHT, int wndHeight = WINDOW_DEFAULT_HEIGHT);
	~Window();

	void initialize(); // set up the window, present it
	void uninitialize(); // safely free all of the resources

	void runMessageLoop(); // returns on application exit
	
	HWND& getWindowHandle();
};

