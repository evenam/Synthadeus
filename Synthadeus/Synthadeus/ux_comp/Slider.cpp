#include "Slider.h"

Slider::Slider(Point origin, Point size, unsigned int bkgColor, unsigned int fgColor, Orientation orien) : sliderLogicUnit(-1.f, 1.f, 0.f)
{
	orientation = orien;
	sliderOrigin[0] = origin[0];
	sliderOrigin[1] = origin[1];
	sliderSize[0] = size[0];
	sliderSize[1] = size[1];
	sliderBkgColor = bkgColor;
	sliderFgColor = fgColor;
	setBoundingRectangle(sliderOrigin, sliderSize);
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
		tick = sliderOrigin[1] + sliderSize[1] / 2.f + sliderLogicUnit.getValue() * (sliderSize[1] / 2.f);
		tickMarker = new Line(Point(sliderOrigin[0], tick), Point(sliderOrigin[0] + sliderSize[0], tick), sliderFgColor, 4.5f);
	}
	else
	{
		// lerp
		tick = sliderOrigin[0] + sliderSize[0] / 2.f + sliderLogicUnit.getValue() * (sliderSize[0] / 2.f);
		tickMarker = new Line(Point(tick, sliderOrigin[1]), Point(tick, sliderOrigin[1] + sliderSize[1]), sliderFgColor, 4.5f);
	}
	boundingRectangle->next = tickMarker;

	if (interacting)
	{
		char stringBuffer[10];
		sprintf_s(stringBuffer, "%6.3f\0", sliderLogicUnit.getValue());
		Renderable* text = new Text(stringBuffer, Point((sliderSize[0] - 30.f) / 2.f, -18.f), Point(30.f, 15.f), FONT_ARIAL11, COLOR_WHITE);
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
		tick = 2.f * (vMouse->instancePosition()[0] - sliderOrigin[0]) / (sliderSize[0]) - 1.f;									 
	else										 
		tick = 2.f * (vMouse->instancePosition()[1] - sliderOrigin[1]) / (sliderSize[1]) - 1.f;

	if (!interacting && vMouse->left.checkPressed())
	{
		interacting = true;
		sliderLogicUnit.setValue(tick);
	}
	else if (interacting && vMouse->left.checkReleased())
	{
		interacting = false;
	}

	if (interacting && vMouse->left.check())
		sliderLogicUnit.setValue(tick);
}
