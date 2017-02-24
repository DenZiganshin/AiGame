#ifndef USELOGICSH
#define USELOGICSH

#include "globals.h"
#include "Logics.h"

class BasicAi: public UseLogic{
public:
	struct CInit{
		float param1, param2;
	};
public:
	BasicAi(NPC *me,float viewDist,float patrolDist,unsigned patrolDelay);
	void use(const NPC *const*v, const unsigned& len);
	~BasicAi();
private:
	void startCombat(const NPC *target);
	bool isSameSign(float a, float b);
	bool onViewSide(const NPC *viewer, const NPC *target);
	float _viewDist, _patrolDist;
	unsigned _patrolDelay;
	const NPC *_combatTarget;
	enum State{
		COMBAT,
		IDLE,
		DEAD
	}_state;
};

#endif