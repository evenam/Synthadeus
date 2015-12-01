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

	// enum for specifying orientation
	enum Orientation { VERTICAL, HORIZONTAL };

private:
	SliderBase sliderLogicUnit;

	// slider geometry
	Point sliderOrigin;
	Point sliderSize;

	// color scheme
	unsigned int sliderBkgColor;
	unsigned int sliderFgColor;

	// vertical or horizontal slider?
	Orientation orientation;

	// on changed callback
	ActionCallback callback;

	// slider range
	const float maximumValue;
	const float minimumValue;
	const float totalValue;

	// helps with rendering, the normalized slider position
	float normalizedLerpValue();

public:

	// run time type information
	RTTI_MACRO(Slider);

	// create a slider with all of the paremeters necessary to set up the values, positions, and the callback
	Slider(Point origin, Point size, unsigned int bkgColor, unsigned int fgColor, Orientation orien, 
		float minVal, float maxVal, float initVal, float tickVal, ActionCallback actionCallbackFunction = DEFAULT_ACTION_CALLBACK);

	// modify size
	void setSize(Point origin, Point size);

	// modify color scheme
	void setColorScheme(unsigned int bkgColor, unsigned int fgColor);

	// generate the renderables to make a slider
	virtual Renderable* getRenderList();

	// update the slider every frame
	virtual void update();

	// enables clicking and dragging to adjust value
	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);

	// get the current value of the slider
	float getValue() { return sliderLogicUnit.getValue(); }
};

