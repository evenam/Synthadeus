////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   The Oscillator Node                                                      //
//   Everett Moser                                                            //
//   11-26-15                                                                 //
//                                                                            //
//   A placeable node which creates an oscillator in the audio graph          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Component.h"
#include "Node.h"

class OscillatorNode // : public Node
{
public:
	OscillatorNode();

	// callbacks for various functionality
	ActionCallback onConnected(Synthadeus* app, Component* me);
	ActionCallback onFrequencyChanged(Synthadeus* app, Component* me);
	ActionCallback onVolumeChanged(Synthadeus* app, Component* me);
	ActionCallback onPanningChanged(Synthadeus* app, Component* me);
	ActionCallback onSineClick(Synthadeus* app, Component* me);
	ActionCallback onSawClick(Synthadeus* app, Component* me);
	ActionCallback onSquareClick(Synthadeus* app, Component* me);
};

