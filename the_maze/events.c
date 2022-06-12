#include "maze.h"

/**
 * consumeSDLEvents - handles all game evens on keypress
 * 
 * Return : event
 */

void consumeSDLEvents() 
{
    SDL_Event event;
    char keyIsDown;

    while(SDL_PollEvent(&event)) 
    {
        keyIsDown = (event.type == SDL_KEYDOWN);
        switch(event.type) {
            case SDL_KEYUP:
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) 
                {
                    case SDLK_UP:
                        movingForward = keyIsDown;
                        break;
                    case SDLK_DOWN:
                        movingBack = keyIsDown;
                        break;
                    case SDLK_LEFT:
                        turningLeft = keyIsDown;
                        break;
                    case SDLK_RIGHT:
                        turningRight = keyIsDown;
                        break;
                    case SDLK_LSHIFT:
                    case SDLK_RSHIFT:
                        playerIsRunning = keyIsDown;
                        break;
                    case SDLK_ESCAPE:
                        gameIsRunning = FALSE;
                        break;
                    case SDLK_t:
                        if(keyIsDown) textureMode = (textureMode + 1) % 2;
                        break;
                    case SDLK_m:
                        if(keyIsDown) showMap = !showMap;
                        break;
                    case SDLK_f:
                        if(keyIsDown) distortion = !distortion;
                        break;
                    case SDLK_r:
                        if(keyIsDown) slowRenderMode = !slowRenderMode;
                        break;
                    case SDLK_c:
                        if(keyIsDown) rayCastMode = (rayCastMode + 1) % 3;
                        break;
                    case SDLK_LEFTBRACKET:
                        if(keyIsDown && distFromViewplane - 20.0f > 100.0f) distFromViewplane -= 20.0f;
                        break;
                    case SDLK_RIGHTBRACKET:
                        if(keyIsDown) distFromViewplane += 20.0f;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                gameIsRunning = FALSE;
                break;
            default:
                break;
        }
    }
}
