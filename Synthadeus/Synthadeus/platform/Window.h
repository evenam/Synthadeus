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

// #define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Error.h"
#include "resource.h"

// neat little macro to extract hInstance from exe
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

// abstract class to help with making a window
class Window
{
public:
	enum { WINDOW_DEFAULT_WIDTH = 640, WINDOW_DEFAULT_HEIGHT = 480 };

private:
	bool isInitialized;

	// windows specific statics
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static const char* wndClassName;

	// window!
	HWND hWnd;	
	unsigned long windowStyle;
	int cmdShow;
	
protected:
	int wndHeight, wndWidth;

	// specific styles
	void setBordered(bool isBordered);
	void setTitlebarAndButtons(bool hasTitlebar, bool isMinimizeable, bool isMaximizeable);

	virtual bool initialize() { return true; } // set up the window, present it
	virtual bool uninitialize() { return true; } // safely free all of the resources
	
	// handles a message, -1 if message not handled
	virtual int handleMessage(UINT msg, WPARAM wParam, LPARAM lParam) = 0;

public:

	Window(int nCmdShow = SW_SHOWNORMAL, int wndWidth = WINDOW_DEFAULT_WIDTH, int wndHeight = WINDOW_DEFAULT_HEIGHT);
	~Window();

	void setSize(int width, int height);

	void runMessageLoop(); // returns on application exit
	
	HWND getWindowHandle(); //window handler

	void createWindow();
	void destroyWindow();
};

