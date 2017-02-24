#ifndef GAMEH
#define GAMEH

#include "globals.h"

/*
*	main class. Methods called by main
*/
class Game{
	/* npc's y position */
	static const int _yPos = 20;
	/* npcs number */
	static const unsigned _maxNPC = 30;
	unsigned _numNPC;
	/* NPC array */
	NPC **_npcs;
	/* camera moves on _camStep pixels */
	const float _camStep;
	/* current camera x position */
	float _x;
	/* npc factory */
	NpcFactory* fact[1];
public:
	/* get instance of singleton */
	static Game& getInstance();
	/* draw all elements of game */
	void draw();
	/* update game logic */
	void update();
	void keyb(unsigned char key);
private:
	// constructor
	Game();
	Game(const Game& r);
	Game& operator=(const Game& r);

	void addNPC(float x);

	//destructor
	~Game();
};


#endif