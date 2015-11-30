////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Signal Summation                                                         //
//   Everett Moser                                                            //
//   11-23-15                                                                 //
//                                                                            //
//   An audio graph node for combining multiple signals into a single signal  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AudioNode.h"

class SignalSummation : public AudioNode
{
	const static int MAX_SIGNALS = 8;
	AudioNode* signals[MAX_SIGNALS];
	int numSignals;

	int calculatePhase();

public:
	RTTI_MACRO(SignalSummation);
	SignalSummation(int signalCount = 0, AudioNode** theSignals = NULL);

	void addChild(AudioNode* signal);
	void removeChild(AudioNode* signal);
	void removeChild(int signalIndex);
	void clearChildren();

	int getSignalIndex(AudioNode* signal);
	AudioNode* getSignal(int signalIndex);

	virtual void recalculate();
};