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

// for the ID2D calls, we need direct2d
#pragma comment(lib, "d2d1.lib")

class Render2D;
class Renderable : public Object
{
public:
	RTTI_MACRO(Renderable);

	// initialize an empty item to insert into a list
	inline Renderable()
	{
		// nullify to reduce errors in release builds for uninitialized variables
		next = NULL;
		child = NULL;
	}

	// free the child and the next
	inline ~Renderable()
	{
		// delete the whole tree
		if (child) delete child;
		if (next) delete next;
	}

	// generate the renderable list from the object, then its child, then the next renderable, creating a new list
	inline void renderList(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette)
	{
		// render me in the current render setting
		render(render2d, renderTarget, colorPalette, fontPalette);
		
		// instance the rendering and render the child
		render2d->instance(getOrigin());
		if (child) 
			child->renderList(render2d, renderTarget, colorPalette, fontPalette);
		render2d->restore();

		// render the next item in the render list after restoring the rendering instance
		if (next) next->renderList(render2d, renderTarget, colorPalette, fontPalette);
	}

	// a function to actually call ID2D calls
	virtual void render(Render2D* render2d, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette) = 0; // issue D2D commands
	
	// abstract function to get the origin of the renderable
	virtual Point getOrigin() = 0;
	
	// hooray C++11! (except this is rather unnecessary)
	Renderable *next = NULL, *child = NULL;
};
