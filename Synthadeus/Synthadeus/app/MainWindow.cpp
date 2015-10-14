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
	return true;
}

bool MainWindow::uninitialize()
{
	return true;
}
