#pragma once
#include "AudioNode.h"

class AudioConstant : public AudioNode
{
private:
	float value;

public:
	AudioConstant(float val = 440.f);
	void setValue(float val);
	virtual void recalculate();
};

