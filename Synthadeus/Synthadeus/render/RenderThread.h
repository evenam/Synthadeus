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

#include "../common/Thread.h"
#include "../common/Semaphore.h"
//#include "RenderTree.h"
#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <atomic>

#pragma comment(lib, "d2d1.lib")

#define RENDER_QUEUE_SIZE 4

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

struct RenderThreadShared
{
	//Semaphore queueSemaphore;
	//RenderTree* treeQueue[RENDER_QUEUE_SIZE];
	//int isQueueModified;
	int x = 0;
};

class RenderThread : public Thread
{
private:
	ID2D1Factory* d2dFactory;
	//ID2D1Brush* brushes[10];
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* sampleBrush1;
	//ID2D1SolidColorBrush* sampleBrush2;
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

	//enum { QueueModified = 1, QueueNotModified = 2 };
};

