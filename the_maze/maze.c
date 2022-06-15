#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

//Assign a map to move around
const short MAP[MAP_GRID_HEIGHT][MAP_GRID_WIDTH] = {
    {R,R,R,R,R,R,R,R,R,R},
    {R,B,0,0,0,0,P,0,B,R},
    {R,0,0,0,0,0,0,0,0,R},
    {R,0,0,G,0,0,G,0,0,R},
    {R,0,0,0,0,0,0,0,0,R},
    {R,0,0,0,0,0,0,0,0,R},
    {R,0,0,G,0,0,G,0,0,R},
    {R,0,0,0,0,0,0,0,0,R},
    {R,B,0,0,0,0,0,0,B,R},
    {R,R,R,R,R,R,R,R,R,R}
};

// Program globals 
Uint32* screenBuffer    = NULL;
Uint32* redXorTexture   = NULL;
Uint32* reXorTexture = NULL;
Uint32* blueXorTexture  = NULL;
Uint32* grayXorTexture  = NULL;

const Uint64 COLORS[4] = {
    RGBtoABGR(255, 0, 0),
    RGBtoABGR(0, 255, 0),
    RGBtoABGR(0, 0, 255),
    RGBtoABGR(128, 128, 128)
};

Uint32* TEXTURES[4];

//program links
char gameIsRunning    = TRUE;
char showMap          = TRUE;
char distortion       = FALSE;
char slowRenderMode   = FALSE;
char rayCastMode      = 0;
char textureMode      = 0;
