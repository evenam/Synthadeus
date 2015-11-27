#include "CommandMenu.h"
#include "Synthadeus.h"

CommandMenu::CommandMenu(Point cmOrigin) :
	btnMakeOscillator(new Button(Point(0.f, 0.f),
		Point(120.f, 40.f), COLOR_DKGREY, COLOR_LTGREY, "Oscillator", FONT_ARIAL20, CommandMenu::createOscillator)),
	btnMakeEnvelope(new Button(Point(0.f, 40.f),
		Point(120.f, 40.f), COLOR_DKGREY, COLOR_LTGREY, "Envelope", FONT_ARIAL20, CommandMenu::createEnvelope)),
	btnMakeConstant(new Button(Point(0.f, 80.f),
		Point(120.f, 40.f), COLOR_DKGREY, COLOR_LTGREY, "Constant", FONT_ARIAL20, CommandMenu::createConstant)),
	btnMakeSummation(new Button(Point(0.f, 120.f),
		Point(120.f, 40.f), COLOR_DKGREY, COLOR_LTGREY, "Summation", FONT_ARIAL20, CommandMenu::createSummation)),
	size(Point(120.f, 160.f))
{
	origin[0] = cmOrigin[0];
	origin[1] = cmOrigin[1];
	setBoundingRectangle(origin, size);

	assert(addChild(btnMakeOscillator) > -1);
	assert(addChild(btnMakeEnvelope) > -1);
	assert(addChild(btnMakeConstant) > -1);
	assert(addChild(btnMakeSummation) > -1);
	needsClosing = false;
}

void CommandMenu::createOscillator(Synthadeus* app, Component* other)
{
	//app->createOscillator();
	DebugPrintf("Creating an Oscillator\n");
	assert(_strcmpi(other->getClassName(), CommandMenu::nameString()) == 0);
	CommandMenu* myself = (CommandMenu*)other;
	myself->signalRemoval();
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
	app->createOscillatorNode();
}

void CommandMenu::createEnvelope(Synthadeus* app, Component* other)
{
	//app->createOscillator();
	DebugPrintf("Creating an Envelope\n");
	assert(_strcmpi(other->getClassName(), CommandMenu::nameString()) == 0);
	CommandMenu* myself = (CommandMenu*)other;
	myself->signalRemoval();
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
}

void CommandMenu::createConstant(Synthadeus* app, Component* other)
{
	//app->createOscillator();
	DebugPrintf("Creating an Constant\n");
	assert(_strcmpi(other->getClassName(), CommandMenu::nameString()) == 0);
	CommandMenu* myself = (CommandMenu*)other;
	myself->signalRemoval();
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
}

void CommandMenu::createSummation(Synthadeus* app, Component* other)
{
	//app->createOscillator();
	DebugPrintf("Creating an Summation\n");
	assert(_strcmpi(other->getClassName(), CommandMenu::nameString()) == 0);
	CommandMenu* myself = (CommandMenu*)other;
	myself->signalRemoval();
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
}

void CommandMenu::mouseEventHandler(Synthadeus* app, InputDevice::Mouse* vMouse)
{
}

void CommandMenu::update()
{
}

Renderable* CommandMenu::getRenderList()
{
	Renderable* bounds = new Rectangle2(origin, size, COLOR_NONE, COLOR_NONE);
	Renderable* osc = btnMakeOscillator->getRenderTree();
	Renderable* env = btnMakeEnvelope->getRenderTree();
	Renderable* con = btnMakeConstant->getRenderTree();
	Renderable* sum = btnMakeSummation->getRenderTree();

	assert(osc->next);
	assert(env->next);
	assert(con->next);
	osc->next->next = env;
	env->next->next = con;
	con->next->next = sum;
	bounds->child = osc;
	return bounds;
}
