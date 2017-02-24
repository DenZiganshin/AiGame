#ifndef LOGICSH
#define LOGICSH

#include "globals.h"
#include "NPC.h"

/*
*	declarations
*/
class PatrolLogic;
class DeadLogic;
class AttackLogic;


/*
*	concrete Logic declarations
*	Patrol Logic
*/
class PatrolLogic: public ILogic{
public:
	/* declare struct which pointer will be returned by getState */
	struct COut{
		unsigned PatrolCount;
	};
private:
	float init,_distance;
	COut _out;
	Delay _d;
	bool _isCounting;
	/* turn on other side */
	void turn();
public:
	PatrolLogic(NPC *me,float distance, unsigned delay, bool useCount = false);
	void doAi();
	const void* getState() const;
};

/*
*	Dead Logic
*/
class DeadLogic: public ILogic{
	Delay _d;
public:
	DeadLogic(NPC *me);
	void doAi();
	const void* getState() const;
};

/*
*	Attack Logic
*/
class AttackLogic: public ILogic{
public:
	struct COut{
		bool _isTargetDead;
		COut():
		_isTargetDead(false)
		{}
	};
private:
	Delay _d;
	COut _out;
	const NPC* _target;
public:
	AttackLogic(NPC *me, const NPC* target);
	void doAi();
	const void* getState() const;
};

#endif