#include "Render2D.h"
#include "Renderable.h"

void Render2D::createDeviceDependentResources()
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
		hr = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &renderTarget);

		// create brushes, definitions in Renderable
		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0xFFFFFF, 1.0f), &colorPalette[0]);
		}

		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0x000000, 1.0f), &colorPalette[1]);
		}

		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0xFF0000, 1.0f), &colorPalette[2]);
		}

		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0x0000FF, 1.0f), &colorPalette[3]);
		}

		if (FAILED(hr))
			AssertWindowsHRESULT(hr);
	}
}

void Render2D::createDeviceFontResources()
{
	HRESULT hr = S_OK;
	hr = dwFactory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20.f, L"en-us", &fontPalette[FONT_ARIAL20]);
	
	if (SUCCEEDED(hr))
	{
		hr = fontPalette[FONT_ARIAL20]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	}

	if (SUCCEEDED(hr))
	{
		hr = fontPalette[FONT_ARIAL20]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	
	if (FAILED(hr))
		AssertWindowsHRESULT(hr);
}

void Render2D::removeDeviceDependentResources()
{
	SafeRelease(&renderTarget);
	for (int i = 0; i < RENDER_COLOR_PALETTE_SIZE; i++)
		SafeRelease(&colorPalette[i]);
	for (int i = 0; i < RENDER_FONT_PALETTE_SIZE; i++)
		SafeRelease(&fontPalette[i]);
}

Point Render2D::getInstance()
{
	// cumulation of relative origins
	return origin;
}

void Render2D::instance(Point otherOrigin)
{
	// add it to the origin
	origin[0] += otherOrigin[0];
	origin[1] += otherOrigin[1];
	
	// push it onto the stack
	instanceStack[instanceStackSize][0] = otherOrigin[0];
	instanceStack[instanceStackSize][1] = otherOrigin[1];
	instanceStackSize++;
}

void Render2D::restore()
{
	// pop the origin off the stack
	instanceStackSize--;
	Point otherOrigin;
	otherOrigin[0] = instanceStack[instanceStackSize][0];
	otherOrigin[1] = instanceStack[instanceStackSize][1];

	// subtract it from the cumulative origin
	origin[0] -= otherOrigin[0];
	origin[1] -= otherOrigin[1];
}

Render2D::Render2D(HWND wnd)
{
	hWnd = wnd;
	renderList = NULL;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&dwFactory));
	createDeviceDependentResources();
	createDeviceFontResources();

	instanceStackSize = 0;
	origin[0] = 0.f;
	origin[1] = 0.f;
}

Render2D::~Render2D()
{
	SafeRelease(&factory);
}

void Render2D::render()
{
	// update to window size;
	RECT clientSize;
	GetClientRect(hWnd, &clientSize);
	D2D1_SIZE_F renderSize = renderTarget->GetSize();
	D2D1_SIZE_F size = D2D1::SizeF(clientSize.right - clientSize.left, clientSize.bottom - clientSize.top);
	renderTarget->Resize(D2D1::SizeU(clientSize.right - clientSize.left, clientSize.bottom - clientSize.top));

	assert(instanceStackSize == 0);
	renderTarget->BeginDraw();

	if (renderList)
		renderList->renderList(this, renderTarget, colorPalette, fontPalette);

	HRESULT result = renderTarget->EndDraw();
	if (FAILED(result))
	{
		removeDeviceDependentResources();
		createDeviceDependentResources();
	}

	ValidateRect(hWnd, &clientSize);
	assert(instanceStackSize == 0);
}

void Render2D::addToRenderList(Renderable * item)
{
	if (!renderList)
		renderList = item;
	else
	{
		Renderable* current = renderList;
		while (current->next)
			current = current->next;
		current->next = item;
	}
}

void Render2D::clearList()
{
	delete renderList;
	renderList = NULL;
}
