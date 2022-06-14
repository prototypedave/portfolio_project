#include "maze.h"

/**
* functions:
* 1- draws color
* 2- draws line
* 3- rectangle
*/
void setDrawColor(int r, int g, int b, int a) 
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void drawLine(int x1, int y1, int x2, int y2) 
{
    int xOffset = 0;
    int yOffset = 0;

    if (x2 - x1 > 0) xOffset = -1;
    if (y2 - y1 > 0) yOffset = -1;

    SDL_RenderDrawLine(renderer, x1, y1, x2 + xOffset, y2 + yOffset);
}

void fillRect(int x, int y, int w, int h) 
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(renderer, &rect);
}

void drawRect(int x, int y, int w, int h) 
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderDrawRect(renderer, &rect);
}

void presentRenderer() 
{
    SDL_RenderPresent(renderer);
}

void clearRenderer() 
{
    SDL_RenderClear(renderer);
}

