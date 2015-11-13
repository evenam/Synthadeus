#include "Synthadeus.h"
#include "Renderables.h"

Synthadeus::Synthadeus()
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
