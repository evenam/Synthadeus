Synthadeus - A Digital Synthesizer in C++
Class project for CSC4330

Dependencies - Windows, DirectX
 More specifically, this app uses PortAudio, Direct2D, DirectWrite, and the Windows API. Subject to change. 

Description of Project Directories
* Common: files common to code segments
* Render: files involved with controlling Direct2D
* App: files involved with the main application logic
* Audio: files involved with controlling PortAudio
* Platform: files involved with handling the ugly Windows API
* UX_Comp: files related to creating GUI components

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
* Refractor, Refractor, Refractor!
* Overuse asserts, DebugPrintf, RTTI_MACRO, and inheriting from Object to help with error reporting
* Make sure to check for Windows error codes from functions that return RESULT
* Make sure to check for Windows error codes from functions that return NULL
* Handle as many errors as possible in release build (report the errors too!)
* Have fun! :D 