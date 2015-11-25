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

	// button properties
	Point btnOrigin;
	Point btnSize;
	unsigned int btnBkgColor;
	unsigned int btnFgColor;
	char* btnText;
	unsigned int btnFont;
	ActionCallback callback;
	bool hover;

public:
	RTTI_MACRO(Button);
	Button(Point origin, Point size, unsigned int bkgColor, unsigned int fgColor, 
		char* text, unsigned int font, ActionCallback actionCallbackFunction = DEFAULT_ACTION_CALLBACK);

	// modify properties
	void setSize(Point origin, Point size);
	void setColorScheme(unsigned int bkgColor, unsigned int fgColor);
	void setText(char* text, unsigned int font);

	// overrides from Component
	virtual Renderable* getRenderList();
	virtual void update();
	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);
};

