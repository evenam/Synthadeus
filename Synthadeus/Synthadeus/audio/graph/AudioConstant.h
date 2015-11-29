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
	float value;

public:
	RTTI_MACRO(AudioConstant);
	AudioConstant(float val = 440.f);
	void setValue(float val);
	virtual void recalculate();
};

