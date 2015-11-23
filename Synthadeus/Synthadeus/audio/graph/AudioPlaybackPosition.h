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
	int positionL, positionR;
	int maxPosition;
public:
	inline void setMaxPosition(int maxPos) { maxPosition = maxPos; }
	inline AudioPlaybackPosition(int bufferSize = 0) : positionL(0), positionR(0), maxPosition(bufferSize) {}
	inline void moveToStart() { positionL = 0; positionR = 0; }
	inline void moveToTime(int timeL, int timeR) { positionL = timeL % maxPosition; positionR = timeR % maxPosition; }
	inline int getPositionL() { int pos = positionL; positionL = ((positionL + 1) % maxPosition); return pos; }
	inline int getPositionR() { int pos = positionR; positionR = ((positionR + 1) % maxPosition); return pos; }
};
