#include "MainWindow.h"
#include "BackgroundGrid.h"

int MainWindow::handleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_QUIT:
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;

	case WM_PAINT:
		renderer->forceReRender();
		return 0;
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
	//BackgroundGrid* grid;
	BezierCurve<4>* grid;
	//grid = new BackgroundGrid(Point(0.f, 0.f), Point(wndWidth, wndHeight), Point(32.f, 32.f), COLOR_WHITE, COLOR_BLACK);
	grid = new BezierCurve<4>(Point(0.f, 0.f), Point(wndWidth / 2.f, 0.f), Point(wndWidth / 2.f, wndHeight), Point(wndWidth, wndHeight));
	renderer->sendRenderList(grid);
}

void MainWindow::endRenderer()
{
	renderer->endRenderThread();
	delete renderer;
}
