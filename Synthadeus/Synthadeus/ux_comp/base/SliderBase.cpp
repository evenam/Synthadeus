#include "SliderBase.h"

SliderBase::SliderBase(float minValue, float maxValue, float initialValue, float tickValue) : minimum(minValue), maximum(maxValue), currentValue(initialValue), tick(tickValue)
{
	int ticks = initialValue / tickValue;
	currentValue = ticks * tickValue;
	if (currentValue < minimum) currentValue = minimum;
	if (currentValue > maximum) currentValue = maximum;
}

void SliderBase::update(float deltaValue)
{
	currentValue += deltaValue;
	int ticks = currentValue / tick;
	currentValue = ticks * tick;
	if (currentValue < minimum) currentValue = minimum;
	if (currentValue > maximum) currentValue = maximum;
}

void SliderBase::setValue(float newValue)
{
	currentValue = newValue;
	int ticks = currentValue / tick;
	currentValue = ticks * tick;
	if (currentValue < minimum) currentValue = minimum;
	if (currentValue > maximum) currentValue = maximum;
}
