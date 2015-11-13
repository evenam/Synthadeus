#include "Window.h"
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Window Something or other                                                //
//   Hunter Crossett and Ronald Richardson II                                 //
//   2015-9-21                                                                //
//                                                                            //
//   :: creates static members of CLASSES  				                      //
//   static members on class                                                  //
////////////////////////////////////////////////////////////////////////////////

const char* Window::wndClassName = "NULL";

//Constructor that creates window!
Window::Window(int nCmdShow, int inWidth, int inHeight) :
	wndWidth(inWidth),
	wndHeight(inHeight),
	isInitialized(false),
	windowStyle(WS_OVERLAPPEDWINDOW),
	hWnd(NULL),
	cmdShow(nCmdShow)
{
	// sanity check
	assert(!isInitialized);

	// fill out basic window class for generic overlapped windows
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Window::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = HINST_THISCOMPONENT;
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = wndClassName;
	wcex.hIcon = LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(HINST_THISCOMPONENT, IDC_ARROW);

	// register the class
	if (!RegisterClassEx(&wcex))
		AssertWindowsError();

	// wait for createWindow
}

//Closes window
Window::~Window()
{
	// post the quit message 
	PostQuitMessage(0);
}

void Window::setBordered(bool isBordered)
{
	if (isBordered)
		windowStyle |= WS_THICKFRAME;
	else
		windowStyle &= ~WS_THICKFRAME;
}

void Window::setTitlebarAndButtons(bool hasTitlebar, bool isMinimizeable, bool isMaximizeable)
{
	if (hasTitlebar)
		windowStyle |= WS_CAPTION;
	else
		windowStyle &= ~WS_CAPTION;
	if (isMinimizeable)
		windowStyle |= WS_MINIMIZEBOX;
	else
		windowStyle &= ~WS_MINIMIZEBOX;
	if (isMaximizeable)
		windowStyle |= WS_MAXIMIZEBOX;
	else
		windowStyle &= ~WS_MAXIMIZEBOX;
}

//Event handler equivalent from JS
void Window::runMessageLoop() 
{
	// Pass events to the windows proceedure and update as fast as we can
	MSG msg;
	bool quitFlag = false;
	while (!quitFlag)
	{
		// update cycle
		update();

		// handle system messages
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// once we receive the quit message, end the loop
			if (msg.message == WM_CLOSE || msg.message == WM_QUIT)
				quitFlag = true;
		}
	}
}

HWND Window::getWindowHandle()
{
	// get the window handle for renderer, child windows, etc. 
	return hWnd;
}

void Window::setSize(int width, int height)
{
	wndWidth = width;
	wndHeight = height;
	if (!SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW))
		AssertWindowsError();
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* wnd = NULL;
	if (msg == WM_CREATE)
	{
		// retrieve window pointer passed in lParam
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		wnd = (Window *)pcs->lpCreateParams;
		if (!SetWindowLongPtrW(hWnd, GWLP_USERDATA, PtrToLong(wnd)))
			AssertWindowsError(); 
	}

	// grab a previously set window if this isn't create
	if (!wnd)
		wnd = reinterpret_cast<Window*>(static_cast<LONG_PTR>(GetWindowLongPtrW(hWnd, GWLP_USERDATA)));
	if (!wnd || !wnd->isInitialized)
	{
		AssertWindowsError(); // this shouldn't fail if create was not called prior to other messages
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	// handle message
	int eventCode = wnd->handleMessage(msg, lParam, wParam);
	if (eventCode == -1)
		eventCode = DefWindowProc(hWnd, msg, wParam, lParam);
	return eventCode;
}

void Window::createWindow()
{
	// run initialization code
	assert(initialize());

	// create the window
	hWnd = CreateWindowEx(NULL, wndClassName, "Synthadaeus", windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, wndWidth, wndHeight, NULL, NULL, HINST_THISCOMPONENT, this);
	if (!hWnd)
		AssertWindowsError();

	// show window
	if (!ShowWindow(hWnd, cmdShow))
		AssertWindowsError();

	// update the shown window
	if (!UpdateWindow(hWnd))
		AssertWindowsError();

	// successful initialization
	isInitialized = true;
}

void Window::destroyWindow()
{
	// make sure we uninitialize successfully
	assert(uninitialize());
	isInitialized = false;
}

int Window::getWidth()
{
	// window width check
	return wndWidth;
}

int Window::getHeight()
{
	// window height check
	return wndHeight;
}
