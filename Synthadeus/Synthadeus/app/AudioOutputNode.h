////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   The Audio Playback Node                                                  //
//   Everett Moser                                                            //
//   11-26-15                                                                 //
//                                                                            //
//   A single node dedicated to holding the final audio buffer for playback   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Component.h"
#include "Node.h"
#include "Connector.h"
#include "Oscillator.h"

class AudioOutputNode : public Node
{
	//AudioNode* outputNode;
	InputConnector* input;
	Oscillator* testOscillator;
public:
	AudioOutputNode(Point audioOutputNodeOrigin);

	// extends to lerp from audio nodes
	AudioNode* getAudioNode();

	virtual Renderable* getRenderList();
};

