////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   The Render Thread                                                        //
//   Everett Moser                                                            //
//   9-22-15                                                                  //
//                                                                            //
//   Responsible for actually rendering data (Direct2D calls and all)         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Thread.h"
#include "Semaphore.h"
//#include "RenderTree.h"
#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <atomic>

#include "BezierCurve.h"

#pragma comment(lib, "d2d1.lib")

#define RENDER_COLOR_PALETTE_SIZE 4

// safe release is handy for removing unwanted resources
template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
	)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

// structure to pass renderable list to the thread
struct RenderThreadShared
{
	Renderable* list;
};

// render thread with direct2d specific stuff
class RenderThread : public Thread
{
private:
	ID2D1Factory* d2dFactory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* colorPalette[RENDER_COLOR_PALETTE_SIZE];
	HWND hWnd;
	std::atomic<bool> rendering;

	void createDeviceDependentResources();
	void removeDeviceDependentResources();

public:
	RTTI_MACRO(RenderThread);

	RenderThread(ID2D1Factory* factory, HWND hWnd);
	~RenderThread();

	virtual void run();

	void render();
	void blockForRender();

	std::atomic<bool> ready;
};

