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
	SafeRelease(&renderTarget);
	SafeRelease(&sampleBrush1);
	//SafeRelease(&sampleBrush2);
}

void RenderThread::render()
{
	rendering = true;

	// update to window size;
	RECT clientSize;
	GetClientRect(hWnd, &clientSize);
	D2D1_SIZE_F renderSize = renderTarget->GetSize();
	D2D1_SIZE_F size = D2D1::SizeF(clientSize.right - clientSize.left, clientSize.bottom - clientSize.top);
	if (renderSize.height != size.height && renderSize.width != size.width)
	{
		renderTarget->Resize(D2D1::SizeU(clientSize.right - clientSize.left, clientSize.bottom - clientSize.top));
	}
	ValidateRect(hWnd, &clientSize);

	renderTarget->BeginDraw();

	//RECT r;
	//renderTarget->DrawRectangle()

	renderTarget->EndDraw();
	rendering = false;
}

void RenderThread::blockForRender()
{
	while (rendering);
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
