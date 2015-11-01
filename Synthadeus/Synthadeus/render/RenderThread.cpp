#include "RenderThread.h"

void RenderThread::createDeviceDependentResources()
{
	// revalidate the render target and related resources if needed
	HRESULT result = S_OK;
	if (!renderTarget)
	{
		// result
		HRESULT hr;

		// query client area
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		// create render target
		hr = d2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &renderTarget);

		// create brushes, definitions in Renderable
		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0xFFFFFF), &colorPalette[0]);
		}

		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0x000000), &colorPalette[1]);
		}

		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0xFF0000), &colorPalette[2]);
		}

		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0x0000FF), &colorPalette[3]);
		}

		if (FAILED(hr))
			AssertWindowsError();
	}
}

void RenderThread::removeDeviceDependentResources()
{
	SafeRelease(&renderTarget);
	for (int i = 0; i < RENDER_COLOR_PALETTE_SIZE; i++)
		SafeRelease(&colorPalette[i]);
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

	RenderThreadShared* shared = getSharedMemory<RenderThreadShared>();
	if (shared->list)
		shared->list->renderList(renderTarget, colorPalette);
	releaseSharedMemory();

	renderTarget->EndDraw();
	rendering = false;
}

void RenderThread::blockForRender()
{
	while (rendering);
}

RenderThread::RenderThread(ID2D1Factory* factory, HWND wnd) : Thread(sizeof(RenderThreadShared)), ready(false)
{
	d2dFactory = factory;
	hWnd = wnd;
	createDeviceDependentResources();
	ready = true;
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
