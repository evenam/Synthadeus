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
#include "AudioConstant.h"

class AudioOutputNode : public Node, public AudioUINode
{
	//AudioNode* outputNode;
	InputConnector* input;
	AudioConstant* defaultValue;
public:
	AudioOutputNode(Point audioOutputNodeOrigin);

	// extends to lerp from audio nodes
	virtual AudioNode* getAudioNode();

	virtual Renderable* getRenderList();
	virtual inline void onDestroy() { delete defaultValue; }
};

