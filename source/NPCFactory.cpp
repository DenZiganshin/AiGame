#include "globals.h"
#include "NPCFactory.h"

BasicNPC::BasicNPC(): 
  tex(0),
  stand(CActor::STAND,0,0,2,20),
  move(CActor::MOVE,0,1,4,10),
  melee(CActor::MELEE_ATTACK,0,2,4,3),
  dead(CActor::DEAD,0,3,4,4)
{
	srand((unsigned)time(NULL));
	tex = CUtils::loadTexture("sprite.png");

	slist.texId = tex;
	slist.spWidth = 4; slist.spHeight = 4;
	slist.imgWidth = 100; slist.imgHeight = 100;
	slist.offset.x = -44; slist.offset.y = 0;
	slist.anims.push_back(stand);
	slist.anims.push_back(move);
	slist.anims.push_back(melee);
	slist.anims.push_back(dead);
}

/*
*	overrided method create
*	initX - start x position
*	calls all npcSetup methods
*/
NPC* BasicNPC::create(float initX, float initY){
	NPC *ret = new NPC();

	ret->setupAnim(slist);
	ret->setupActor(initX, initY, float(rand()%20+10)/10.0f, (float)(rand()%20+20), (float)(rand()%3+1), 15);
	ret->setupNPC(rand()%50+5,rand()%10+5,2);
	ret->setupAi(new BasicAi(ret, 300.0f, 50.0f, 20));
	return ret;
}