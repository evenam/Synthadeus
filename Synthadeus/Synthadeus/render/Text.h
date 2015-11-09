////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   A Text Renderable                                                        //
//   Everett Moser                                                            //
//   11-9-15                                                                  //
//                                                                            //
//   A simple way to create renderable text elements                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Renderable.h"
#include "Vector2D.h"

#define TEXT_MAX_STRING_LENGTH 256

class Text : public Renderable
{
private:
	char buffer[TEXT_MAX_STRING_LENGTH];
	int font;
	int color;
	Point point1, point2;

public:
	Text(char* string, Point p1, Point p2, int fontType, unsigned int fontColor);
	void setAttributes(char* string, int fontType, unsigned int fontColor);
	void setArea(Point p1, Point p2);
	virtual void render(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush** colorPalette, IDWriteTextFormat** fontPalette);
};

