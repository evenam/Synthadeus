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
	hWnd(NULL)
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
	
	// run initialization code
	assert(initialize());

	// create the window
	hWnd = CreateWindowEx(NULL, wndClassName, "Synthadaeus", windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, wndWidth, wndHeight, NULL, NULL, HINST_THISCOMPONENT, this);
	if (!hWnd)
		AssertWindowsError();

	// show window
	ShowWindow(hWnd, nCmdShow); //NEEDS TO NOT BE 0

							   // update the shown window
	if (!UpdateWindow(hWnd))
		AssertWindowsError();
	
	// successful initialization
	isInitialized = true;
}

//Closes window
Window::~Window()
{
	// post the quit message 
	PostQuitMessage(0);

	// sanity check
	assert(isInitialized);

	// run uninitialization code
	assert(uninitialize());

	// successful uninitialization
	isInitialized = false;
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
	// literally pass everything to the WndProc
	// TODO: accelerators
	MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
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
