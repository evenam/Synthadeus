#include "Button.h"

Button::Button(Point origin, Point size, unsigned int bkgColor, unsigned int fgColor,
	char* text, unsigned int font, actionCallback actionCallbackFunction) : Component()
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
	callback = actionCallbackFunction;

	setBoundingRectangle(origin, size);
}

void Button::setSize(Point origin, Point size)
{
	btnOrigin[0] = origin[0];
	btnOrigin[1] = origin[1];
	btnSize[0] = size[0];
	btnSize[1] = size[1];
	setBoundingRectangle(origin, size);
}

void Button::setColorScheme(unsigned int bkgColor, unsigned int fgColor)
{
	btnBkgColor = bkgColor;
	btnFgColor = fgColor;
}

void Button::setText(char* text, unsigned int font)
{
	btnText = text;
	btnFont = font;
}

Renderable* Button::getRenderList()
{
	unsigned int realFG = btnFgColor, realBG = btnBkgColor;
	if (interacting)
	{
		realFG = btnBkgColor;
		realBG = btnFgColor;
	}
	Rectangle2* bounds = new Rectangle2(btnOrigin, btnSize, realFG, realBG);
	bounds->next = new Text(btnText, btnOrigin, btnSize, btnFont, COLOR_WHITE);
	return bounds;
}

void Button::update()
{
	logicUnit.update(interacting);
}

void Button::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
	if (vMouse->left.checkPressed())
		interacting = true;
	else if (vMouse->left.checkReleased())
	{
		if (interacting)
			callback(app, getParent());
		interacting = false;
	}
}
