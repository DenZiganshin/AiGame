#include "globals.h"

CActor::CActor():
_stepSize(1),
_dir(1),
_currentAnim(UNDEF),
_step(0),
_hp(10),
_dmg(1),
_attDistance(5),
_state(STATE_STAND)
{
    //init
}

void CActor::setupAnim(const CAnim::SpriteList& l){
	_anim.setup(l);
	for(unsigned i=0; i<l.anims.size(); i++)
		if(l.anims[i].id == MOVE){
			_dAttack.set(l.anims[i].len*l.anims[i].fdelay);
		}
}
void CActor::setupActor(float x, float y, float stepSize, float initHP, float dmg, float distance){
	_pos.x = x;
	_pos.y = y;
	_stepSize = stepSize;
	_hp = initHP;
	_dmg = dmg;
	_attDistance = distance;
}
CActor::~CActor(){
}
void CActor::draw(){
	//check phys initialized
    _anim.draw(_pos.x, _pos.y);
}
bool CActor::turnLeft(){
	if(_state != STATE_STAND)
		return false;
	_dir = -1;
	return true;
}
bool CActor::turnRight(){
	if(_state != STATE_STAND)
		return false;
	_dir = 1;
	return true;
}
bool CActor::move(){
	if(!((_state == STATE_STAND) || (_state == STATE_MOVE)))
		return false;
	_step = _stepSize * _dir;
	changeAnim(MOVE);
	_state = STATE_MOVE;
	return true;
}
void CActor::update(){
	if(_state == STATE_MOVE)
		_pos.x += _step;
	if(_state == STATE_ATTACK){
		if(!_dAttack.update()){
			_state = STATE_STAND;
			stand();
		}
	}
}

bool CActor::stand(){
	if( !((_state == STATE_STAND) || (_state == STATE_MOVE)) )
		return false;
	_step = 0;
	_state = STATE_STAND;
	changeAnim(STAND);
	return true;
}

bool CActor::changeAnim(AnimName name){
	if(_currentAnim == name){
		return false;
	}
	bool inv = _dir<0?false:true;
	switch(name){
	case STAND: _anim.playAnim(STAND,inv);
		break;
	case MOVE: _anim.playAnim(MOVE,inv);
		break;
	case MELEE_ATTACK: _anim.playAnim(MELEE_ATTACK,inv,false);
		break;
	case DEAD: _anim.playAnim(DEAD,inv,false);
		break;
	default:
		_anim.playAnim(MOVE,inv);
	}	
	_currentAnim = name;
	return true;
}

const Point2f& CActor::readPosition() const{
	return _pos;
}

char CActor::readDirection() const{
	return _dir;
}

bool CActor::isMoving() const{
	return _state == STATE_MOVE;
}
bool CActor::isAttack() const{
	return _state == STATE_ATTACK;
}
float CActor::readAttDistance() const{
	return _attDistance;
}
float CActor::readDmg() const{
	return _dmg;
}


bool CActor::attack(){
	//can attack
	if(_state != STATE_STAND)
		return false;
	//start anim
	changeAnim(MELEE_ATTACK);
	_dAttack.start();
	_state = STATE_ATTACK;
	return true;
}

void CActor::damage(float dmg){
	_hp -= dmg;
	if(_hp <= 0){
		_state = STATE_DEAD;
	}
}

void CActor::dead(){
	_dAttack.reset();
	_state = STATE_DEAD;
	changeAnim(DEAD);
}
bool CActor::isDead() const{
	return _state == STATE_DEAD;
}