////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Renderable Interface                                                     //
//   Everett Moser                                                            //
//   10-5-15                                                                  //
//                                                                            //
//   Interface for defining renderable items for the renderer                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Object.h"
#include <d2d1.h>
#include <d2d1helper.h>

#pragma comment(lib, "d2d1.lib")

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

class Renderable : public Object
{
public:
	RTTI_MACRO(Renderable);
	inline Renderable()
	{
		next = NULL;
		child = NULL;
	}

	inline ~Renderable()
	{
		if (child) delete child;
		if (next) delete next;
	}

	inline void renderList(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette)
	{
		render(renderTarget, colorPalette, fontPalette);
		if (child) child->renderList(renderTarget, colorPalette, fontPalette);
		if (next) next->renderList(renderTarget, colorPalette, fontPalette);
	}
	virtual void render(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette) = 0; // issue D2D commands

	// hooray C++11
	Renderable *next = NULL, *child = NULL;
};
