#include "globals.h"
#include "Logics.h"

/*
* implemetation on concrete logics methods
*/
PatrolLogic::PatrolLogic(NPC *me,float distance, unsigned delay,bool useCount):
	ILogic(me),
	_d(),
	init(0),
	_distance(0),
	_out(),
	_isCounting(useCount)
{
	_out.PatrolCount = 0;
	_d.set(delay); //delay
	_distance = distance;
	init = _me->readPosition().x;
}
void PatrolLogic::doAi(){
	_d.update();
	//start
	if((!_me->isMoving()) && (_d.isOver())){
		turn();
		_me->move();
	}
	//end
	if(	(fabs(init-_me->readPosition().x) >= _distance) && (_me->isMoving())){
		_me->stand();
		init = _me->readPosition().x;
		_d.start();
		if(_isCounting)
			++_out.PatrolCount;
	}
}
const void* PatrolLogic::getState() const{
	return &_out;
}
/* turn on other side */
void PatrolLogic::turn(){
	if(_me->readDirection() > 0){
		_me->turnLeft();
	}else{
		_me->turnRight();
	}
}


DeadLogic::DeadLogic(NPC *me):
  ILogic(me)
{
	_me->stand();
	_me->changeAnim(NPC::DEAD);
}
void DeadLogic::doAi(){
}
const void* DeadLogic::getState() const{
	return NULL;
}


AttackLogic::AttackLogic(NPC *me, const NPC* target):
ILogic(me),
_target(target)
{
}
void AttackLogic::doAi(){
	if(_out._isTargetDead){
		return;
	}
	if(_target->isDead()){
		_me->stand();
		_out._isTargetDead = true;
		return;
	}
	float diff, dist;
	diff = _target->readPosition().x-_me->readPosition().x;
	dist = fabs(diff);
	if(diff > 0){
		_me->turnRight();
	}else{
		_me->turnLeft();
	}
	if(dist <= _me->readAttDistance()){
		if(_me->isMoving())
			_me->stand();
		_me->attack();
	}else{
		_me->move();
	}
}
const void* AttackLogic::getState() const{
	return &_out;
}