#ifndef GLOBALSH
#define GLOBALSH

#include <windows.h>
#include <gdiplus.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>

//init basic types
typedef struct{
	float x,y;
}Point2f;

#include "CUtils.h"
#include "CAnim.h"
#include "CActor.h"
#include "NPC.h"
#include "Logics.h"
#include "UseLogics.h"
#include "NPCFactory.h"
#include "Game.h"

extern const int FPS;
extern const unsigned WND_WIDTH;
extern const unsigned WND_HEIGHT;

#endif