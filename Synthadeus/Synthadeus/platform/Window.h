#pragma once

#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Window Something or other                                                //
//   Hunter Crossett and Ronald Richardson II                                 //
//   2015-9-21                                                                //
//                                                                            //
//   Making windows and shit? IDK Cplus+				                      //
//   static members on class                                                  //
////////////////////////////////////////////////////////////////////////////////
//Arbitrary sizes
#define WINDOW_DEFAULT_WIDTH 640
#define WINDOW_DEFAULT_HEIGHT 480

// preliminary skeleton for a window class

class Window
{
private:
	void handleMessage(UINT msg); // one cycle of the event loop, eventually we will run this on a separate thread or two
	HWND hWnd;
	int wndHeight, wndWidth;
	
public:

	Window(int wndWidth = WINDOW_DEFAULT_HEIGHT, int wndHeight = WINDOW_DEFAULT_HEIGHT);
	~Window();

	void initialize(); // set up the window, present it
	void uninitialize(); // safely free all of the resources

	void runMessageLoop(); // returns on application exit
	
	HWND& getWindowHandle(); //window handler
};

