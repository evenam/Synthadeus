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
	// command buttons to issue commands
	Button *btnMakeOscillator, *btnMakeEnvelope, *btnMakeConstant, *btnMakeMultiplier, *btnMakeSummation;

	// menu origin and size
	Point origin;
	const Point size;

	// determine if the user clicked elsewhere?
	bool needsClosing;

public:
	// run time type information
	RTTI_MACRO(CommandMenu);

	// creating the menu at a specific point
	CommandMenu(Point cmOrigin);

	// menu command callback for making an oscillator
	static void createOscillator(Synthadeus* app, Component* other);

	// menu command callback for making an envelope
	static void createEnvelope(Synthadeus* app, Component* other);

	// menu command callback for making an consant
	static void createConstant(Synthadeus* app, Component* other);

	// menu command callback for making an multiplier
	static void createMultiplier(Synthadeus* app, Component* other);

	// menu command callback for making an summation
	static void createSummation(Synthadeus* app, Component* other);

	// generate the menu renderables list
	virtual Renderable* getRenderList();
};

