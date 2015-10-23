#include "MainWindow.h"

int MainWindow::handleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_QUIT:
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;
	}
	return -1;
}

bool MainWindow::initialize()
{
	setBordered(false);
	setTitlebarAndButtons(false, false, false);
	return true;
}

bool MainWindow::uninitialize()
{
	return true;
}

void MainWindow::startRenderer()
{
	renderer = new Render2D(getWindowHandle());
	renderer->beginRenderThread();
}

void MainWindow::endRenderer()
{
	renderer->endRenderThread();
	delete renderer;
}
