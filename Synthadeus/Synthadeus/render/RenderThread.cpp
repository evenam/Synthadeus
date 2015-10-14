#include "RenderThread.h"

void RenderThread::createDeviceDependentResources()
{
	HRESULT result = S_OK;
	if (!renderTarget)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		d2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &renderTarget);
	
	}
}

void RenderThread::removeDeviceDependentResources()
{
	//SafeRelease(&renderTarget);
	//SafeRelease(&sampleBrush1);
	//SafeRelease(&sampleBrush2);
}

void RenderThread::render()
{
	renderTarget->BeginDraw();

	//RECT r;
	//renderTarget->DrawRectangle()

	renderTarget->EndDraw();
}

RenderThread::RenderThread(ID2D1Factory* factory, HWND wnd) : Thread(sizeof(RenderThreadShared))
{
	d2dFactory = factory;
	hWnd = wnd;
	createDeviceDependentResources();
}

RenderThread::~RenderThread()
{
	removeDeviceDependentResources();
}

void RenderThread::run()
{
	while (!stopFlag)
	{
		// Compute adjusted geometry
		render();
	}
}
