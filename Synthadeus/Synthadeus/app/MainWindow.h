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
class InputDevice;
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
	virtual InputDevice* getInputDevice() = 0;
};

// the main window class for Synthadeus
class MainWindow : public Window
{
protected:
	// renderer for the window
	Render2D* renderer;

	// handle windows messages
	virtual int handleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	// initialize any information prior to window creation
	virtual bool initialize();

	// deinitialize any informatiotion necessary before removal
	virtual bool uninitialize();

	// pointer to application logic object
	Application* application;

	// the update function override from Window
	virtual void update();

	// update the window dimensions to the actual ones (like on resize)
	void updateWindowDimensions();

public:
	// request a render frame
	void render();

	// start the renderer
	void startRenderer();

	// stop the renderer
	void endRenderer();

	// add an item to the render list
	void addToRenderList(Renderable* list);

	// free the old list
	void clearRenderList();

	// set the current list 
	void setRenderList(Renderable* list);
	
	// returns the current render list the renderer is being sent
	Renderable* getRenderList();

	// apply a viewport zoom
	void viewportApplyZoom(float factor);

	// apply a viewort translation
	void viewportApplyTranslation(Point factor);

	// reset the viewport to the default position
	void viewportSetDefault();

	// get the viewport coordinates
	Point getViewportInstance();

	// constructor from window to initialize the window and the logic object
	MainWindow(Application* app, int nCmdShow = SW_SHOWNORMAL, int wndWidth = WINDOW_DEFAULT_WIDTH, int wndHeight = WINDOW_DEFAULT_HEIGHT);
};

