////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   A 2D Renderer                                                            //
//   Everett Moser                                                            //
//   10-7-15                                                                  //
//                                                                            //
//   The renderer for the program using Direct2D                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include "Renderable.h"

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

class Render2D
{
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* colorPalette[RENDER_COLOR_PALETTE_SIZE];
	HWND hWnd;

	IDWriteFactory* dwFactory;
	IDWriteTextFormat* fontPalette[RENDER_FONT_PALETTE_SIZE];

	void createDeviceDependentResources();
	void createDeviceFontResources();
	void removeDeviceDependentResources();
	Renderable* renderList;

public:
	Render2D(HWND hWnd);
	~Render2D();
	void render();
	void addToRenderList(Renderable* item);
	void clearList();
};

