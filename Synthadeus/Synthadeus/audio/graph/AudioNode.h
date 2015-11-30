////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Audio Node                                                               //
//   Everett Moser                                                            //
//   11-23-15                                                                 //
//                                                                            //
//   Base class for a node in the audio graph                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CFMaths.h"
#include "AudioPlaybackPosition.h"
#include "AudioDefines.h"
#include "Error.h"
#include "Object.h"

// returns the evaluated member function unless the object is null, then it returns the default
#define POTENTIAL_NULL(nullableObject, memberFunction, defaultValue) \
	(((nullableObject) != NULL)? \
		(nullableObject)->memberFunction : \
		(defaultValue))

class AudioNode : public AudioPlaybackPosition, public Object
{
protected:

	// some huge buffers to hold audio data
	float bufferL[AUDIO_BUFFER_SIZE];
	float bufferR[AUDIO_BUFFER_SIZE];

	// the size of the part of the buffer actaully in use
	int bufferSize;

	// this LCM calculation is done with this specific order of operations to avoid integer overflow (very common)
	static inline int LCM(int A, int B) { int maxA = A, maxB = B; if (maxA < 1) maxA = 1; if (maxB < 1) maxB = 1; return (maxA / GCD(A, B)) * maxB; }
	
	// via euclidian algorithm
	static int GCD(int A, int B);

public:

	// run time type information
	RTTI_MACRO(AudioNode);

	// construct the default, along with playback position
	inline AudioNode() : AudioPlaybackPosition() { }

	// get the buffer size
	inline int getBufferSize() { return bufferSize; }

	// get the left audio buffer
	inline float* getBufferL() { return bufferL; }

	// get the right audio buffer
	inline float* getBufferR() { return bufferR; }

	// get the left audio buffer value at position
	inline float getBufferValueL(int pos) 
	{ 
		if (bufferSize == 0) 
			return 0; 
		return bufferL[pos % bufferSize]; 
	}

	// get the right audio buffer value at position
	inline float getBufferValueR(int pos) 
	{ 
		if (bufferSize == 0) 
			return 0; 
		return bufferR[pos % bufferSize]; 
	}

	// get the next playback position value for the left audio buffer
	inline float getBufferAtPositionL() 
	{ 
		if (bufferSize == 0) 
			return 0; 

		// this modulus should never happen, but included for safety
		return bufferL[getPositionL() % bufferSize]; 
	}

	// get the next playback position value for the right audio buffer
	inline float getBufferAtPositionR() 
	{ 
		if (bufferSize == 0) 
			return 0;

		// this modulus should never happen, but included for safety
		return bufferR[getPositionR() % bufferSize]; 
	}

	// abstract recalculate pure to guarantee recalculatability
	virtual void recalculate() = 0;

	// linearly interpolate the sample at time t (t in terms of samples) for the left buffer
	float lerpValueL(float t);

	// linearly interpolate the sample at time t (t in terms of samples) for the right buffer
	float lerpValueR(float t);
};

// interface for the UI
class AudioUINode
{
public:
	
	// assert that we have access to the underlying audio node
	virtual AudioNode* getAudioNode() = 0;
};
