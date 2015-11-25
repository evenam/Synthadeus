#include "CommandMenu.h"
#include "Synthadeus.h"

CommandMenu::CommandMenu(Point cmOrigin) :
	btnMakeOscillator(Button(Point(0.f, 0.f),
		Point(120.f, 40.f), COLOR_CORNFLOWERBLUE, COLOR_WHITE, "Oscillator", FONT_ARIAL20, CommandMenu::createOscillator)),
	btnMakeEnvelope(Button(Point(0.f, 40.f),
		Point(120.f, 40.f), COLOR_CORNFLOWERBLUE, COLOR_WHITE, "Envelope", FONT_ARIAL20, CommandMenu::createEnvelope)),
	btnMakeConstant(Button(Point(0.f, 80.f),
		Point(120.f, 40.f), COLOR_CORNFLOWERBLUE, COLOR_WHITE, "Constant", FONT_ARIAL20, CommandMenu::createConstant)),
	btnMakeSummation(Button(Point(0.f, 120.f),
		Point(120.f, 40.f), COLOR_CORNFLOWERBLUE, COLOR_WHITE, "Summation", FONT_ARIAL20, CommandMenu::createSummation)),
	size(Point(120.f, 160.f))
{
	origin[0] = cmOrigin[0];
	origin[1] = cmOrigin[1];
	setBoundingRectangle(origin, size);

	addChild(&btnMakeOscillator);
	addChild(&btnMakeEnvelope);
	addChild(&btnMakeConstant);
	addChild(&btnMakeSummation);
	needsClosing = false;
}

void CommandMenu::createOscillator(Synthadeus* app, Component* other)
{
	//app->createOscillator();
	DebugPrintf("Creating an Oscillator\n");
	CommandMenu* myself = (CommandMenu*)other;
	myself->needsClosing = true;
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
}

void CommandMenu::createEnvelope(Synthadeus* app, Component* other)
{
	//app->createOscillator();
	DebugPrintf("Creating an Envelope\n");
	CommandMenu* myself = (CommandMenu*)other;
	myself->needsClosing = true;
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
}

void CommandMenu::createConstant(Synthadeus* app, Component* other)
{
	//app->createOscillator();
	DebugPrintf("Creating an Constant\n");
	CommandMenu* myself = (CommandMenu*)other;
	myself->needsClosing = true;
	myself->setBoundingRectangle(Point(0.f, 0.f), Point(0.f, 0.f));
}

void CommandMenu::createSummation(Synthadeus* app, Component* other)
{
	//app->createOscillator();
	DebugPrintf("Creating an Summation\n");
	CommandMenu* myself = (CommandMenu*)other;
	myself->needsClosing = true;
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
	Renderable* osc = btnMakeOscillator.getRenderTree();
	Renderable* env = btnMakeEnvelope.getRenderTree();
	Renderable* con = btnMakeConstant.getRenderTree();
	Renderable* sum = btnMakeSummation.getRenderTree();

	osc->next->next = env;
	env->next->next = con;
	con->next->next = sum;
	bounds->child = osc;
	return bounds;
}
