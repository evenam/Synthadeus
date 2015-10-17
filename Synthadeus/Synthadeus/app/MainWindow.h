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

class MainWindow : public Window
{
protected:
	Render2D* renderer;

	virtual int handleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	virtual bool initialize();
	virtual bool uninitialize();

	using Window::Window;

public:
	void startRenderer();
	void endRenderer();
};

