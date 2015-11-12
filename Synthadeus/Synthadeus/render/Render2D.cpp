#include "Render2D.h"
#include "Renderable.h"

void Render2D::createDeviceDependentResources()
{
	// revalidate the render target and related resources if needed
	HRESULT result = S_OK;
	if (!renderTarget)
	{
		// query client area
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		// create render target
		AssertWindowsHRESULT(factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &renderTarget));

		// create brushes, definitions in the palette.h
		AssertWindowsHRESULT(createBrush(COLOR_WHITE, COLOR_CODE_WHITE, 1.0));
		AssertWindowsHRESULT(createBrush(COLOR_BLACK, COLOR_CODE_BLACK, 1.0));
		AssertWindowsHRESULT(createBrush(COLOR_BLUE , COLOR_CODE_BLUE , 1.0));
		AssertWindowsHRESULT(createBrush(COLOR_RED  , COLOR_CODE_RED  , 1.0));

		// create fonts, definitions in pallet.h
		AssertWindowsHRESULT(createFont(FONT_ARIAL20, L"Arial", 20.f, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
		AssertWindowsHRESULT(createFont(FONT_ARIAL40, L"Arial", 40.f, DWRITE_FONT_WEIGHT_BOLD, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
		AssertWindowsHRESULT(createFont(FONT_ARIAL11, L"Arial", 10.f, DWRITE_FONT_WEIGHT_LIGHT, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	}
}

HRESULT Render2D::createFont(int font, CONST WCHAR* name, float size, DWRITE_FONT_WEIGHT weight, DWRITE_TEXT_ALIGNMENT hAlign, DWRITE_PARAGRAPH_ALIGNMENT vAlign)
{
	// create the font
	HRESULT hr = dwFactory->CreateTextFormat(name, NULL, weight, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", &fontPalette[font]);
	
	// set text horizontal align
	if (SUCCEEDED(hr))
	{
		hr = fontPalette[font]->SetTextAlignment(hAlign);
	}

	// set text vertical align
	if (SUCCEEDED(hr))
	{
		hr = fontPalette[font]->SetParagraphAlignment(vAlign);
	}

	// return the error code (succeeds on S_OK)
	return hr;
}

HRESULT Render2D::createBrush(int color, unsigned int colorCode, float alpha)
{
	// return the errror code from creating the brush (succeeds on S_OK)
	return renderTarget->CreateSolidColorBrush(D2D1::ColorF(colorCode, alpha), &colorPalette[color]);;
}

void Render2D::removeDeviceDependentResources()
{
	// release the render target
	SafeRelease(&renderTarget);

	// release brush resources
	for (int i = 0; i < RENDER_COLOR_PALETTE_SIZE; i++)
		SafeRelease(&colorPalette[i]);

	// release the font resources
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

Vector2D Render2D::applyViewportTransform(Vector2D p)
{
	return Vector2D();
}

float Render2D::applyViewportTransform(float f)
{
	return 0.0f;
}

Render2D::Render2D(HWND wnd)
{
	// grab the window handle and clear the renderlist
	hWnd = wnd;
	renderList = NULL;

	// create the factories
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&dwFactory));
	
	// create the resources from the factories
	createDeviceDependentResources();

	// initialize the instancing to start at (0.f, 0.f)
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
	// query window size
	RECT clientSize;
	GetClientRect(hWnd, &clientSize);

	// determine render size and client area size
	D2D1_SIZE_F renderSize = renderTarget->GetSize();
	D2D1_SIZE_F size = D2D1::SizeF(clientSize.right - clientSize.left, clientSize.bottom - clientSize.top);

	// update the render region to be equal to the client area size
	renderTarget->Resize(D2D1::SizeU(clientSize.right - clientSize.left, clientSize.bottom - clientSize.top));

	// assert we got back to the bottom of the instancing stack
	assert(instanceStackSize == 0);

	// begin the draw phase
	renderTarget->BeginDraw();

	// traverse and render the renderlist
	if (renderList)
		renderList->renderList(this, renderTarget, colorPalette, fontPalette);

	// end the draw phase
	HRESULT result = renderTarget->EndDraw();

	// if the render failed (target is invalid) recreate resources (as they will be invalid)
	if (FAILED(result))
	{
		removeDeviceDependentResources();
		createDeviceDependentResources();
	}

	// validate rendered region
	ValidateRect(hWnd, &clientSize);

	// assert we got back to the bottom of the instancing stack after rendering completes
	assert(instanceStackSize == 0);
}

void Render2D::addToRenderList(Renderable * item)
{
	// assign the list if it is empty
	if (!renderList)
		renderList = item;

	// else append the item to the list
	else
	{
		Renderable* current = renderList;

		// hooray O(n) for linked list traversal
		while (current->next)
			current = current->next;

		// the actual append
		current->next = item;
	}
}

void Render2D::clearList()
{
	// clear out the render list and free memory
	delete renderList;
	renderList = NULL;
}

Renderable * Render2D::getRenderList()
{
	return renderList;
}
