Synthadeus - A Digital Synthesizer in C++
Class project for CSC4330

Dependencies - Windows, DirectX, PortAudio, PortMidi
 More specifically, this app uses PortAudio, PortMidi, Direct2D, DirectWrite, and the Windows API. 
* Binary builds for PortAudio and PortMidi are provided. 
* Please install the DirectX SDK (https://www.microsoft.com/en-us/download/details.aspx?id=6812) if you do not already have the Direct2D or DirectWrite binaries. 

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

Building the Project
* The project is designed for Windows 7 SP1, Windows 8/8.1, and Windows 10. 
* The solution and project files are for Microsoft Visual Studio 2015 Community. (With the C++ tools installed.)
* To compile to project using the project files provided:
 1) Assert you have the appropriate system. 
 2) Assert you have Direct2D/DirectWrite binaries installed.
 3) Assert you have Microsoft Visual Studio 2015 Community installed.
 4) Assert you have the C++ tools installed for Microsoft Visual Studio 2015 Community. 
 4) Open the solution ('Synthadeus/Synthadeus.sln') in Microsoft Visual Studio 2015 Community. 
 5) Double check your the project properties, under VC++ Directories, that you have the following include directories listed:
  - $(ProjectDir)/app
  - $(ProjectDir)/audio
  - $(ProjectDir)/audio/external
  - $(ProjectDir)/audio/graph
  - $(ProjectDir)/render
  - $(ProjectDir)/render/geoms
  - $(ProjectDir)/platform
  - $(ProjectDir)/common
  - $(ProjectDir)/ux_comp
  - $(ProjectDir)/ux_comp/base
 6) Make sure the build target platform is x86 the configuration is Debug or Release. 
 7) Build the project with Crtl-Alt-F7.
* Once the project is built, press F5 to run it. 