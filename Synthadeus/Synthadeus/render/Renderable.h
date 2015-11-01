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

#define COLOR_CODE_WHITE 0xFFFFFF
#define COLOR_CODE_BLACK 0x000000
#define COLOR_CODE_RED	 0xFF0000
#define COLOR_CODE_BLUE	 0x0000FF

#define COLOR_WHITE 0
#define COLOR_BLACK 1
#define COLOR_RED	2
#define COLOR_BLUE	3

class Renderable : public Object
{
public:
	RTTI_MACRO(Renderable);
	inline ~Renderable()
	{
		if (child) delete child;
		if (next) delete next;
	}

	inline void renderList(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette)
	{
		render(renderTarget, colorPalette);
		if (child) child->render(renderTarget, colorPalette);
		if (next) next->render(renderTarget, colorPalette);
	}
	virtual void render(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette) = 0; // issue D2D commands
	virtual bool inView(float viewLeft, float viewTop, float viewRight, float viewBottom) = 0; // are we inside rectangle?
	
	// collision check against two axis aligned rectangles
	static inline bool collisionCheckBoundingBox(float left1, float top1, float right1, float bottom1, 
												 float left2, float top2, float right2, float bottom2)
	{
		if (left1 > right2) return false;
		if (left2 > right1) return false;
		if (top1 < bottom2) return false;
		if (top2 > bottom1) return false;
		return false;
	}

	Renderable *next = NULL, *child = NULL;
};
