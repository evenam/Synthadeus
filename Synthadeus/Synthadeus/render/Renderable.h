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
#include "Vector2D.h"
#include "Render2D.h"
#include <d2d1.h>
#include <d2d1helper.h>

#pragma comment(lib, "d2d1.lib")

class Render2D;
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

	inline void renderList(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette)
	{
		render(render2d, renderTarget, colorPalette, fontPalette);
		render2d->instance(getOrigin());
		if (child) child->renderList(render2d, renderTarget, colorPalette, fontPalette);
		if (next) next->renderList(render2d, renderTarget, colorPalette, fontPalette);
		render2d->restore();
	}
	virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette) = 0; // issue D2D commands
	virtual Point getOrigin() = 0;
	// hooray C++11
	Renderable *next = NULL, *child = NULL;
};
