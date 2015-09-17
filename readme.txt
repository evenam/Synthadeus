Synthadeus - A Digital Synthesizer in C++
Class project for CSC4330

Dependencies - Windows, DirectX
 More specifically, this app uses Direct2D, DirectWrite, and the Windows API. Subject to change. 

Description of Header Files:
* Common
 - CFMaths.h: Low precision, quick floating point math functions. 
 - Error.h: The assert macro and debug logging for offensive programming. 
 - Mutex.h: Skeleton for the Mutex object wrapper.
 - Semaphore.h: Skeleton for the Semaphore object wrapper. 
 - Object.h: ARC Object base, RTTI macro, and other useful anti-leak debugging. 
* Render
* App
* Audio
* Platform
- Main.cpp: Just the WinMain definition. 

Style:
* Prefer stack allocation over heap
* Short circuit optimize ifs and whiles
* Put the { on a separate line
* Prefer // comments over /* c-style */
* Keep global namespace relatively clear
 - Don't use macros unless it gives a clear advantage
 - If you use a file-local macro, be sure to #undef it
 - Use static "file-global" constants to remove magic numbers
* Don't commit to origin-master (pull only)
* #pragma once header guard
* #pragma comment .lib files in as needed
* Do not alter the project config unless absolutely necessary
* Overuse asserts, DebugPrintf, RTTI_MACRO, and inheriting from Object
* Make sure to check for Windows error codes from functions that return RESULT
* Make sure to check for Windows error codes from functions that return NULL
* Have fun! :D 