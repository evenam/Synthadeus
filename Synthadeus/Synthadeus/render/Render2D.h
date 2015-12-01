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

// windows is fat, so we go to the gym before we release it
#if !defined(DEBUG) && !defined(_DEBUG)
#define WIN32_LEAN_AND_MEAN
#endif

// windows/directx specific headers
#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

// link in the appropriate binaries for the API calls
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include "Vector2D.h"
#include "Palettes.h"

class Renderable;

// increase as necessary. small value to start with. max number of times we can instance rendering
#define RENDER_INSTANCE_STACK_SIZE 8

// safe release is handy for removing unwanted resources and nullifying the pointer
template <class Interface> inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	// release if and only if not invalid
	if (*ppInterfaceToRelease != NULL)
	{
		// release and nulify
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

class Render2D
{
private:
	// D2D and Dwrite factory instances for making Directx resources
	ID2D1Factory* factory;
	IDWriteFactory* dwFactory;

	// the canvas on which we paint our GUI
	HWND hWnd;
	ID2D1HwndRenderTarget* renderTarget;

	// palettes of resources (see Palette.h)
	ID2D1SolidColorBrush* colorPalette[RENDER_COLOR_PALETTE_SIZE];
	IDWriteTextFormat* fontPalette[RENDER_FONT_PALETTE_SIZE];

	// handle the dynamic creation of resources as they are created and invalidated
	void createDeviceDependentResources();

	// remove all of the resources we are using
	void removeDeviceDependentResources();

	// routine to simplify font creation
	HRESULT createFont(int font, CONST WCHAR* name, float size, DWRITE_FONT_WEIGHT weight, DWRITE_TEXT_ALIGNMENT hAlign, DWRITE_PARAGRAPH_ALIGNMENT vAlign);
	
	// routine to simplify brush creation
	HRESULT createBrush(int color, unsigned int colorCode, float alpha);

	// list of renderables which need drawing
	Renderable* renderList;

	// instancing stack for relative drawing positions
	Vector2D instanceStack[RENDER_INSTANCE_STACK_SIZE];
	Point origin;
	int instanceStackSize;

	// viewport data
	Vector2D viewportOrigin;
	float viewportZoom;

public:
	// create the render area with this window handle
	Render2D(HWND hWnd);

	// free the resources we used
	~Render2D();

	// render the current list
	void render();

	// add another item to the list
	void addToRenderList(Renderable* item);

	// remove an item from the list
	void clearList();

	// generate the render list to actaully draw
	Renderable* getRenderList();

	// get the current origin
	Point getInstance();

	// move the coordinate system
	void instance(Point otherOrigin);

	// restore the coordinate system
	void restore();

	// apply viewport transform to 1D and 2D vectors
	// these are undefined as of now, TODO: implement and propigate to renderables
	Vector2D applyViewportTransform(Vector2D p);
	float applyViewportTransform(float f);

	// get the current viewport location
	Point getViewportInstance();

	// modify the viewport zoom
	void viewportApplyZoom(float relativeZoom);

	// modify viewport translation
	void viewportApplyTranslation(Point relativeTranslation);

	// reset viewport to the default
	void viewportSetDefault();
};

