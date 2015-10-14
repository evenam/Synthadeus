#include "Synthadeus.h"
#include "Error.h"
#include "MainWindow.h"
#include "Render2D.h"

Synthadeus::Synthadeus()
{
	MainWindow wnd(SW_SHOWNORMAL);
	Render2D renderer(wnd.getWindowHandle());
	renderer.beginRenderThread();
	wnd.runMessageLoop();
	renderer.endRenderThread();
}

Synthadeus::~Synthadeus()
{
}
