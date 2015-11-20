////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Font and Color Palettes                                                  //
//   Everett Moser                                                            //
//   11-11-15                                                                 //
//                                                                            //
//   A list of all colors and fonts used by Direct2D                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

// number of colors
#define RENDER_COLOR_PALETTE_SIZE 17

// color code values (RGB format, 0-255)
// greyscale
#define COLOR_CODE_WHITE 0xFAFAFA
#define COLOR_CODE_BLACK 0x010101
#define COLOR_CODE_LTGREY 0xBDBDBD
#define COLOR_CODE_GREY 0x757575
#define COLOR_CODE_DKGREY 0x424242

// windows api lolz colors
#define COLOR_CODE_CORNFLOWERBLUE 0x6495ED

// basic color scale
#define COLOR_CODE_RED 0xFF3D00
#define COLOR_CODE_ORANGE 0xFF8F00
#define COLOR_CODE_YELLOW 0xFFEB3B
#define COLOR_CODE_GREEN 0x00C853
#define COLOR_CODE_BLUE	0x304FFE
#define COLOR_CODE_MAGENTA 0x6200EA
#define COLOR_CODE_CYAN 0x00E5FF
#define COLOR_CODE_PINK 0xE91E63
#define COLOR_CODE_BROWN 0x3E2723
#define COLOR_CODE_ABLACK 0x010101

// a fully alpha'd color
#define COLOR_CODE_NONE 0x000000


// color indices
// greyscale
#define COLOR_WHITE 0
#define COLOR_BLACK 1
#define COLOR_LTGREY 2
#define COLOR_GREY 3
#define COLOR_DKGREY 4
#define COLOR_CORNFLOWERBLUE 5
#define COLOR_RED 6
#define COLOR_ORANGE 7
#define COLOR_YELLOW 8
#define COLOR_GREEN 9
#define COLOR_BLUE	10
#define COLOR_MAGENTA 11
#define COLOR_CYAN 12
#define COLOR_PINK 13
#define COLOR_BROWN 14

#define COLOR_ABLACK 15

#define COLOR_NONE 16

// number of fonts
#define RENDER_FONT_PALETTE_SIZE 3

// font indicies
#define FONT_ARIAL20 0
#define FONT_ARIAL40 1
#define FONT_ARIAL11 2