#include <Windows.h>
#include "Error.h"

//do we need to add a windowParam to these parameters?  - hunter
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpwCmdLine, int nCmdShow)
{
	//Should we register window class here? - hunter
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

	//assumes constructor will assign default values - hunter
	//assigning the created window to the window handler - hunter
	hWnd = Window();

	DebugLogging::initDebugLogger();
	DebugPrintf("Testing logging....\n");
	if (!MessageBox(NULL, "Hello, world!", "Synthadeus", MB_OK))
		AssertWindowsError();
	DebugLogging::finishDebugLogger();
	return 0;
}