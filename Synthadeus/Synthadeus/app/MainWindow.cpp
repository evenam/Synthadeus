#include "MainWindow.h"

int MainWindow::handleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_QUIT:
	case WM_CLOSE:
		// handle quit message
		PostQuitMessage(0);
		return 0;
		break;
	case WM_PAINT:
	case WM_SIZE:
		// we need to re-render the window contents
		render();
	}

	return -1;
}

bool MainWindow::initialize()
{
	// make the window be non-resizeable and only have a close button
	setBordered(false);
	setTitlebarAndButtons(true, true, false);
	return true;
}

bool MainWindow::uninitialize()
{
	// nothing to uninitialize
	return true;
}

MainWindow::MainWindow(Synthadeus* app, int nCmdShow, int wndWidth, int wndHeight)
	: Window(nCmdShow, wndWidth, wndHeight)
{
	// save off application pointer
	application = app;
}

void MainWindow::render()
{
	// render the window contents
	renderer->render();
}

void MainWindow::startRenderer()
{
	// make renderer
	renderer = new Render2D(getWindowHandle());
}

void MainWindow::endRenderer()
{
	// remove the renderer
	delete renderer;
}

void MainWindow::addToRenderList(Renderable * list)
{
	// add the item to the renderer's list
	renderer->addToRenderList(list);
}

void MainWindow::clearRenderList()
{
	// clear the renderer's list
	renderer->clearList();
}

void MainWindow::setRenderList(Renderable * list)
{
	// clear the render list
	renderer->clearList();

	// update the list to the new list
	renderer->addToRenderList(list);
}

Renderable * MainWindow::getRenderList()
{
	// get the render list from the renderer
	return renderer->getRenderList();
}
