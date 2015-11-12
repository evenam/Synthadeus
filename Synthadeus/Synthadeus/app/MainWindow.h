////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   The Main Window for the Program                                          //
//   Everett Moser                                                            //
//   10-5-15                                                                  //
//                                                                            //
//   The main window derived class for Synthadeus                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Window.h"
#include "Render2D.h"

class Synthadeus;

class MainWindow : public Window
{
protected:
	// renderer for the window
	Render2D* renderer;

	// handle windows messages
	virtual int handleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	// initialize and deinitize any information prior to window creation/deletion
	virtual bool initialize();
	virtual bool uninitialize();

	// pointer to application logic object
	Synthadeus* application;

public:
	// start, stop and render with the window renderer
	void render();
	void startRenderer();
	void endRenderer();

	// modify render list for window's renderer
	void addToRenderList(Renderable* list);
	void clearRenderList();
	void setRenderList(Renderable* list);
	Renderable* getRenderList();

	// constructor from window to initialize the window and the logic object
	MainWindow(Synthadeus* app, int nCmdShow = SW_SHOWNORMAL, int wndWidth = WINDOW_DEFAULT_WIDTH, int wndHeight = WINDOW_DEFAULT_HEIGHT);
};

