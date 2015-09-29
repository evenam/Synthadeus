////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   The Render Thread                                                        //
//   Everett Moser                                                            //
//   9-22-15                                                                  //
//                                                                            //
//   Responsible for actually rendering data (Direct2D calls and all)         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Thread.h"
#include "Semaphore.h"
//#include "RenderTree.h"
#include <Windows.h>

#define RENDER_QUEUE_SIZE 4

struct RenderThreadShared
{
	Semaphore queueSemaphore;
	//RenderTree* treeQueue[RENDER_QUEUE_SIZE];
	int isQueueModified;
};

class RenderThread : public Thread
{

public:
	RTTI_MACRO(RenderThread);

	//RenderThread(/*HWND hWnd*/);
	//~RenderThread();
	inline RenderThread() : Thread(sizeof(RenderThreadShared)) {}

	virtual void run();

	enum { QueueModified = 1, QueueNotModified = 2 };
};

