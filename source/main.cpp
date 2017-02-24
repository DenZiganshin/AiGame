#include "globals.h"

const int FPS(45);
const unsigned WND_HEIGHT = 250;
const unsigned WND_WIDTH = 400;
Game *g_game;
unsigned g_delayBtwFrames = 1000/FPS;


/*
*	calc when window need redraw
*/
void draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	g_game->draw();	
	glutSwapBuffers();
}

/*
*	enter frame calcs
*/
void calcs(){
	g_game->update();
}

/*
*	program main cycle
*/
void cycle(){
	//calc
	calcs();
	//draw
	draw();
	//delay
	Sleep(g_delayBtwFrames);
}

/*
* on resize window
*/
void resize(int w, int h){
	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0,w,0,h, 10,-10);

	glMatrixMode(GL_MODELVIEW);
}

/*
*	on keyboard
*/
void keyb(unsigned char key, int x, int y){
	g_game->keyb(key);
}



int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(WND_WIDTH, WND_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("title");

	//callbacks
	glutDisplayFunc(draw);
	glutIdleFunc(cycle);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyb);

	//gl draw setups
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//init game
	g_game = &Game::getInstance();
	
    glutMainLoop();
    return 0;
}
