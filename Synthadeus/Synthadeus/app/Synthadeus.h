#pragma once

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Synthadeus Main Application Class                                        //
//   Everett Moser                                                            //
//   9-28-15                                                                  //
//                                                                            //
//   The main class for the application                                       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "Error.h"
#include "MainWindow.h"

class Synthadeus : public Application
{
	// pointer to the window
	MainWindow* appWindow;

	// viewport momentum and cool stuff
	const float viewportFriction;
	const float viewportTranslateAcceleration;
	const float viewportZoomAcceleration;
	const float viewportEpsilon;
	const float viewportMaxTranslateSpeed;
	const float viewportMaxZoomSpeed;
	Point viewportMoveAmount;
	float viewportZoomAmount;

public:
	// create and destroy the application
	Synthadeus();
	~Synthadeus();

	// start up the application
	void run();

	// overrides from Application interface
	virtual void update();
	virtual bool needsRendering();
	virtual Renderable* getRenderList();
};

