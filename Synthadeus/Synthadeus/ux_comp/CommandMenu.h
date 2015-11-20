#pragma once

#include "Component.h"
#include "Button.h"

class CommandMenu : public Component
{
private:
	Button* btnMakeOscillator, btnMakeEnvelope, btnMakeConstant, btnMakeSummation;
public:
	RTTI_MACRO(CommandMenu);
	CommandMenu();

	inline virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse) {};
	inline virtual void update() {};
	inline virtual Renderable* getRenderList() { return NULL; };
};

