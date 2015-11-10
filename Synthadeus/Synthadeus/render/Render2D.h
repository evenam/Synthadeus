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

#define RENDER_INSTANCE_STACK_SIZE 8

#define RENDER_COLOR_PALETTE_SIZE 4

#define COLOR_CODE_WHITE 0xFFFFFF
#define COLOR_CODE_BLACK 0x000000
#define COLOR_CODE_RED	 0xFF0000
#define COLOR_CODE_BLUE	 0x0000FF

#define COLOR_WHITE 0
#define COLOR_BLACK 1
#define COLOR_RED	2
#define COLOR_BLUE	3

#define RENDER_FONT_PALETTE_SIZE 1

#define FONT_ARIAL20 0

#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include "Vector2D.h"

class Renderable;

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

	Vector2D instanceStack[RENDER_INSTANCE_STACK_SIZE];
	Point origin;
	int instanceStackSize;

public:
	Render2D(HWND hWnd);
	~Render2D();
	void render();
	void addToRenderList(Renderable* item);
	void clearList();

	Point getInstance();
	void instance(Point otherOrigin);
	void restore();
};

