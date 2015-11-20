#include "AudioNode.h"

int AudioNode::GCD(int A, int B)
{
	// euclidian algorithm
	int max = A;
	int min = B;
	if (A < B)
	{
		max = B;
		min = A;
	}

	// idiot test (just suppose the numbers are relatively prime)
	if (min * max == 0) return 1.f;

	int Q = max / min;
	int R = max % min;

	// iterations O(log(n))
	while (R != 0)
	{
		max = min;
		min = R;
		Q = max / min;
		R = max % min;
	}

	// this will have the GCD at this point: R(n-1)
	return min;
}

float AudioNode::lerpValueL(float t)
{
	// calculate the decimal on t
	float fModSize = 1.f;
	float deltaT = modff(t, &fModSize);

	// calculate upper and lower samples
	int lowerSample = (int)t % bufferSize;
	int upperSample = (int)(t + 1) % bufferSize;

	// calculate the lerp
	float deltaB = bufferL[upperSample] - bufferL[lowerSample];
	return bufferL[lowerSample] + deltaB * deltaT;
}

float AudioNode::lerpValueR(float t)
{
	// calculate the decimal on t
	float fModSize = 1.f;
	float deltaT = modff(t, &fModSize);

	// calculate upper and lower samples
	int lowerSample = (int)t % bufferSize;
	int upperSample = (int)(t + 1) % bufferSize;

	// calculate the lerp
	float deltaB = bufferR[upperSample] - bufferR[lowerSample];
	return bufferR[lowerSample] + deltaB * deltaT;
}