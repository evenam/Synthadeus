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
	// Connection to final graph node
	InputConnector* input;

	// A default value to feed the audio driver when not connected to another graph node
	AudioConstant* defaultValue;

	// the actual graph node whose data is fed to the audio playback mechanism
	AudioNode* outputNode;

public:

	// runtime type information macro
	RTTI_MACRO(AudioOutputNode);

	// a simple contructor creating the node at a target location
	AudioOutputNode(Point audioOutputNodeOrigin);

	// get the audio node related to this UI graph node
	virtual AudioNode* getAudioNode();

	// get the render list
	virtual Renderable* getRenderList();

	// free the default value node
	virtual inline void onDestroy() { delete defaultValue; }

	// on input connected callback
	static void onConnected(Synthadeus* app, Component* me);

	// updates the default node when the connection changes
	void setOutputNode(AudioUINode* node);
};

