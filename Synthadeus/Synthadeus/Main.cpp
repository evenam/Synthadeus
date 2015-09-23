#include <Windows.h>
#include "Error.h"

//do we need to add a windowParam to these parameters?  - hunter
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpwCmdLine, int nCmdShow)
{
	//Should we register window class here or in initialize? - hunter
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = Window::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = sizeof(LONG_PTR);
        wcex.hInstance = THIS_HINSTANCE;
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = wndClassName;

	DWORD retCode = 0;//what is this? - hunter
	retCode = RegisterClassEx(wecx);//registering but idk what registering is - hunter
	if (retCode == 0) //throws error if it is not registered - hunter
		AssertWindowsError();

	//assumes constructor will assign default values for width/height - hunter
	//assigning the created window to the window handler - hunter
	hWnd = Window(); //should this be hWnd = Window.getWindowHandle? - hunter
	if(hWnd == NULL)
    {
    	AssertWindowsError();
        /* from winprog.org, but we throw assert instead - hunter
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;*/
    }
    //window is registered, handler not null, so show and update window - hunter
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    //window is functioning, add loop
    hWnd.runMessageLoop();
    //msg sent in Main to Window class to be handled, right? - hunter
    //LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> go to Window.handleMessage;?

	DebugLogging::initDebugLogger();
	DebugPrintf("Testing logging....\n");
	if (!MessageBox(NULL, "Hello, world!", "Synthadeus", MB_OK))
		AssertWindowsError();
	DebugLogging::finishDebugLogger();
	return 0;
}