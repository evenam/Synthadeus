#include "Slider.h"

Slider::Slider(Point origin, Point size, unsigned int bkgColor, unsigned int fgColor, Orientation orien, float minVal, float maxVal, float initVal, float tickVal, ActionCallback actionCallbackFunction) 
	: sliderLogicUnit(minVal, maxVal, initVal, tickVal), minimumValue(minVal), maximumValue(maxVal), totalValue(maxVal - minVal)
{
	orientation = orien;
	sliderOrigin[0] = origin[0];
	sliderOrigin[1] = origin[1];
	sliderSize[0] = size[0];
	sliderSize[1] = size[1];
	sliderBkgColor = bkgColor;
	sliderFgColor = fgColor;
	setBoundingRectangle(sliderOrigin, sliderSize);

	callback = actionCallbackFunction;
}

float Slider::normalizedLerpValue()
{
	float normalizedValue = (sliderLogicUnit.getValue() - minimumValue) / totalValue;
	assert(normalizedValue >= 0.f);
	assert(normalizedValue <= 1.f);
	return normalizedValue * 2.f - 1.f;
}

// modify properties
void Slider::setSize(Point origin, Point size)
{
	sliderOrigin[0] = origin[0];
	sliderOrigin[1] = origin[1];
	sliderSize[0] = size[0];
	sliderSize[0] = size[0];
	setBoundingRectangle(sliderOrigin, sliderSize);
}

void Slider::setColorScheme(unsigned int bkgColor, unsigned int fgColor)
{
	sliderBkgColor = bkgColor;
	sliderFgColor = fgColor;
}

// overrides from Component
Renderable* Slider::getRenderList()
{
	unsigned int realFG, realBG;
	Rectangle2* boundingRectangle;
	Line* tickMarker;
	
	// bounding reectangle is always the same
	boundingRectangle = new Rectangle2(sliderOrigin, sliderSize, sliderFgColor, sliderBkgColor);
	float tick = 0.f;
	if (orientation == VERTICAL)
	{
		// lerp
		tick = sliderOrigin[1] + sliderSize[1] / 2.f + normalizedLerpValue() * (sliderSize[1] / 2.f);
		tickMarker = new Line(Point(sliderOrigin[0], tick), Point(sliderOrigin[0] + sliderSize[0], tick), sliderFgColor, 4.5f);
	}
	else
	{
		// lerp
		tick = sliderOrigin[0] + sliderSize[0] / 2.f + normalizedLerpValue() * (sliderSize[0] / 2.f);
		tickMarker = new Line(Point(tick, sliderOrigin[1]), Point(tick, sliderOrigin[1] + sliderSize[1]), sliderFgColor, 4.5f);
	}
	boundingRectangle->next = tickMarker;

	if (interacting)
	{
		char stringBuffer[15];
		sprintf_s(stringBuffer, "%.3f\0", sliderLogicUnit.getValue());
		Renderable* text = NULL;
		if (orientation == VERTICAL)
			text = new Text(stringBuffer, Point((sliderSize[0] - 50.f) / 2.f, -18.f), Point(50.f, 15.f), FONT_ARIAL11, COLOR_WHITE);
		else
			text = new Text(stringBuffer, Point(-25.f, -12.f), Point(50.f, 15.f), FONT_ARIAL11, COLOR_WHITE);
		tickMarker->child = text;
	}

	return boundingRectangle;
}

void Slider::update()
{

}

void Slider::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
	float tick = 0.f;
	if (orientation == HORIZONTAL)
		tick = (vMouse->instancePosition()[0] - sliderOrigin[0]) / (sliderSize[0]);									 
	else										 
		tick = (vMouse->instancePosition()[1] - sliderOrigin[1]) / (sliderSize[1]);

	if (!interacting && vMouse->left.checkPressed())
	{
		interacting = true;
		sliderLogicUnit.setValue(tick * totalValue + minimumValue);
	}
	else if (interacting && vMouse->left.checkReleased())
	{
		interacting = false;
		callback(app, this);
	}

	if (interacting && vMouse->left.check())
		sliderLogicUnit.setValue(tick * totalValue + minimumValue);
}
