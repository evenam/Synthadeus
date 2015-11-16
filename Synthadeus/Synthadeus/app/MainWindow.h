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

// interface so the window can render and process the application properly
class InputDeviceState;
class Application
{
public:
	// called as much as possible
	virtual void update() = 0;

	// figure out if we need to render
	virtual bool needsRendering() = 0;

	// called whenever we need to render
	virtual Renderable* getRenderList() = 0;

	// get the virtual input device so we may update it
	virtual InputDeviceState* getInputDevice() = 0;
};

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
	Application* application;

	// the update function override from Window
	virtual void update();

	// update the window dimensions to the actual ones (like on resize)
	void updateWindowDimensions();

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

	// modify the renderer viewport
	void viewportApplyZoom(float factor);
	void viewportApplyTranslation(Point factor);
	void viewportSetDefault();
	Point getViewportInstance();

	// constructor from window to initialize the window and the logic object
	MainWindow(Application* app, int nCmdShow = SW_SHOWNORMAL, int wndWidth = WINDOW_DEFAULT_WIDTH, int wndHeight = WINDOW_DEFAULT_HEIGHT);
};

