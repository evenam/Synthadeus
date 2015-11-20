#pragma once
#include <cmath>

#define RADIAN_TABLE_SIZE 6283

class SineLookup
{
private:
	static float* sineLookup;

public:
	inline static void initialize()
	{
		sineLookup = new float[RADIAN_TABLE_SIZE];
		for (int i = 0; i < RADIAN_TABLE_SIZE; i++)
		{
			sineLookup[i] = sinf((float)i / 1000.f);
		}
	}

	inline static void deinitialize()
	{
		delete[] sineLookup;
	}

	inline static float sine(float radians)
	{
		if (sineLookup == NULL)
			initialize();
		int realRadians = (int)(radians * 1000);
		realRadians %= RADIAN_TABLE_SIZE;
		return sineLookup[realRadians];
	}
};

#define fast_sinf(x) (SineLookup::sine(x))
