////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Audio Graph Constant Node                                                //
//   Everett Moser                                                            //
//   11-23-15                                                                 //
//                                                                            //
//   A constant audio buffer                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AudioNode.h"

class AudioConstant : public AudioNode
{
private:

	// the node's constant value
	float value;

public:

	// run time type information
	RTTI_MACRO(AudioConstant);

	// initialize the node with a value
	AudioConstant(float val = 440.f);

	// update the node's value
	void setValue(float val);

	// recalculate if we get a new value
	virtual void recalculate();
};

