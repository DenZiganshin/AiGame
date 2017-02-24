#ifndef NPCH
#define NPCH

#include "globals.h"
#include "CActor.h"

class UseLogic;

/*
*	child of CActor. Defines methods to control actor by ai
*/
class NPC : public CActor{
	Delay _dAttacks;
	Delay _dMoves;
	Delay _dTurns;

	UseLogic *_useLogic;
public:
	//constructor
	NPC();
	/* initialization */
	void setupNPC(unsigned delayBtwAttacks, unsigned delayBtwMoves, unsigned delayBtwTurns);
	void setupAi(UseLogic *ai);
	/* every frame update */
	void update(const NPC *const*v, unsigned len);

	void move();
	void turnLeft();
	void turnRight();
	void attack();
	void stand();
	//destructor
	~NPC();
private:
};

/*
*	interface of Logic. Objects which make Actor to do some stuff
*	implemented in Logics.h
*/
class ILogic{
protected:
	NPC *_me;
	/* me is NPC object which could be controled by Logic */
	ILogic(NPC *me):
		_me(me)
	{}
public:
	/* must be called every time */
	virtual void doAi() = 0;
	/* return some info */
	virtual const void* getState() const = 0;
	virtual ~ILogic(){
	}
};


/*
*	interface of classes, which use several of ILogics to make ai
*	implemented in UseLogics.h
*/
class UseLogic{
protected:
	NPC *_me;
	ILogic *_curr;
	/* me is NPC object which could be controled by Logic */
	UseLogic(NPC *me): _curr(NULL), _me(me){}
	/* change current Logic to another one */
	virtual void next(ILogic *l){
		if(_curr)
			delete _curr;
		_curr = l;
	}
public:
	/*  must be called every time , calls ILogic::doAi */
	virtual void use(const NPC *const*v, const unsigned& len){
		if(_curr)
			_curr->doAi();
	}
	virtual ~UseLogic(){
		if(_curr)
			delete _curr;
	}
};





#endif