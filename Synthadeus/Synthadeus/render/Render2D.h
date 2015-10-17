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

#pragma comment(lib, "d2d1.lib")

#include "RenderThread.h"

class Render2D
{
private:
	//float maxFPS;
	RenderThread* renderThread;
	ID2D1Factory* factory;

public:
	Render2D(HWND hWnd);
	~Render2D();

	void beginRenderThread();
	void endRenderThread();
	inline void forceRender() { renderThread->blockForRender();  renderThread->render(); };

	inline void addToRenderTree(/*Renderable* geometry*/) {};
	inline void removeFromRenderTree(/*Renderable* geometry*/) {};

	//void setMaxFPS();
	//float getFPS();
};

