#include "MainWindow.h"
#include "BackgroundGrid.h"
#include "BezierCurve.h"
#include "Line.h"
#include "Text.h"
#include "Rectangle2.h"
#include "RoundedRectangle.h"

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
	this->setTitlebarAndButtons(true, true, false);
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
	RoundedRectangle* synthadeusVersionTagBackground = new RoundedRectangle(Point(5.f, 5.f), Point(185.f, 45.f), COLOR_WHITE, COLOR_BLACK, 5.f, 5.f);
	Text* synthadeusVersionText = new Text("Synthadeus v0.1", Point(10.f, 10.f), Point(170.f, 30.f), FONT_ARIAL20, COLOR_WHITE);
	
	synthadeusVersionTagBackground->child = synthadeusVersionText;
	grid->child = synthadeusVersionTagBackground;

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
	renderer->render();
}
