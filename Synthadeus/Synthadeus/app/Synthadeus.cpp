#include "Synthadeus.h"
#include "Error.h"
#include "MainWindow.h"
#include "Render2D.h"

Synthadeus::Synthadeus()
{
	MainWindow wnd(SW_SHOWNORMAL);
	wnd.createWindow();
	wnd.startRenderer();
	wnd.runMessageLoop();
	wnd.endRenderer();
	wnd.destroyWindow();
}

Synthadeus::~Synthadeus()
{
}
