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
}

// modify properties
void Slider::setSize(Point origin, Point size)
{
	sliderOrigin[0] = origin[0];
	sliderOrigin[1] = origin[1];
	sliderSize[0] = size[0];
	sliderSize[0] = size[0];
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
	//if (orientation == VERTICAL)
	//{
	float tickY = sliderOrigin[1] + sliderSize[1] / 2.f;// +sliderLogicUnit.getValue() * (sliderSize[1] / 2.f);
	tickMarker = new Line(Point(sliderOrigin[0], tickY), Point(sliderOrigin[0] + sliderSize[0], tickY), sliderFgColor, 2.5f);
	//}
	boundingRectangle->next = tickMarker;
	return boundingRectangle;
}

void Slider::update()
{

}

void Slider::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{

}
