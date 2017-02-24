#ifndef CANIMH
#define CANIMH

#include "globals.h"

/*
*	methods to draw sprite animations. Used in CActor
*/
class CAnim{
public:
	struct SpriteAnim{
		byte id; //anim index (for using)
		byte initX,initY; //anim start coords (in cells)
		byte len; //anim length
		byte fdelay; //delay between frames (in frames)
		SpriteAnim(byte i, byte x, byte y, byte l, byte d):
		id(i), initX(x), initY(y), len(l), fdelay(d)
		{}
	};
	struct SpriteList{
		GLuint texId;
		byte spWidth,spHeight; //width, height of sprite list in cells
		float imgWidth, imgHeight;
		Point2f offset; //offset from given x,y
		std::vector<SpriteAnim> anims; //specification of anims
	};
private:
	// animation params
	SpriteList _slist;
	//support
	byte _sAnimId;
	float _frameW, _frameH; //size of frame in texture coords (<1.0f)
	byte _last; //last frame index in anim
	bool _isStatic; //no frame change
	bool _isInvert;
	bool _isLoop;
	byte _sumFrame; //frames after last 'nextframe'
	byte _cx, _cy; //current x,y in sprite cells
public:
	CAnim();
	/*  id - textureId;
        spriteWidth,spriteHeight - bitmap size in cells;
        delay - delay in frames*/
	void setup(const SpriteList& l);
	/* go to sprite offset fx,fy */
	void playAnim(byte index, bool isInvert = false, bool isLoop = true);
	/* position and size to draw. Also msec time between frames */
	void draw(float x, float y);
private:
	/* next frame from _cx,_cy */
	void nextFrame();
};


#endif
