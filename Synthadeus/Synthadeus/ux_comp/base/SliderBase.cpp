#include "SliderBase.h"

SliderBase::SliderBase(float minValue, float maxValue, float initialValue) : minimum(minValue), maximum(maxValue), currentValue(initialValue)
{
	if (currentValue < minimum) currentValue = minimum;
	if (currentValue > maximum) currentValue = maximum;
}

void SliderBase::update(float deltaValue)
{
	currentValue += deltaValue;
	if (currentValue < minimum) currentValue = minimum;
	if (currentValue > maximum) currentValue = maximum;
}

void SliderBase::setValue(float newValue)
{
	currentValue = newValue;
	if (currentValue < minimum) currentValue = minimum;
	if (currentValue > maximum) currentValue = maximum;
}
