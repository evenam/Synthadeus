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
	SliderBase(float minValue, float maxValue, float initialValue, float tickValue = 0.25f);
	void update(float deltaValue);
	void setValue(float newValue);
	float getValue() { return currentValue; }
	float getMinValue() { return minimum; }
	float getMaxValue() { return maximum; }

private:
	const float minimum;
	const float maximum;
	float currentValue;
	const float tick;
};

