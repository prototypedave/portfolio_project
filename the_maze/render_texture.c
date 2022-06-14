#include <stdlib.h>
#include "maze.h"

/**
* getTextureColumnNumberForRay - checks for tile the player is on and the texture
*Vector3f* ray - variable to record ray hit position
*
*Return: texture
*/

int getTextureColumnNumberForRay(Vector3f* ray, RayType rtype) 
{
    Vector3f rayHitPos = vectorAdd(&playerPos, ray);
    if(rtype == HORIZONTAL_RAY) 
    {
        if(ray->y < 0)
            return (int)rayHitPos.x % TEXTURE_SIZE;
        else
            return TEXTURE_SIZE - 1 - ((int)rayHitPos.x % TEXTURE_SIZE);
    } else 
    {
        if(ray->x > 0)
            return (int)rayHitPos.y % TEXTURE_SIZE;
        else
            return TEXTURE_SIZE - 1 - ((int)rayHitPos.y % TEXTURE_SIZE);
    }
}

float getUndistortedRayLength(Vector3f* ray) 
{
    Vector3f undistortedRay;
    Vector3f proj = vectorProjection(ray, &viewplaneDir);
    undistortedRay = vectorSubtract(ray, &proj);

    return homogeneousVectorMagnitude(&undistortedRay);
}

void renderProjectedScene() 
{
    int i;

    if (slowRenderMode) 
    {
        int x, y;

        for(x = 0; x < WINDOW_WIDTH; x++)
            for(y = 0; y < WINDOW_HEIGHT; y++)
                screenBuffer[(WINDOW_WIDTH * y) + x] = 0xFFFFFFFF;
    }

    for(i = 0; i < WINDOW_WIDTH; i++) 
    {
        int textureX = 0;
        int mapx, mapy;
        float drawLength;
        RayType rtype;
        Vector3f ray;

        if(homogeneousVectorMagnitude(&rays[i].hRay) < homogeneousVectorMagnitude(&rays[i].vRay)) 
        {
            Vector3f coords;
            ray = rays[i].hRay;
            rtype = HORIZONTAL_RAY;

            coords = getTileCoordinateForHorizontalRay(&ray);
            mapx = coords.x;
            mapy = coords.y;
        } else 
        {
            Vector3f coords;
            ray = rays[i].vRay;
            rtype = VERTICAL_RAY;

            coords = getTileCoordinateForVerticalRay(&ray);
            mapx = coords.x;
            mapy = coords.y;
        }

        if(textureMode)
            textureX = getTextureColumnNumberForRay(&ray, rtype);

        if(distortion)
            drawLength = calculateDrawHeight(homogeneousVectorMagnitude(&ray));
        else
            drawLength = calculateDrawHeight(getUndistortedRayLength(&ray));

        if(textureMode) 
        {
            int texnum = MAP[mapy][mapx];
            if(texnum < 1 || texnum > 4)
                texnum = 4;
            drawTexturedStrip(i, (WINDOW_HEIGHT / 2.0f) - (drawLength / 2.0f), drawLength, textureX, TEXTURES[texnum - 1], rtype == HORIZONTAL_RAY);

        } else 
        {
            int color = MAP[mapy][mapx];
            if(color < 1 || color > 4)
                color = 4;
            drawUntexturedStrip(i, (WINDOW_HEIGHT / 2.0f) - (drawLength / 2.0f), drawLength, COLORS[color - 1], rtype == HORIZONTAL_RAY);
        }
        if (slowRenderMode) 
        {
            clearRenderer();
            displayFullscreenTexture(screenBuffer);
            SDL_Delay(2);
        }
    }
    if (slowRenderMode)
        slowRenderMode = 0;

    clearRenderer();
    displayFullscreenTexture(screenBuffer);
}
