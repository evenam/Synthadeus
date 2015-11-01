#include "Render2D.h"

Render2D::Render2D(HWND hWnd)
{
	D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
	renderThread = new RenderThread(factory, hWnd);
}

Render2D::~Render2D()
{
	SafeRelease(&factory);
	delete renderThread;
}

void Render2D::beginRenderThread()
{
	Thread::start(renderThread);
}

void Render2D::endRenderThread()
{
	Thread::wait(renderThread);
}

void Render2D::sendRenderList(Renderable* item)
{
	while (!renderThread->ready);

	RenderThreadShared* shared = renderThread->getSharedMemory<RenderThreadShared>();
	if (shared->list)
		delete (shared->list);
	shared->list = item;
	renderThread->releaseSharedMemory();
}
