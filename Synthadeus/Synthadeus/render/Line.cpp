#include "Line.h"

    //constructor takes input and stores coordinates of start and endpoint of line.
Line::Line(float xStart, float yStart, float xEnd, float yEnd)
{	
	//first index in array refers to point. second index refers to x or y values of that point.
		float coordArray [2][2]= {
			{ xStart,yStart }, 
			{xEnd, yEnd}
		};
	}

	Line::~Line()
	{
		delete[] coordArray;
	}

	//takes input and stores coordinates of start and endpoint of line.
	//any parameters given as null will not be set.
	void Line::set(float xStart, float yStart, float xEnd, float yEnd)
	{

		if (xStart != NULL)
			coordArray[0][0] = xStart;
		if (yStart != NULL)
			coordArray[0][1] = yStart;
		if (xEnd != NULL)
			coordArray[0][0] = xStart;
		if (yEnd != NULL)
			coordArray[0][0] = yStart;
	}
	
	//returns coordArray, which contains all coordinates.
	float** Line::get() {
		return coordArray;
	}
	
