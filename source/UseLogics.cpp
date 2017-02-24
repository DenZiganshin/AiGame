#include "globals.h"
#include "UseLogics.h"



/*
*	basicAi implementation
*/
BasicAi::BasicAi(NPC *me,float viewDist,float patrolDist,unsigned patrolDelay):
	UseLogic(me),
	_state(IDLE),
	_combatTarget(NULL),
	_viewDist(viewDist),
	_patrolDist(patrolDist),
	_patrolDelay(patrolDelay)
{
	next(new PatrolLogic(_me,_patrolDist,_patrolDelay));
	_state = IDLE;
}
void BasicAi::use(const NPC *const*v, const unsigned& len){
	UseLogic::use(v,len);

	if(_state == DEAD)
		return;
	//is _me get damage
	for(unsigned i=0; i<len; ++i){
		//not _me
		if(v[i] == _me)
			continue;
		if(v[i]->isDead())
			continue;
		//distance calc
		float diff, dist; //diff - differece(sign) dist-unsigned
		diff = v[i]->readPosition().x - _me->readPosition().x;
		dist = fabs(diff);
		//check detection
		if( (_combatTarget == NULL) && (dist<=_viewDist) && (onViewSide(_me, v[i])) ){
			startCombat(v[i]);
		}
		//is other[i] attacking
		if(v[i]->isAttack()){
			//in front of v[i]
			if( !onViewSide(v[i], _me) ){
				continue;
			}
			//on attack distance
			float dDist = v[i]->readAttDistance();
			if(dist <= dDist){
				_me->damage(v[i]->readDmg()); //ouch
				startCombat(v[i]);
			}
		}
	}
	//is _me dead
	if((_state != DEAD) && (_me->isDead())){
		_state = DEAD;
		next(new DeadLogic(_me));
	}
	//check dead target
	if( (_state == COMBAT) && (_combatTarget->isDead())){
		next(new PatrolLogic(_me,_patrolDist,_patrolDelay));
		_state = IDLE;
		_combatTarget = NULL;
	}
}

BasicAi::~BasicAi(){
	if(_curr)
		delete _curr;
}
bool BasicAi::isSameSign(float a, float b){
	if( a*b > 0 ){
		return true;
	}
	return false;
}

void BasicAi::startCombat(const NPC *target){
	if(_state == COMBAT)
		return;
	_combatTarget = target;
	_state = COMBAT;
	next(new AttackLogic(_me, _combatTarget));
}

bool BasicAi::onViewSide(const NPC *viewer, const NPC *target){
	if( ((viewer->readPosition().x > target->readPosition().x) && (viewer->readDirection() < 0)) ||
		((viewer->readPosition().x < target->readPosition().x) && (viewer->readDirection() > 0)) )
		return true;
	return false;
}