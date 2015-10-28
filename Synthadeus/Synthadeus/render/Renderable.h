////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Renderable Interface                                                     //
//   Everett Moser                                                            //
//   10-5-15                                                                  //
//                                                                            //
//   Interface for defining renderable items for the renderer                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../common/Object.h"

class Renderable : public Object
{
public:
	RTTI_MACRO(Renderable);

	virtual void render() = 0; // issue D2D commands
	virtual bool inView(float viewLeft, float viewTop, float viewRight, float viewBottom) = 0; // are we inside rectangle?
	
	// collision check against two axis aligned rectangles
	static inline bool collisionCheckBoundingBox(float left1, float top1, float right1, float bottom1, 
												 float left2, float top2, float right2, float bottom2)
	{
		if (left1 > right2) return false;
		if (left2 > right1) return false;
		if (top1 < bottom2) return false;
		if (top2 > bottom1) return false;
		return false;
	}
};
