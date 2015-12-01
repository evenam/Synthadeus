////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Silder Base Logic                                                        //
//   Everett Moser                                                            //
//   11-14-15                                                                 //
//                                                                            //
//   Contains logic relating to how a UX slider works                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

class SliderBase
{
public:

	// initialize a slider with a range, initial value and an increment size
	SliderBase(float minValue, float maxValue, float initialValue, float tickValue = 0.25f);

	// update the slider with a value change
	void update(float deltaValue);

	// update the slider with a new value
	void setValue(float newValue);

	// get the current value
	float getValue() { return currentValue; }

	// the slider minimum value
	float getMinValue() { return minimum; }

	// the slider minimum value
	float getMaxValue() { return maximum; }

private:

	// range
	const float minimum;
	const float maximum;

	// value
	float currentValue;

	// tick size
	const float tick;
};

