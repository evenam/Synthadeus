#include "Synthadeus.h"
#include "Renderables.h"

void Synthadeus::updateViewport()
{
	// update viewport movement amount with keyboard state data (false = 0 by definition)
	viewportMoveAmount[0] += inputDevice->vController.left.check() * viewportTranslateAcceleration;
	viewportMoveAmount[0] += inputDevice->vController.right.check() * -viewportTranslateAcceleration;
	viewportMoveAmount[1] += inputDevice->vController.down.check() * -viewportTranslateAcceleration;
	viewportMoveAmount[1] += inputDevice->vController.up.check() * viewportTranslateAcceleration;

	// apply friction constant
	viewportMoveAmount[0] *= viewportFriction;
	viewportMoveAmount[1] *= viewportFriction;

	// cap off the delta position
	if (viewportMoveAmount[0] > viewportMaxTranslateSpeed)
		viewportMoveAmount[0] = viewportMaxTranslateSpeed;
	if (viewportMoveAmount[0] < -viewportMaxTranslateSpeed)
		viewportMoveAmount[0] = -viewportMaxTranslateSpeed;
	if (viewportMoveAmount[1] > viewportMaxTranslateSpeed)
		viewportMoveAmount[1] = viewportMaxTranslateSpeed;
	if (viewportMoveAmount[1] < -viewportMaxTranslateSpeed)
		viewportMoveAmount[1] = -viewportMaxTranslateSpeed;

	// bring to stop if below delta espilon (whats a limit proof?)
	if (fabsf(viewportMoveAmount[0]) < viewportEpsilon)
		viewportMoveAmount[0] = 0.f;
	if (fabsf(viewportMoveAmount[1]) < viewportEpsilon)
		viewportMoveAmount[1] = 0.f;

	// move the viewport
	appWindow->viewportApplyTranslation(viewportMoveAmount);

	// if the user presses enter, reset view
	if (inputDevice->vController.center.checkPressed())
	{
		appWindow->viewportSetDefault();
		viewportMoveAmount[0] = 0.f;
		viewportMoveAmount[1] = 0.f;
	}
}

Synthadeus::Synthadeus()
	: viewportFriction(0.95f), viewportEpsilon(0.5f), viewportTranslateAcceleration(2.f),
	viewportZoomAcceleration(0.1f), viewportMaxTranslateSpeed(5.f), viewportMaxZoomSpeed(1.f)
{
	DebugPrintf("Starting Synthadeus.\n");

	// create the window
	appWindow = new MainWindow(this, SW_SHOWNORMAL, 1280, 768);
	appWindow->createWindow();
	DebugPrintf("Window Created.\n");

	// start the renderer
	appWindow->startRenderer();
	DebugPrintf("Renderer Started.\n");

	// create the input device
	inputDevice = new InputDevice();
	DebugPrintf("Input Device Allocated.\n");

	// create midi interface
	midiInterface = new MidiInterface();
	assert(midiInterface->initialize());
	DebugPrintf("midi successfully initialized\n");

	// initialize the base with an audio endpoint
	base = new GridBase(Point(-640.f, -640.f), Point(appWindow->getWidth() + 1280.f, appWindow->getHeight() + 1280.f), COLOR_LTGREY, COLOR_BLACK);
	audioOutputEndpoint = new AudioOutputNode(Point(appWindow->getWidth() + 340.f, appWindow->getHeight() * 0.5f + 610.f));
	base->addChild(audioOutputEndpoint);

	// create the audio playback interface
	audioInterface = new AudioPlayback(audioOutputEndpoint, &inputDevice->vPiano);
	assert(audioInterface->initialize());
	DebugPrintf("audio successfully initialized\n");

	// success!
	DebugPrintf("Base Components Initialized.\n");
}

Synthadeus::~Synthadeus()
{
	// starting shutdown
	DebugPrintf("Shutting down Synthadeus.\n");

	// free the midi
	DebugPrintf("Deinitializing Midi Interface\n");
	midiInterface->deinitialize();

	// free the audio interface
	DebugPrintf("Deinitializing audio interface\n");
	audioInterface->deinitialize();

	//  end the renderer
	appWindow->endRenderer();
	DebugPrintf("Ended Renderer.\n");

	// kill the window
	appWindow->destroyWindow();
	delete appWindow;
	DebugPrintf("Destroyed the window.\n");

	// free the component tree
	DebugPrintf("Freeing components\n");
	base->signalRemoval();
	base->sweepDeletion();

	// free local references to devices and the base
	delete midiInterface;
	delete audioInterface;
	delete inputDevice;
	delete base;
	DebugPrintf("Freed Base Components.\n");

	// success!
	DebugPrintf("Synthadeus Shutdown Complete.\n");
}

void Synthadeus::run()
{
	// the initial render
	appWindow->setRenderList(getRenderList());
	appWindow->render();
	DebugPrintf("Initial Render.\n");

	// run the application message loop
	appWindow->runMessageLoop();
}

void Synthadeus::update()
{
	// update the input device
	inputDevice->update(midiInterface);

	// update the viewport
	updateViewport();

	// pass an instanced mouse through to the base component to handle mouse events
	inputDevice->vMouse.instance(appWindow->getViewportInstance());
	base->handleMouseInput(this, &inputDevice->vMouse);
	inputDevice->vMouse.restore();

	// call component update methods
	base->updateTree();

	// apply sweep garbage collection, destroying everything that vanishes this frame
	base->sweepDeletion();

	// apply the wave export function if we press F5
	if (inputDevice->vController.waveExport.checkReleased())
	{
		recalculateAudioGraph();
		WaveExporter exporter(audioOutputEndpoint->getAudioNode()->getBufferSize(), audioOutputEndpoint->getAudioNode()->getBufferL(), audioOutputEndpoint->getAudioNode()->getBufferR());
		exporter.prepareExport();
		exporter.saveWaveFile();
		exporter.unprepareExport();
	}

	// quit the application if we pressed escape
	if (inputDevice->vController.quit.checkReleased())
		quit();

	// reset the scroll wheel delta
	inputDevice->vMouse.scrollDelta = 0;
}

bool Synthadeus::needsRendering()
{
	// for now, we always need to render
	return true;
}

Renderable* Synthadeus::getRenderList()
{
	// create the watermark
	Renderable* watermark = new Text(SYNTHADEUS_VERSION, -1.f * appWindow->getViewportInstance(), Point((float)appWindow->getWidth(), 40.f), FONT_ARIAL40, COLOR_LTGREY);
	
	// append it to the current render list
	Renderable* renderList = sortRenderList(base->getRenderTree());
	renderList->next = watermark;

	// return the new render list
	return renderList;
}

InputDevice* Synthadeus::getInputDevice()
{
	// return the input device, asserting that it exists
	assert(inputDevice);
	return inputDevice;
}

void Synthadeus::quit()
{
	// give the window the quit message, terminating the realtime logic loop
	SendMessage(appWindow->getWindowHandle(), WM_QUIT, 0, 0);
}

Component* Synthadeus::findComponentAtLocation(Point pt)
{
	// search through the components, narrowing the area by instanced coordinate systems
	return base->getComponentAtPoint(pt -appWindow->getViewportInstance());
}

Renderable * Synthadeus::sortRenderList(Renderable * list)
{
	// TODO: sort the bezier curves to the end (for now we return the raw list)
	return list;
}

void Synthadeus::createOscillatorNode()
{
	// create the oscillator node relative to the base component
	Point place = inputDevice->vMouse.position - base->getOrigin() - appWindow->getViewportInstance();

	// add it to the base
	base->addChild(new OscillatorNode(place));
}

void Synthadeus::createEnvelopeNode()
{
	// let the user know the feature is incomplete, taking note to prioritize feature development order
	MessageBox(appWindow->getWindowHandle(), "Feature not yet fully implemented. ", "Whoops!", MB_ICONERROR);
	DebugPrintf("User requested non-existant feature: Envelope Node\n");
}

void Synthadeus::createConstantNode()
{
	// create the constant node relative to the base component
	Point place = inputDevice->vMouse.position - base->getOrigin() - appWindow->getViewportInstance();

	// add it to the base
	base->addChild(new ConstantNode(place));
}

void Synthadeus::createMultiplierNode()
{
	// create the multiplier node relative to the base component
	Point place = inputDevice->vMouse.position - base->getOrigin() - appWindow->getViewportInstance();

	// add it to the base
	base->addChild(new MultiplierNode(place));
}

void Synthadeus::createSummationNode()
{
	// create the summation node relative to the base component
	Point place = inputDevice->vMouse.position - base->getOrigin() - appWindow->getViewportInstance();

	// add it to the base
	base->addChild(new SummationNode(place));
}

void Synthadeus::recalculateAudioGraph()
{
	// should figure out how to minimize these calls by looking at the logs afterward
	DebugPrintf("User did something to force the recalculation of the audio graph.");

	// show a brief message while the program recalculates (could be upwards of several seconds if the graph is LARGE)
	Renderable* recalculatingMark = new Text("Calculating", -1.f * appWindow->getViewportInstance() + Point(0.f, appWindow->getHeight() / 2.f), Point((float)appWindow->getWidth(), 40.f), FONT_ARIAL40, COLOR_WHITE);
	
	// get the application render list, asserting there is the base and the watermark
	Renderable* list = getRenderList();
	assert(list->next);

	// append the message
	list->next->next = recalculatingMark;

	// force render
	appWindow->setRenderList(list);
	appWindow->render();

	// start the graph update process (slow)
	audioOutputEndpoint->getAudioNode()->recalculate();
}