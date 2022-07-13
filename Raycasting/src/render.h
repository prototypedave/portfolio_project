#ifndef _RENDER_HEADER_
#define _RENDER_HEADER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <pthread.h>
#include <unistd.h>
#include "main.h"
#include "gest_event.h"
#include "map.h"

#define FPS_TO_GET 1000/60.0

#define ULTRA 1
#define HIGH 2
#define MEDIUM 4
#define LOW 6

#define DOF (MAPSIZE * 1.5)
#define BLOCK_SIZE 64

#define NB_RAYS (screen_width/QUALITY)
#define FOV_ANGLE 60

#define ANGLE_INC ((DR * FOV_ANGLE)/(NB_RAYS))

extern int Window_Height;
extern int Window_Width;

extern int DrawHitEffect;

extern int startTime;
extern int currTime;
extern double elapsedTime;

int BouclePrincipale();

void AffichageMap();

void drawX();

#endif /*_RENDER_HEADER_*/
