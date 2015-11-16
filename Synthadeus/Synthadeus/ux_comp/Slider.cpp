#include "Slider.h"

Slider::Slider(Point origin, Point size, unsigned int bkgColor, unsigned int fgColor, Orientation orien) : sliderLogicUnit(-1.f, 1.f, 0.f)
{
}

// modify properties
void Slider::setSize(Point origin, Point size)
{

}

void Slider::setColorScheme(unsigned int bkgColor, unsigned int fgColor)
{

}

// overrides from Component
Renderable* Slider::getRenderList()
{
	unsigned int realFG, realBG;
	Rectangle2* boundingRectangle;
	Rectangle2* tickMarker;
	
	// bounding reectangle is always the same
	boundingRectangle = new Rectangle2(sliderOrigin, sliderSize, sliderFgColor, sliderBkgColor);
	return boundingRectangle;
}

void Slider::update()
{

}

void Slider::mouseEventHandler(Synthadeus* app, Point mousePosition, bool check, bool pressed, bool released)
{

}
