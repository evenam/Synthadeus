#pragma once

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Window Something or other                                                //
//   Hunter Crossett and Ronald Richardson II                                 //
//   2015-9-21                                                                //
//                                                                            //
//   Making windows and shit? IDK Cplus+				                      //
//   static members on class                                                  //
////////////////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "Error.h"
#include "resource.h"

// neat little macro to extract hInstance from exe
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

//Arbitrary sizes
#define WINDOW_DEFAULT_WIDTH 640
#define WINDOW_DEFAULT_HEIGHT 480

// abstract class to help with making a window
class Window
{
private:
	// handles a message, -1 if message not handled
	virtual inline int handleMessage(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	int wndHeight, wndWidth;
	bool isInitialized;

	virtual inline bool initialize() { return true;  } // set up the window, present it
	virtual inline bool uninitialize() { return true; } // safely free all of the resources

	// windows specific statics
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static const char* wndClassName;

	// window!
	HWND hWnd;
	
public:

	Window(int nCmdShow = SW_SHOWNORMAL, int wndWidth = WINDOW_DEFAULT_HEIGHT, int wndHeight = WINDOW_DEFAULT_HEIGHT);
	~Window();

	void runMessageLoop(); // returns on application exit
	
	HWND getWindowHandle(); //window handler
};

