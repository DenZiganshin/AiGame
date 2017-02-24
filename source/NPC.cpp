#include "globals.h"
#include "NPC.h"


/*
* NPC implementations
*/
NPC::NPC():
	CActor(),
	_useLogic(NULL)
{
}
/* initialization */
void NPC::setupNPC(unsigned delayBtwAttacks, unsigned delayBtwMoves, unsigned delayBtwTurns){
	stand();
	//setup delays
	_dAttacks.set(delayBtwAttacks);
	_dMoves.set(delayBtwMoves);
	_dTurns.set(delayBtwTurns);
}
void NPC::setupAi(UseLogic *ai){
	_useLogic = ai;
}
/* every frame update */
void NPC::update(const NPC *const*v, unsigned len){
	CActor::update();
	_dAttacks.update();
	_dMoves.update();
	_dTurns.update();
	_useLogic->use(v,len);
}
//destructor
NPC::~NPC(){
	delete _useLogic;
}

void NPC::move(){
	if(_dMoves.isOver())
		CActor::move();
}
void NPC::turnLeft(){
	if(!_dTurns.isOver())
		return;
	if(CActor::turnLeft())
		_dTurns.start();
}
void NPC::turnRight(){
	if(!_dTurns.isOver())
		return;
	if(CActor::turnRight())
		_dTurns.start();
}
void NPC::attack(){
	if(!_dAttacks.isOver())
		return;
	if(!CActor::attack())
		return;
	_dAttacks.start();
}
void NPC::stand(){
	if(CActor::stand()){
		_dMoves.start();
	}
}
