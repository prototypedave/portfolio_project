#include <stdlib.h>
#include "maze.h"

//calculates the height to draw wall/texture
float calculateDrawHeight(float rayLength) 
{
    return distFromViewplane * WALL_SIZE / rayLength;
}

// draws untextured structure
void drawUntexturedStrip(int x, float wallYStart, float length, Uint32 ABGRColor, char darken) 
{
    int y;

    if(wallYStart < 0)
        wallYStart = 0;

    for(y = 0; y < WINDOW_HEIGHT; y++) 
    {
        if(y < wallYStart) 
        {
            screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = CEILING_COLOR;
        } else if(y > (wallYStart + length)) 
        {
            screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = FLOOR_COLOR;
        } else 
        {
            screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = (darken) ? ABGRColor : DARKEN_COLOR(ABGRColor);
        }
    }
}

void drawTexturedStrip(int x, float wallYStart, float length, int textureX, Uint32* texture, char darken) 
{
    int y;
    float d, ty;
    Uint32 color;

    if(wallYStart < 0)
        wallYStart = 0;

    for(y = 0; y < WINDOW_HEIGHT; y++) 
    {
        d = y - (WINDOW_HEIGHT / 2.0f) + length / 2.0f;
        ty = d * (float)(TEXTURE_SIZE-EPS) / length;

        if(y < wallYStart) 
        {
            screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = CEILING_COLOR;
        } else if(y > (wallYStart + length)) 
        {
            screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = FLOOR_COLOR;
        } else 
        {
            color = texture[XY_TO_TEXTURE_INDEX(textureX, (int)ty)];
            if(darken) color = DARKEN_COLOR(color);

            screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = color;
        }
    }

}
