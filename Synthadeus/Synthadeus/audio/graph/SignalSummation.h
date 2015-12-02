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
	// the maximum signals potentially combined in this way
	const static int MAX_SIGNALS = 8;

	// the input signals to combine
	AudioNode* signals[MAX_SIGNALS];

	// total number of combined signals
	int numSignals;

	// calculate the size of the buffers
	int calculatePhase();

	void calculateBuffer();

public:

	// run time type information
	RTTI_MACRO(SignalSummation);

	// create the summation with a potential list of input signals
	SignalSummation(int signalCount = 0, AudioNode** theSignals = NULL);

	// add a new signal to the summation
	void addChild(AudioNode* signal);

	// remove a signal from the summation by pointer
	void removeChild(AudioNode* signal);

	// remove a signal from the summation by index
	void removeChild(int signalIndex);

	// clear out all signals from the summation
	void clearChildren();

	// get the index of a signal in the summation
	int getSignalIndex(AudioNode* signal);

	// get the signal at the specified index in the summation
	AudioNode* getSignal(int signalIndex);

	// recalculate the buffers with the summed signals
	virtual void recalculate();
};