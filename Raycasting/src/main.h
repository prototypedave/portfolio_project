#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_

#include <SDL2/SDL.h>
#include "render.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define GAMERUNNING 1
#define MENU 0
#define SETTINGS 2
#define END_SCREEN 4

#define pi 3.14159265358979323846
#define pi2 pi/2
#define pi3 3*pi/2
#define DR 0.0174533
#define SENSI 0.1

extern int screen_height;
extern int screen_width;

extern int drawincenter;

extern int running;
extern int GameOption;

extern int QUALITY;




float dist(float x1, float y1, float x2, float y2);

float getScalingFactor(float x1, float y1, float x2, float y2);


#endif
