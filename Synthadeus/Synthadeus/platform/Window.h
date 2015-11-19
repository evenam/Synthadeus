////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Window Base class                                                        //
//   Hunter Crossett and Ronald Richardson II                                 //
//   2015-9-21                                                                //
//                                                                            //
//   Abstracts window management from the windows API                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

// windows is fat, so we go to the gym before we release it
#if !defined(DEBUG) && !defined(_DEBUG)
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include "Error.h"
#include "resource.h"

// neat little macro to extract hInstance from executable source
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

// abstract class to help with making a window
class Window
{
public:
	// default width and height of a window
	enum { WINDOW_DEFAULT_WIDTH = 640, WINDOW_DEFAULT_HEIGHT = 480 };

private:
	// a boolean to the initialization status of the window
	bool isInitialized;

	// window proceedure and class name to make the API happy
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static const char* wndClassName;

	// window handle, style, and initial display mode
	HWND hWnd;	
	unsigned long windowStyle;
	int cmdShow;

	// window title string buffer
	const static int windowTitleLength = 40;
	char windowTitle[windowTitleLength];
	
protected:
	// window width and height
	int wndHeight, wndWidth;

	// specific window styles
	void setBordered(bool isBordered);
	void setTitlebarAndButtons(bool hasTitlebar, bool isMinimizeable, bool isMaximizeable);

	// overrideable [de]initialization function
	virtual bool initialize() { return true; }
	virtual bool uninitialize() { return true; }
	
	// handles a message, -1 if message not handled
	virtual int handleMessage(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	inline virtual void update() {};

public:

	// constructs a window class
	Window(int nCmdShow = SW_SHOWNORMAL, int wndWidth = WINDOW_DEFAULT_WIDTH, int wndHeight = WINDOW_DEFAULT_HEIGHT);
	~Window();

	// window sizing functions
	void setSize(int width, int height);
	int getWidth();
	int getHeight();

	// run the message loop
	void runMessageLoop(); 
	
	// return the window handle
	HWND getWindowHandle(); 

	// creates and destroys the window
	void createWindow();
	void destroyWindow();
};

