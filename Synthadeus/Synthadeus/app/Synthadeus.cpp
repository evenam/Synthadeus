#include "Synthadeus.h"
#include "Renderables.h"

Synthadeus::Synthadeus()
	: viewportFriction(0.5f), viewportEpsilon(0.001), viewportTranslateAcceleration(2.f),
	viewportZoomAcceleration(0.1), viewportMaxTranslateSpeed(5.f), viewportMaxZoomSpeed(1.f)
{
	DebugPrintf("Starting Synthadeus.\n");

	// create the window and start the renderer
	appWindow = new MainWindow(this, SW_SHOWNORMAL, 1200, 800);
	appWindow->createWindow();
	appWindow->startRenderer();
}

Synthadeus::~Synthadeus()
{
	DebugPrintf("Shutting down Synthadeus.\n");

	// destroy the window and end the renderer
	appWindow->endRenderer();
	appWindow->destroyWindow();
	delete appWindow;
}

void Synthadeus::run()
{
	appWindow->setRenderList(getRenderList());
	appWindow->render();
	appWindow->runMessageLoop();
}

void Synthadeus::update()
{
	// APPLICATION CODE NEEDED!

	// update viewport movement amount with keyboard state data
	viewportMoveAmount[0] += (GetAsyncKeyState(VK_LEFT) ? viewportTranslateAcceleration : 0);
	viewportMoveAmount[0] += (GetAsyncKeyState(VK_RIGHT) ? -viewportTranslateAcceleration : 0);
	viewportMoveAmount[1] += (GetAsyncKeyState(VK_DOWN) ? -viewportTranslateAcceleration : 0);
	viewportMoveAmount[1] += (GetAsyncKeyState(VK_UP) ? viewportTranslateAcceleration : 0);
	
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
	if (GetAsyncKeyState(VK_RETURN))
		appWindow->viewportSetDefault();
}

bool Synthadeus::needsRendering()
{
	// for now, we always need to render
	return true;
}

Renderable* Synthadeus::getRenderList()
{
	return new BackgroundGrid(Point(0.f, 0.f), Point((float)appWindow->getWidth(), (float)appWindow->getHeight()),
		Point(32.f, 32.f), COLOR_WHITE, COLOR_BLACK);
}
