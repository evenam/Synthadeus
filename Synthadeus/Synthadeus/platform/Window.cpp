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
Window::Window(int inWidth, int inHeight)
{
	//close window if already open
	uninitialize();
	//Check for full screen eventually
	//requires compatibility and multiple full screen window checks
	//Give parameters to the window at creation
	//is this even c++? 
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Window::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = HINST_THISCOMPONENT;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = wndClassName;

	if (!RegisterClassEx(&wcex))
		AssertWindowsError();
		
	this->wndWidth = wndWidth;
	this->wndHeight = wndHeight;
	initialize();
}

//Closes window
Window::~Window()
{
	uninitialize();
}

//create window
void Window::initialize()
{
	hWnd = CreateWindowEx(NULL, wndClassName, "Synthadaeus", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, this->wndWidth, this->wndHeight, NULL, NULL, HINST_THISCOMPONENT, this);
	if(!hWnd)
		AssertWindowsError();
	ShowWindow(hWnd, 0); //NEEDS TO NOT BE 0
	if (!UpdateWindow(hWnd))
		AssertWindowsError();

	SetWindowLongPtr(hWnd, 0, (LONG_PTR*)this);
	//we don't have any behaviors right now so what does this even do?
	
	//once we have initialize, this resets all behavors/aspects to false/null
	//closes window, not application
	//BOOL WINAPI DestroyWindow(
  	//	_In_ HWND hWnd
	//);
}

//Event handler equivalent from JS
void Window::runMessageLoop() 
{
	MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HWND& Window::getWindowHandle()
{
	return hWnd;
}

//either processes messages or sends messages to be processed
void Window::handleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
	//switch for all msg 
	//is this where WndProc is? or is it in main? 
	/* from functionx.com
	* uints will be from http://ahkscript.org/docs/misc/SendMessageList.htm
	LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
    case WM_CREATE:
	break;
    case WM_SHOWWINDOW:
	break;
    case WM_ACTIVATE:
	break;
    case WM_PAINT:
	break;
    case WM_SIZE:
	break;
    case WM_DESTROY:
        PostQuitMessage(WM_QUIT);
        break;
    default:
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
    return 0;
}
	*/
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* wnd = (Window*)GetWindowLongPtr(hWnd, 0);
	wnd->handleMessage(msg);
}
