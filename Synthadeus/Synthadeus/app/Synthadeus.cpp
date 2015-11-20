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

	// create the window and start the renderer
	appWindow = new MainWindow(this, SW_SHOWNORMAL, 1280, 768);
	appWindow->createWindow();
	DebugPrintf("Window Created.\n");

	appWindow->startRenderer();
	DebugPrintf("Renderer Started.\n");


	// create the input device
	inputDevice = new InputDevice();
	DebugPrintf("Input Device Allocated.\n");

	base = new GridBase(Point(-640.f, -640.f), Point(appWindow->getWidth() + 1280.f, appWindow->getHeight() + 1280.f), COLOR_LTGREY, COLOR_BLACK);
	
	testNode = new Node(Point(700.f, 700.f), Point(200.f, 200.f), COLOR_CORNFLOWERBLUE, COLOR_ABLACK);
	//projectPageButton = new Button(Point(10.f, 10.f), Point(50.f, 50.f), COLOR_ABLACK, COLOR_RED, "SIN", FONT_ARIAL11);
	testNode->addChild(new InputConnector(Point(10.f, 10.f), Point(50.f, 50.f), COLOR_ORANGE, testNode));
	projectPageButton = new Button(Point(75.f, 10.f), Point(50.f, 50.f), COLOR_ABLACK, COLOR_RED, "SAW", FONT_ARIAL11);
	testNode->addChild(projectPageButton);
	projectPageButton = new Button(Point(140.f, 10.f), Point(50.f, 50.f), COLOR_ABLACK, COLOR_RED, "SQR", FONT_ARIAL11);
	testNode->addChild(projectPageButton);
	testNode->addChild(new Slider(Point(20.f, 70.f), Point(20.f, 80.f), COLOR_ABLACK, COLOR_RED, Slider::VERTICAL));
	base->addChild(testNode);
	testNode = new Node(Point(950.f, 700.f), Point(200.f, 200.f), COLOR_ORANGE, COLOR_ABLACK);
	base->addChild(testNode);
	testNode = new Node(Point(1200.f, 700.f), Point(200.f, 200.f), COLOR_GREEN, COLOR_ABLACK);
	base->addChild(testNode);
	DebugPrintf("Base Components Initialized.\n");
}

Synthadeus::~Synthadeus()
{
	DebugPrintf("Shutting down Synthadeus.\n");

	// destroy the window and end the renderer
	appWindow->endRenderer();
	DebugPrintf("Ended Renderer.\n");
	appWindow->destroyWindow();
	delete appWindow;
	DebugPrintf("Destroyed the window.\n");

	// free the input device
	delete inputDevice;
	delete projectPageButton;
	delete base;
	DebugPrintf("Freed Base Components.\n");

	DebugPrintf("Synthadeus Shutdown Complete.\n");
}

void Synthadeus::run()
{
	appWindow->setRenderList(getRenderList());
	appWindow->render();
	DebugPrintf("Initial Render.\n");

	appWindow->runMessageLoop();
}

void Synthadeus::update()
{
	// APPLICATION CODE NEEDED!
	// update the input device
	inputDevice->update();

	// update the viewport
	updateViewport();

	base->updateTree();

	inputDevice->vMouse.instance(appWindow->getViewportInstance());
	//if (inputDevice->vMouse.left.check())
		base->handleMouseInput(this, &inputDevice->vMouse);
	inputDevice->vMouse.restore();

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
	inputDevice->vMouse.instance(appWindow->getViewportInstance());
	Component* hover = base->getComponentAtPoint(inputDevice->vMouse.instancePosition());
	inputDevice->vMouse.restore();
	Renderable* watermark = new Text((hover == NULL) ? SYNTHADEUS_VERSION : hover->getClassName(), -1.f * appWindow->getViewportInstance(), Point((float)appWindow->getWidth(), 40.f), FONT_ARIAL40, COLOR_LTGREY);
	Renderable* renderList = base->getRenderTree();
	renderList->next = watermark;
	return renderList;
}

InputDevice* Synthadeus::getInputDevice()
{
	return inputDevice;
}

void Synthadeus::quit()
{
	// give the window the quit message, terminating the realtime logic loop
	SendMessage(appWindow->getWindowHandle(), WM_QUIT, 0, 0);
}

Component* Synthadeus::findComponentAtLocation(Point pt)
{
	return base->getComponentAtPoint(pt);
}
