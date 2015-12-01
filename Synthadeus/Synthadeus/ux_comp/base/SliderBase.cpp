#include "SliderBase.h"

SliderBase::SliderBase(float minValue, float maxValue, float initialValue, float tickValue) : minimum(minValue), maximum(maxValue), currentValue(initialValue), tick(tickValue)
{
	// get the closest tick
	int ticks = initialValue / tickValue;

	// update the value to the value of the closest tick
	currentValue = ticks * tickValue;

	// restrict slider range
	if (currentValue < minimum) currentValue = minimum;
	if (currentValue > maximum) currentValue = maximum;
}

void SliderBase::update(float deltaValue)
{
	// add in delta value
	currentValue += deltaValue;

	// calculate nearest tick
	int ticks = currentValue / tick;

	// update value to the tick value
	currentValue = ticks * tick;

	// restrict by slider range
	if (currentValue < minimum) currentValue = minimum;
	if (currentValue > maximum) currentValue = maximum;
}

void SliderBase::setValue(float newValue)
{
	// update the value 
	currentValue = newValue;

	// calculate nearest tick
	int ticks = currentValue / tick;

	// update value to the tick value
	currentValue = ticks * tick;

	// restrict by slider range
	if (currentValue < minimum) currentValue = minimum;
	if (currentValue > maximum) currentValue = maximum;
}
