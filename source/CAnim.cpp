#include "globals.h"
#include "CAnim.h"

CAnim::CAnim():
_sAnimId(0),
_frameW(0), _frameH(0),
_sumFrame(0),
_cx(0), _cy(0),
_last(0),
_isStatic(false),
_isInvert(false),
_isLoop(true)
{}
void CAnim::setup(const SpriteList& l){
	_slist = l;
	_frameW = 1.0f/_slist.spWidth;
	_frameH = 1.0f/_slist.spHeight;
}
void CAnim::playAnim(byte index, bool isInvert, bool isLoop){
	index = index>=_slist.anims.size()?_slist.anims.size()-1:index;
	index = index<0?0:index;

	//flags
	_sAnimId = index;
	_isInvert = isInvert;
	_isLoop = isLoop;
	SpriteAnim *tempA = &_slist.anims[_sAnimId];
	//init coords
	_cx = tempA->initX;
	_cy = tempA->initY;
	//calc last anim frame
	_last = tempA->initX + tempA->len-1;
	_last = _last>=_slist.spWidth ? _slist.spWidth-1 : _last;
	//check static
	if(tempA->fdelay == (byte)-1)
		_isStatic = true;
}
void CAnim::draw(float x, float y){
	//check time
	if(!_isStatic)
		nextFrame();
	//drawImage
	float currFrameX = _frameW * _cx;
	float currFrameY = _frameH * _cy;

	CUtils::drawTex(_slist.texId, 	x+_slist.offset.x, y+_slist.offset.y,
									_slist.imgWidth,_slist.imgHeight,
					currFrameX, currFrameY, _frameW, _frameH,_isInvert);
}
void CAnim::nextFrame(){
	if((!_isLoop) && (_cx == _last))
		return;
	_sumFrame += 1;
	if(_sumFrame < _slist.anims[_sAnimId].fdelay)
		return;
	//next frame
	_sumFrame = 0;
	_cx += 1;
	if(_cx > _last){
		_cx = _slist.anims[_sAnimId].initX;
	}
}
