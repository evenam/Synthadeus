////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   A Command Menu UX Component                                              //
//   Everett Moser                                                            //
//   11-25-15                                                                 //
//                                                                            //
//   The right click context menu for right-clicking on a gridbase            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Component.h"
#include "Button.h"

class CommandMenu : public Component
{
private:
	Button btnMakeOscillator, btnMakeEnvelope, btnMakeConstant, btnMakeSummation;
	Point origin;
	const Point size;
	bool needsClosing;
public:
	RTTI_MACRO(CommandMenu);
	CommandMenu(Point cmOrigin);
	static void createOscillator(Synthadeus* app, Component* other);
	static void createEnvelope(Synthadeus* app, Component* other);
	static void createConstant(Synthadeus* app, Component* other);
	static void createSummation(Synthadeus* app, Component* other);

	virtual void mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse);
	virtual void update();
	virtual Renderable* getRenderList();
};

