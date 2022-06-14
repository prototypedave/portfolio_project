#include "maze.h"

/**
* initGFX - manages gfx
*
*Return: 1 on Success, 0 on error
*/
int initGFX(char* title, unsigned int width, unsigned int height) 
{
    if(window || renderer) return 0;

    screenWidth = width;
    screenHeight = height;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        gfxSetError("Error initializing SDL", 1);
        return 0;
    }

    window = SDL_CreateWindow(title, 50, 50, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if(!window || !renderer) 
    {
        gfxSetError("Could not create SDL window", 1);
        return 0;
    }

    SDL_SetWindowTitle(window, title);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return 1;
}

/**
* createTexture - creates texture
*
*Return: pixel data
*/
void* createTexture(unsigned int width, unsigned int height) 
{
    Uint32* data;
    ManagedTexture_* newmtex;
    if(!width || !height || !renderer) 
    {
        gfxSetError("SDL window has not been initialized yet", 0);
        return NULL;
    }

    newmtex = malloc(sizeof(ManagedTexture_)); if(!newmtex) { return NULL; }
    newmtex->pitch = width * sizeof(Uint32);
    newmtex->next = NULL;
    newmtex->prev = NULL;
    newmtex->magicTag  = TEX_TAG;

    newmtex->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if(!(newmtex->texture)) 
    {
        free(newmtex);
        gfxSetError("Could not create texture", 1);
        return NULL;
    }

    data = malloc((sizeof(Uint32) * width * height) + sizeof(ManagedTexture_*)); if(!data) {free(newmtex); return NULL; }

    /*
     * Hide a pointer to the managed struct before the actual pixel data.
     *
     * This allows the caller to only have to worry about the data they
     * want, while still allowing this library to perform more complicated
     * management tasks given only a reference to the pixel data.
     */
    *((ManagedTexture_**)data) = newmtex;
    newmtex->pixelData = ((ManagedTexture_**)data) + 1;

    /* Insert the item into the linked list */
    if(managedTextures) {
        newmtex->next = managedTextures;
        managedTextures->prev = newmtex;
    }
    managedTextures = newmtex;


    return newmtex->pixelData;
}
