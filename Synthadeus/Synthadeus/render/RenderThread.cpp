#include "RenderThread.h"

void RenderThread::run()
{
	while (!stopFlag)
	{
		DebugPrintf("%s\n", "RenderThreadLoop...");
	}
}
