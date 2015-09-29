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
	isInitialized(false)
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
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = wndClassName;
	wcex.hIcon = LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(HINST_THISCOMPONENT, IDC_ARROW);

	// register the class
	if (!RegisterClassEx(&wcex))
		AssertWindowsError();
	
	// create the window
	hWnd = CreateWindowEx(NULL, wndClassName, "Synthadaeus", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wndWidth, wndHeight, NULL, NULL, HINST_THISCOMPONENT, this);
	if (!hWnd)
		AssertWindowsError();

	// show window
	ShowWindow(hWnd, nCmdShow); //NEEDS TO NOT BE 0

							   // update the shown window
	if (!UpdateWindow(hWnd))
		AssertWindowsError();

	// run initialization code
	assert(initialize());
	
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

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* wnd = NULL;
	if (msg == WM_CREATE)
	{
		// retrieve window pointer passed in lParam
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		wnd = (Window *)pcs->lpCreateParams;
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, PtrToLong(wnd)))
			AssertWindowsError(); 
	}

	// grab a previously set window if this isn't create
	if (!wnd)
		wnd = reinterpret_cast<Window*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
	if (!wnd)
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
