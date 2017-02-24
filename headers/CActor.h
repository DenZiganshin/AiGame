#ifndef CACTORH
#define CACTORH

#include "globals.h"

/* class to control delays between actions */
class Delay{
	unsigned _curr;
	unsigned _duration;
public:
	Delay():_curr(0),_duration(0){}
	void set(unsigned duration){
		_duration = duration;
	}
	void start(){
		_curr = _duration;
	}
	void reset(){
		_curr = 0;
	}
	bool update(){
		if(_curr > 0){
			_curr--;
			return true;
		}
		return false;
	}
	bool isOver() const{
		return _curr==0?true:false;
	}
};

/*
*	methods & objects defines Actor
*/
class CActor{
public:
	/* animation indeces */
	enum AnimName{
		UNDEF = -1,
		STAND = 0,
		MOVE,
		MELEE_ATTACK,
		DEAD
	};
	enum ActorState{
		STATE_STAND,
		STATE_MOVE,
		STATE_DEAD,
		STATE_ATTACK
	};
private:
	float _step; //current x translation
	CAnim _anim;
	Point2f _pos;
	//delay between melee attacks
	Delay _dAttack;

protected:
	char _dir; //look direction
	float _hp;
	float _dmg;
	float _attDistance;
	float _stepSize; //unsigned size of step
	/* animation indeces */
	AnimName _currentAnim;
	ActorState _state;
	CActor();	
public:	
	/*
	* setups
	*/
	void setupAnim(const CAnim::SpriteList& l);
	/* move on direction */
	void setupActor(float x, float y, float stepSize, float initHP, float dmg, float distance);
	/*
	*	controls
	*/
	/* turn hero. change _dir */
	bool turnLeft();
	bool turnRight();
	/* move on current direction */
	bool move();
	/*stop moving */
	bool stand();
	/* start melee attack */
	bool attack();
	/*decrase current actor's hp */
	void damage(float dmg);
	void dead();
	/*
	*	get Info
	*/
	/*read position*/
	const Point2f& readPosition() const;
	/* read look direction */
	char readDirection() const;
	/* return distance of melee attack */
	float readAttDistance() const;
	/* return melee attack damage*/
	float readDmg() const;
	/* is actor moving (_step != 0) */
	bool isMoving() const;
	/* is _hp < 0 */
	bool isDead() const;
	/* is on melee attack */
	bool isAttack() const;
	/* is stand */
	bool isStand() const;
	
	/*
	*	system methods
	*/
	/* update actor state (usually for moving)*/
	void update();
	/*change current anim*/
	bool changeAnim(AnimName name);
	/* draw actor. Must be called by draw*/
    void draw();
	/*destructor*/
	virtual ~CActor();
};

#endif
