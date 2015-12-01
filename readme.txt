Synthadeus - A Digital Synthesizer in C++
Class project for CSC4330
https://github.com/evenam/Synthadeus

Synthadeus is a new kind of synthesizer. Using time-domain DSP approximation algorithms and allowing for variable input parameters, Synthadeus gives artist a very high degree of control over the sound creation process. The audio flow is composed of a directed acyclic dataflow graph. This will chain various oscillators, envelopes, etc. together to create a desired sound. 

Key fearures of Synthadeus include:
 * Highly parameterized audio graph nodes. 
 * Waveform file export. 
 * Realtime resampled playback.
 * MIDI controller support.
 * ASIO device support. 

Building the Project
* The latest version of the project source can be downloaded from https://github.com/evenam/Synthadeus. 
 - Alternatively, use 'git clone https://github.com/evenam/Synthadeus.git' to clone in your working directory. 
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
For a detailed view of the changes of the files over time, please refer to the GitHub page network graph for the project. (https://github.com/evenam/Synthadeus/network)

User Guide:
 Synthadeus has online documentation at http://everettmoser.me/synthesizer/. Use a QWERTY keyboard layout if no midi controller is present. 
 Overview of controls:
 * Synthadeus has the following viewport controls:
  1) Arrow keys move the view around the graph.
  2) The Enter key centers the view back to the default position.
 * Synthadeus support the following global commands:
  1) Right clicking on the default pane brings up the command menu.
  2) F5 exports the waveform to the user's desired location. 
  3) Escape quits Synthadeus.
 * Synthadeus graph nodes support the following manipulations:
  1) Left click and drag a graph node to move it.
  2) Right click a graph node to delete it. (NOTE: The audio endpoint node CANNOT be deleted.)
  3) Left click and drag connector dots to other connector dots to create connections between nodes. 
  4) Right click a connector to remove all connections with that connector. 
 * Playback within Synthadeus uses most of the remaining general alpha-numerical keys. It's intuitive with C5 as Q/M keys. 

Dependencies - Windows, DirectX, PortAudio, PortMidi
 More specifically, this app uses 
  1) PortAudio (http://www.portaudio.com/) 
  2) PortMidi (http://portmedia.sourceforge.net/portmidi/)
  3) Direct2D, DirectWrite, and the Windows API (https://msdn.microsoft.com/library)
* Binary builds for PortAudio (both with and without ASIO) and PortMidi are provided. 
* Please install the DirectX SDK (https://www.microsoft.com/en-us/download/details.aspx?id=6812) if you do not already have the Direct2D or DirectWrite binaries. 

Description of Project Directories
* Common: files common to various aspects or the catch-all category
* Render: files involved with controlling Direct2D
* App: files involved with the main application logic
* Audio: files involved with controlling PortAudio
* Platform: files involved with handling the Windows API
* UX_Comp: files related to creating GUI components

Style:
 Adhere as much as possible to the style. Refractor when possible to keep it consistent. 
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
* Use asserts, DebugPrintf, RTTI_MACRO, and inheriting from Object to help with error reporting
* Make sure to check for Windows error codes from functions that return RESULT
* Make sure to check for Windows error codes from functions that return NULL
* Handle as many errors as possible in release build (report the errors too!)
* Have fun! :D 
