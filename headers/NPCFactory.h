#ifndef NPCFACTORYH
#define NPCFACTORYH

#include "globals.h"

/*
*	interface class to create different types of NPC
*/
class NpcFactory{	
protected:
	NpcFactory(){
	}
public:
	virtual NPC* create(float initX, float initY) = 0;
	virtual ~NpcFactory(){
	}
};


/*
*	basic NPC creator
*/
class BasicNPC : public NpcFactory{
	GLuint tex;	
	CAnim::SpriteList slist;
	CAnim::SpriteAnim stand,move,melee,dead;
public:
	/*
	*	constructor: creates texture usig CUtils
	*	create sprite list description (CAnim::SpriteList)
	*	init sprite animations (CAnim::SpriteAnim) using ids from CActor (CActor::AnimName)
	*/
	BasicNPC();
	/*
	*	overrided method create
	*	initX - start x position
	*	calls all npcSetup methods
	*/
	NPC* create(float initX, float initY);
};



#endif