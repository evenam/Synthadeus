#include "Button.h"

Button::Button(Point origin, Point size, unsigned int bkgColor, unsigned int fgColor,
	char* text, unsigned int font, ActionCallback actionCallbackFunction) : Component()
{
	// initialize all properties
	btnOrigin[0] = origin[0];
	btnOrigin[1] = origin[1];
	btnSize[0] = size[0];
	btnSize[1] = size[1];
	btnBkgColor = bkgColor;
	btnFgColor = fgColor;
	btnText = text;
	btnFont = font;

	// set the callback
	callback = actionCallbackFunction;
	hover = false;

	// update component size
	setBoundingRectangle(origin, size);
}

void Button::setSize(Point origin, Point size)
{
	// update component size
	btnOrigin[0] = origin[0];
	btnOrigin[1] = origin[1];
	btnSize[0] = size[0];
	btnSize[1] = size[1];
	setBoundingRectangle(origin, size);
}

void Button::setColorScheme(unsigned int bkgColor, unsigned int fgColor)
{
	// change the color scheme
	btnBkgColor = bkgColor;
	btnFgColor = fgColor;
}

void Button::setText(char* text, unsigned int font)
{
	// update the text and the font
	btnText = text;
	btnFont = font;
}

Renderable* Button::getRenderList()
{
	// change the color scheme depending on pressed state
	unsigned int realFG = btnFgColor, realBG = btnBkgColor;
	if (interacting)
	{
		realFG = btnBkgColor;
		realBG = btnFgColor;
	}

	// outside rectange
	Rectangle2* bounds = new Rectangle2(btnOrigin, btnSize, realFG, realBG);
	
	// brighten the text if hovering
	bounds->next = new Text(btnText, btnOrigin, btnSize, btnFont, !hover? COLOR_LTGREY : COLOR_WHITE);
	hover = false;

	// return the list
	return bounds;
}

void Button::update()
{
	// update the button state
	logicUnit.update(interacting);
}

void Button::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
	// toggle hovering
	hover = true;

	// interact when clicked
	if (vMouse->left.checkPressed())
		interacting = true;

	// apply a click if still in bounds
	else if (vMouse->left.checkReleased())
	{
		if (interacting)
			callback(app, getParent());
		interacting = false;
	}
}
