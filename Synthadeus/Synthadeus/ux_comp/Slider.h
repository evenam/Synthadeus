////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Slider UX component                                                      //
//   Everett Moser                                                            //
//   11-15-15                                                                 //
//                                                                            //
//   A slider which can be rendered and receive mouse events.                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Component.h"
#include "Renderables.h"
#include "SliderBase.h"
#include "ButtonBase.h"

class Slider : public Component
{
public:
	enum Orientation { VERTICAL, HORIZONTAL };

private:
	SliderBase sliderLogicUnit;

	// slider properties
	Point sliderOrigin;
	Point sliderSize;
	unsigned int sliderBkgColor;
	unsigned int sliderFgColor;

	// vertical or horizontal slider?
	Orientation orientation;

	ActionCallback callback;

	const float maximumValue;
	const float minimumValue;
	const float totalValue;

	float normalizedLerpValue();

public:
	RTTI_MACRO(Slider);
	Slider(Point origin, Point size, unsigned int bkgColor, unsigned int fgColor, Orientation orien, 
		float minVal, float maxVal, float initVal, float tickVal, ActionCallback actionCallbackFunction = DEFAULT_ACTION_CALLBACK);

	// modify properties
	void setSize(Point origin, Point size);
	void setColorScheme(unsigned int bkgColor, unsigned int fgColor);

	// overrides from Component
	virtual Renderable* getRenderList();
	virtual void update();
	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);

	float getValue() { return sliderLogicUnit.getValue(); }
};

