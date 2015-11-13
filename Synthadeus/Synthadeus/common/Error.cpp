#include "Error.h"

// these [Error.h/cpp] are by far the most messy files (thanks to CPP commands)
// probably the worst place to grade for neatness Dr. Nash :(

// predefined for easy reading
#ifndef DEBUG_NO_LOG
#define __DebugPrintToLogFile__(str) fprintf(log, str)
#else
#define __DebugPrintToLogFile__(str)
#endif

// define the sizes of the file name and debug message string
#define DEBUG_BUFFER_SIZE 512
#define DEBUG_FNAME_SIZE 64

// a special assert to avoid infinite recursion (AKA a standard assert)
#define NO_MSG_assert(expression) (void)(                                                       \
            (!!(expression)) ||                                                              \
            (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \
        )

// if we are building from VS, output to its output console
#if defined(DEBUG) || defined(_DEBUG) // turn VS logging features

#define __DebugPrintToDebuggerArea__(str) OutputDebugString(str)

#else // turn off full debugging features

#define __DebugPrintToDebuggerArea__(str)

#endif // Debug logging functions

void DebugLogging::initDebugLogger()
{
	// open the log file if debug logging is enabled
#ifndef DEBUG_NO_LOG
	// determine the filename
	if (_strcmpi(debugFileName, "") == 0)
	{
		// make the log file "DEBUG_LOG_[date].log"
		SYSTEMTIME systemTime;
		GetSystemTime(&systemTime);
#if defined(DEBUG) || defined(_DEBUG)
		NO_MSG_assert(sprintf_s(debugFileName, DEBUG_FNAME_SIZE, "DEBUG_LOG_(%d-%d-%d_%d-%d-%d).log",
				systemTime.wMonth, systemTime.wDay, systemTime.wYear, systemTime.wHour, systemTime.wSecond, systemTime.wSecond) >= 0);
#else
		sprintf_s(debugFileName, DEBUG_BUFFER_SIZE, "DEBUG_LOG_(%d-%d-%d_%d-%d-%d).log",
			systemTime.wMonth, systemTime.wDay, systemTime.wYear, systemTime.wHour, systemTime.wSecond, systemTime.wSecond);
#endif
	}

	// open the log
#if defined(DEBUG) || defined(_DEBUG)
	NO_MSG_assert(fopen_s(&log, debugFileName, "a") == 0);
#else
	fopen_s(&log, debugFileName, "a");
#endif
#endif

	// establish the file is opened and module is initialized
	isInitialized = true;
}

void DebugLogging::dbgPrintf(const char* format, ...)
{
#ifndef DEBUG_NO_LOG
	// initiate the log (if not already done so)
	if (!isInitialized) initDebugLogger();

	// debug log text buffer
	char debugBuffer[DEBUG_BUFFER_SIZE];
	int result = 0;

	// construct the output string
	va_list args;
	va_start(args, format);
#if defined(DEBUG) || defined(_DEBUG)
	NO_MSG_assert(vsprintf_s(debugBuffer, format, args) >= 0);
#else
	vsprintf_s(debugBuffer, format, args);
#endif
	va_end(args);

	// write it to the correct areas
	__DebugPrintToDebuggerArea__(debugBuffer);
	__DebugPrintToLogFile__(debugBuffer);
#endif
}

void DebugLogging::finishDebugLogger()
{
#ifndef DEBUG_NO_LOG
	// return standard output to its normal location
#if defined(DEBUG) || defined(_DEBUG)
	NO_MSG_assert(fclose(log) == 0);
#else
	fclose(log);
#endif 
#endif

	// establish the module is uninitialized
	isInitialized = false;
}

void DebugLogging::dbgAssertWindowsError(const char* functionName)
{
	// determine the last error code
	DWORD code = GetLastError();
	if (code != 0) // error was not success
	{
		// log the error
		TCHAR buffer[256] = "Error Message.";
		char completeErrorMessage[1024];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, (sizeof(buffer) / sizeof(TCHAR)) - 1, NULL);
		sprintf_s(completeErrorMessage, 1024, "Windows API Error in %s(): %s [ERROR: %x]", functionName, buffer, code);
		DebugPrintf(completeErrorMessage);
		assert(!"Error with HRESULT, see logs.");
	}
}

void DebugLogging::dbgAssertWindowsHRESULT(const char* functionName, HRESULT hresult)
{
	// did the HRESULT indicate a failure?
	if (FAILED(hresult)) // error was not success
	{
		// log the error
		char completeErrorMessage[1024];
		sprintf_s(completeErrorMessage, 1024, "Windows API Error in %s(): code: %x", functionName, hresult);
		DebugPrintf("%s\n", completeErrorMessage);
		assert(!"Error with HRESULT, see logs.");	
	}
}

// macro cleanup 
#undef DEBUG_FILE_NAME
#undef DEBUG_BUFFER_SIZE
#undef __DebugPrintToDebuggerArea__
#undef __DebugPrintToLogFile__
#undef NO_MSG_assert
