////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Synthadeus Main Application Class                                        //
//   Everett Moser                                                            //
//   9-28-15                                                                  //
//                                                                            //
//   The main class for the application                                       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Error.h"
#include "MainWindow.h"
#include "InputDevice.h"
#include "Button.h"
#include "GridBase.h"
#include "Node.h"
#include "Slider.h"
#include "Connector.h"
#include "MidiInterface.h"
#include "AudioOutputNode.h"
#include "AudioPlayback.h"
#include "WaveExporter.h"

#define SYNTHADEUS_VERSION "Synthadeus 0.9" // arbitrary number kek

class Synthadeus : public Application
{
private:
	// pointer to the window
	MainWindow* appWindow;

	// input device
	InputDevice* inputDevice;

	// midi interface
	MidiInterface* midiInterface;

	// audio interface
	AudioPlayback* audioInterface;

	// the output node to play audio back from
	AudioOutputNode* audioOutputEndpoint;

	// viewport momentum and cool stuff
	const float viewportFriction;
	const float viewportTranslateAcceleration;
	const float viewportZoomAcceleration;
	const float viewportEpsilon;
	const float viewportMaxTranslateSpeed;
	const float viewportMaxZoomSpeed;
	Point viewportMoveAmount;
	float viewportZoomAmount;

	// viewport modification with arrow keys and scroll wheel
	void updateViewport();

	GridBase* base;
	Button* projectPageButton;
	Node* testNode;

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
	virtual InputDevice* getInputDevice();

	// request the application to close
	void quit();

	// find a component
	Component* findComponentAtLocation(Point pt);

	// resort render list
	Renderable* sortRenderList(Renderable* list);

	// graph creation
	void createOscillatorNode();
	void createEnvelopeNode();
};

