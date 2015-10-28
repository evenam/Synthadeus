////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Line																      //
//   James Bellard                                                            //
//   9-27-15                                                                  //
//                                                                            //
//   Stores the 2 points of a line data and draws the line on the screen.	  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <Windows.h>
#include "../common/Object.h"

class Line : public Object
{
private:
	float ** coordArray;

public:
	 Line(float, float, float, float);
	~Line();
	void set(float, float, float, float);
	float** get();
};

