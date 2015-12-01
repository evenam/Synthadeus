////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Button UX component                                                      //
//   Everett Moser                                                            //
//   11-14-15                                                                 //
//                                                                            //
//   A button which can be rendered and receive mouse events.                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ButtonBase.h"
#include "Component.h"
#include "Renderables.h"

class Button : public Component
{
private:
	// simply to hold button logic
	ButtonBase logicUnit;

	// button size properties
	Point btnOrigin;
	Point btnSize;

	// button colors
	unsigned int btnBkgColor;
	unsigned int btnFgColor;

	// button text
	char* btnText;
	unsigned int btnFont;

	// pressed event callback
	ActionCallback callback;

	// are we hovering with the mouse?
	bool hover;

public:

	// runtime type information
	RTTI_MACRO(Button);

	// create a customized button
	Button(Point origin, Point size, unsigned int bkgColor, unsigned int fgColor, 
		char* text, unsigned int font, ActionCallback actionCallbackFunction = DEFAULT_ACTION_CALLBACK);

	// modify size
	void setSize(Point origin, Point size);

	// modify colors
	void setColorScheme(unsigned int bkgColor, unsigned int fgColor);

	// modify the text
	void setText(char* text, unsigned int font);

	// returns the render list for the button
	virtual Renderable* getRenderList();
	
	// the button update cycle
	virtual void update();

	// the mouse event handler when mouse is hovering or clicking
	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);
};

