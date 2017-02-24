#include "globals.h"

Game& Game::getInstance(){
	static Game g;
	return g;
}
void Game::draw(){
	glPushMatrix();
	glTranslatef(_x,0,0);
	for(unsigned i=0; i<_numNPC; ++i){
		_npcs[i]->draw();
	}
	glPopMatrix();
}
void Game::update(){
	for(unsigned i=0; i<_numNPC; ++i){
		_npcs[i]->update(_npcs,_numNPC);
	}
}

Game::Game():
_npcs(NULL),
_x(0),
_numNPC(20),
//const
_camStep(5.0f)
{
	srand((unsigned)time(NULL));

	//init NPCs array
	_npcs = new NPC*[_maxNPC];

	//create factory
	fact[0] = new BasicNPC();

	for(unsigned i=0; i<_numNPC; ++i){
		_npcs[i] = fact[0]->create((float)(rand()%500+10), (float)_yPos);
	}
	
}

Game::~Game(){
	for(unsigned i=0; i<_numNPC; ++i){
		delete _npcs[i];
	}
	delete _npcs;

	//delete factories
	delete fact[0];
}
void Game::keyb(unsigned char key){
	if(key == 'a'){
		_x += _camStep;
	}
	if(key == 'd'){
		_x -= _camStep;
	}
	if(key == '1'){
		addNPC((float)WND_WIDTH/2.0f-_x);
	}
}

void Game::addNPC(float x){
	if(_numNPC >= _maxNPC)
		return;
	_npcs[_numNPC] = fact[0]->create(x, (float)_yPos);
	++_numNPC;
}