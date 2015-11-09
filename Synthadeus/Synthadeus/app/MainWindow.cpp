#include "MainWindow.h"
#include "BackgroundGrid.h"
#include "BezierCurve.h"
#include "Line.h"
#include "Text.h"

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
	case WM_SIZE:
		forceRender();
	}

	return -1;
}

bool MainWindow::initialize()
{
	this->setBordered(false);
	this->setTitlebarAndButtons(false, false, false);
	shouldDrawRect = false;
	return true;
}

bool MainWindow::uninitialize()
{
	return true;
}

Renderable* MainWindow::generateDrawArea()
{
	BackgroundGrid* grid = new BackgroundGrid(Point(0.f, 0.f), Point((float)wndWidth, (float)wndHeight), Point(50.f, 50.f), COLOR_WHITE, COLOR_BLACK);
	grid->child = new Text("Synthadeus v0.1", Point(0.f, 0.f), Point(150.f, 20.f), FONT_ARIAL20, COLOR_WHITE);
	return grid;
}

void MainWindow::startRenderer()
{
	// make renderer, initial render
	renderer = new Render2D(getWindowHandle());
	Renderable* list = generateDrawArea();
	renderer->addToRenderList(list);
	renderer->render();
}

void MainWindow::endRenderer()
{
	delete renderer;
}

void MainWindow::forceRender()
{
	Renderable* list = generateDrawArea();
	renderer->clearList();
	renderer->addToRenderList(list);
	renderer->render();
}
