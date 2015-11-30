////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Audio Node's Playback Position                                           //
//   Everett Moser                                                            //
//   11-23-15                                                                 //
//                                                                            //
//   Holds data relating to a current position in an audio buffer             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

class AudioPlaybackPosition
{
private:

	// current left and right position
	int positionL, positionR;

	// the maximum position before restarting from zero
	int maxPosition;

public:

	// update the maximum (probably to buffer size)
	inline void setMaxPosition(int maxPos) { maxPosition = maxPos; }

	// initialize a zero size playback portion
	inline AudioPlaybackPosition(int bufferSize = 0) : positionL(0), positionR(0), maxPosition(bufferSize) {}

	// reset the position to the start
	inline void moveToStart() { positionL = 0; positionR = 0; }

	// move the position to a specific time
	inline void moveToTime(int timeL, int timeR) { positionL = timeL % maxPosition; positionR = timeR % maxPosition; }

	// return the left position, and advance it
	inline int getPositionL() 
	{ 
		int pos = positionL; 
		positionL = ((positionL + 1) % maxPosition); 
		return pos; 
	}

	// return the right position, and advacne it
	inline int getPositionR() { 
		int pos = positionR; 
		positionR = ((positionR + 1) % maxPosition); 
		return pos; 
	}
};
