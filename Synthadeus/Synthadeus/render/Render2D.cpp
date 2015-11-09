#include "Render2D.h"

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

Render2D::Render2D(HWND wnd)
{
	hWnd = wnd;
	renderList = NULL;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&dwFactory));
	createDeviceDependentResources();
	createDeviceFontResources();
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
	if (renderSize.height != size.height && renderSize.width != size.width)
		renderTarget->Resize(D2D1::SizeU(clientSize.right - clientSize.left, clientSize.bottom - clientSize.top));
	ValidateRect(hWnd, &clientSize);

	renderTarget->BeginDraw();

	if (renderList)
		renderList->renderList(renderTarget, colorPalette, fontPalette);

	renderTarget->EndDraw();
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
