#include "CommandMenu.h"
#include "Synthadeus.h"

CommandMenu::CommandMenu(Point cmOrigin) :

	// create the button to make an oscillator
	btnMakeOscillator(new Button(Point(0.f, 0.f),
		Point(120.f, 40.f), COLOR_DKGREY, COLOR_LTGREY, "Oscillator", FONT_ARIAL20, CommandMenu::createOscillator)),

	// create the button to make an envelope
	btnMakeEnvelope(new Button(Point(0.f, 40.f),
		Point(120.f, 40.f), COLOR_DKGREY, COLOR_LTGREY, "Envelope", FONT_ARIAL20, CommandMenu::createEnvelope)),

	// create the button to make an constant
	btnMakeConstant(new Button(Point(0.f, 80.f),
		Point(120.f, 40.f), COLOR_DKGREY, COLOR_LTGREY, "Constant", FONT_ARIAL20, CommandMenu::createConstant)),

	// create the button to make an multiplier
	btnMakeMultiplier(new Button(Point(0.f, 120.f),
		Point(120.f, 40.f), COLOR_DKGREY, COLOR_LTGREY, "Mutliplier", FONT_ARIAL20, CommandMenu::createMultiplier)),

	// create the button to make an summation
	btnMakeSummation(new Button(Point(0.f, 160.f),
		Point(120.f, 40.f), COLOR_DKGREY, COLOR_LTGREY, "Summation", FONT_ARIAL20, CommandMenu::createSummation)),

	// set our size
	size(Point(120.f, 200.f))
{
	// update our origin and set the bounding rectangle
	origin[0] = cmOrigin[0];
	origin[1] = cmOrigin[1];
	setBoundingRectangle(origin, size);

	// assert all buttons have been added to the subcomponent list successfully
	assert(addChild(btnMakeOscillator) > -1);
	assert(addChild(btnMakeEnvelope) > -1);
	assert(addChild(btnMakeConstant) > -1);
	assert(addChild(btnMakeMultiplier) > -1);
	assert(addChild(btnMakeSummation) > -1);

	// we should be open for a little while at least
	needsClosing = false;
}

void CommandMenu::createOscillator(Synthadeus* app, Component* other)
{
	DebugPrintf("Creating an Oscillator\n");

	// resolve the identity crisis
	assert(_strcmpi(other->getClassName(), CommandMenu::nameString()) == 0);
	CommandMenu* myself = (CommandMenu*)other;

	// remove myself and request the new node from the application
	myself->signalRemoval();
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
	app->createOscillatorNode();
}

void CommandMenu::createEnvelope(Synthadeus* app, Component* other)
{
	DebugPrintf("Creating an Envelope\n");

	// resolve the identity crisis
	assert(_strcmpi(other->getClassName(), CommandMenu::nameString()) == 0);
	CommandMenu* myself = (CommandMenu*)other;

	// remove myself and request the new node from the application
	myself->signalRemoval();
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
	app->createEnvelopeNode();
}

void CommandMenu::createConstant(Synthadeus* app, Component* other)
{
	DebugPrintf("Creating an Constant\n");

	// resolve the identity crisis
	assert(_strcmpi(other->getClassName(), CommandMenu::nameString()) == 0);
	CommandMenu* myself = (CommandMenu*)other;
	myself->signalRemoval();
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
	app->createConstantNode();
}

void CommandMenu::createMultiplier(Synthadeus* app, Component* other)
{
	DebugPrintf("Creating an Multiplier\n");
	assert(_strcmpi(other->getClassName(), CommandMenu::nameString()) == 0);
	CommandMenu* myself = (CommandMenu*)other;

	// remove myself and request the new node from the application
	myself->signalRemoval();
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
	app->createMultiplierNode();
}

void CommandMenu::createSummation(Synthadeus* app, Component* other)
{
	DebugPrintf("Creating an Summation\n");

	// resolve the identity crisis
	assert(_strcmpi(other->getClassName(), CommandMenu::nameString()) == 0);
	CommandMenu* myself = (CommandMenu*)other;

	// remove myself and request the new node from the application
	myself->signalRemoval();
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
	app->createSummationNode();
}

Renderable* CommandMenu::getRenderList()
{
	// just return a non renderable to append more things to later
	return new Rectangle2(origin, size, COLOR_NONE, COLOR_NONE);
}
