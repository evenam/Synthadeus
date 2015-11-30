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
#include "OscillatorNode.h"
#include "SummationNode.h"
#include "ConstantNode.h"
#include "MultiplierNode.h"

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

	// viewport friction constant
	const float viewportFriction;

	// viewport acceleration for translation
	const float viewportTranslateAcceleration;

	// viewport acceleration for zoom
	const float viewportZoomAcceleration;

	// viewport error minimum to stop movement
	const float viewportEpsilon;

	// the maximum speed the viewport can move
	const float viewportMaxTranslateSpeed;
	
	// the max speed the viewport can be zoomed
	const float viewportMaxZoomSpeed;

	// the total amount to translate the viewport
	Point viewportMoveAmount;

	// the total amount to zoom the viewport
	float viewportZoomAmount;

	// viewport modification with arrow keys and scroll wheel
	void updateViewport();

	// the base of the UI tree: a grid
	GridBase* base;

public:
	// constructs the awesome! initializes everything and prepares the application to enter the update loop
	Synthadeus();

	// deinitializes everything and frees memory references before we clean up the rest of the COM
	~Synthadeus();

	// start up the application
	void run();

	// update happens once every ~16ms
	virtual void update();

	// always true, needs optimization, which signals whether the application needs to render this update cycle
	virtual bool needsRendering();

	// get the render list for the application
	virtual Renderable* getRenderList();

	// get the input device for the application
	virtual InputDevice* getInputDevice();

	// request the application to close
	void quit();

	// find a component
	Component* findComponentAtLocation(Point pt);

	// resort render list
	Renderable* sortRenderList(Renderable* list);

	// create an oscillator within the base node
	void createOscillatorNode();

	// create an envelope within the base node
	void createEnvelopeNode();

	// create an constant within the base node
	void createConstantNode();

	// create an multiplier within the base node
	void createMultiplierNode();

	// create an summation within the base node
	void createSummationNode();

	// recalculate audio
	void recalculateAudioGraph();
};

