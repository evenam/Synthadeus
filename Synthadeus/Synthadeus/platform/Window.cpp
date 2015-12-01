////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Window Something or other                                                //
//   Hunter Crossett and Ronald Richardson II                                 //
//   2015-9-21                                                                //
//                                                                            //
//   :: creates static members of CLASSES  				                      //
//   static members on class                                                  //
////////////////////////////////////////////////////////////////////////////////

#include "Window.h"

// window class name
const char* Window::wndClassName = "NULL";

// minimum ms before going onto the next frame
const static float minFrameMS = 1000.f / 60.f;

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
	wcex.hIcon = LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDI_ICON1));   // thanks Justin!
	wcex.hIconSm = LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDI_ICON1)); // icon is swag
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

	// register the class
	if (!RegisterClassEx(&wcex))
		AssertWindowsError();

	// set up the window title
	sprintf_s(windowTitle, "%s\0", "Synthadeus");

	// wait for createWindow
}

Window::~Window()
{
	//Closes window
	DestroyWindow(hWnd);
}

void Window::setBordered(bool isBordered)
{
	// toggle the border
	if (isBordered)
		windowStyle |= WS_THICKFRAME;
	else
		windowStyle &= ~WS_THICKFRAME;
}

void Window::setTitlebarAndButtons(bool hasTitlebar, bool isMinimizeable, bool isMaximizeable)
{
	// toggle on titlebar window style
	if (hasTitlebar)
		windowStyle |= WS_CAPTION;
	else
		windowStyle &= ~WS_CAPTION;

	// toggle the minimize bar
	if (isMinimizeable)
		windowStyle |= WS_MINIMIZEBOX;
	else
		windowStyle &= ~WS_MINIMIZEBOX;

	// toggle the maximize bar
	if (isMaximizeable)
		windowStyle |= WS_MAXIMIZEBOX;
	else
		windowStyle &= ~WS_MAXIMIZEBOX;
}

//Event handler equivalent from JS
void Window::runMessageLoop() 
{
	DebugPrintf("Message Loop Started.\n");

	// performance counter data
	_LARGE_INTEGER pc;
	_LARGE_INTEGER freq;
	double interval, tOld, tNew, frameMS;

	// query interval and initial performance counter
	QueryPerformanceCounter(&pc);
	QueryPerformanceFrequency(&freq);
	interval = 1000.f / (double)(freq.QuadPart);
	tNew = (double)pc.QuadPart;

	// Pass events to the windows proceedure and update as fast as we can
	MSG msg;
	bool quitFlag = false;
	while (!quitFlag)
	{
		// start frame time
		tOld = tNew;

		// update cycle
		update();

		// handle system messages
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// once we receive the quit message, end the loop
			if (msg.message == WM_CLOSE || msg.message == WM_QUIT)
			{
				quitFlag = true;
			}
		}

		// get frame time
		QueryPerformanceCounter(&pc);
		tNew = (double)pc.QuadPart;
		frameMS = (tNew - tOld) * interval;

		// set window title
		sprintf_s(windowTitle, "%s FPS: %6.3f\0", "Synthadeus", 1000.f / frameMS);
		SetWindowText(hWnd, windowTitle);

		// hold till 10FPS
		if (frameMS < minFrameMS)
			Sleep((int)(minFrameMS - frameMS));
	}
	DebugPrintf("Message Loop Ended.\n");
}

HWND Window::getWindowHandle()
{
	// get the window handle for renderer, child windows, etc. 
	return hWnd;
}

void Window::setSize(int width, int height)
{
	// set the width and the height
	wndWidth = width;
	wndHeight = height;

	// make sure the window updates properly
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

		// failed to get the window pointer
		if (!SetWindowLongPtrW(hWnd, GWLP_USERDATA, PtrToLong(wnd)))
			AssertWindowsError(); 
	}

	// grab a previously set window if this isn't create
	if (!wnd)
		wnd = reinterpret_cast<Window*>(static_cast<LONG_PTR>(GetWindowLongPtrW(hWnd, GWLP_USERDATA)));

	// if the window has not been initialized, just pass it down
	if (!wnd || !wnd->isInitialized)
	{
		AssertWindowsError(); // this shouldn't fail if create was not called prior to other messages
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	// handle message
	int eventCode = wnd->handleMessage(msg, lParam, wParam);

	// message wasn't handled, pass it down
	if (eventCode == -1)
		eventCode = DefWindowProc(hWnd, msg, wParam, lParam);

	return eventCode;
}

void Window::createWindow()
{
	// run initialization code
	assert(initialize());

	// calculate window size from client area
	RECT windowRect;
	windowRect.top = 0;
	windowRect.left = 0;
	windowRect.bottom = wndHeight;
	windowRect.right = wndWidth;

	// make sure the client size is has the appropriate area
	if (!AdjustWindowRect(&windowRect, windowStyle, false))
		AssertWindowsError();

	// create the window
	hWnd = CreateWindowEx(NULL, wndClassName, windowTitle, windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, HINST_THISCOMPONENT, this);
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
