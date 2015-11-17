#include "Text.h"

Text::Text(char * string, Point p1, Point p2, int fontType, unsigned int fontColor)
{
	strcpy_s(buffer, string);
	font = fontType;
	color = fontColor;
	origin[0] = p1[0];
	origin[1] = p1[1];
	size[0] = p2[0];
	size[1] = p2[1];
}

void Text::render(Render2D* render2d, ID2D1HwndRenderTarget * renderTarget, ID2D1SolidColorBrush ** colorPalette, IDWriteTextFormat** fontPalette)
{
	Point instanceOrigin = render2d->getInstance();
	WCHAR temporaryStringBuffer[TEXT_MAX_STRING_LENGTH];
	int strLength = strlen(buffer);
	for (int i = 0; i < strLength; i++)
		temporaryStringBuffer[i] = (WCHAR)buffer[i];
	renderTarget->DrawText(temporaryStringBuffer, strLength, fontPalette[font],
		D2D1::RectF(instanceOrigin[0] + origin[0], instanceOrigin[1] + origin[1], 
			origin[0] + size[0] + instanceOrigin[0], origin[1] + size[1] + instanceOrigin[1]), colorPalette[color]);
}

Point Text::getOrigin()
{
	return origin;
}
