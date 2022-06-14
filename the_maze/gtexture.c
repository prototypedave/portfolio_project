#include "maze.h"

/* Used to identify a texture structure in memory */
#define TEX_TAG 0x55AA

/* Error string buffer */
char errstr[256];

/*
 * SDL textures are stored in VRAM, so we need to manage
 * a RAM-persistent copy of the texture's pixel data that we
 * can write to. Allocated textures are stored in a linked
 * list so we can keep track of them all easily.
 */
typedef struct ManagedTexture_ ManagedTexture_;
struct ManagedTexture_ 
{
    void* pixelData; // RAM copy of the texture 
    SDL_Texture* texture;
    Uint32 pitch;
    ManagedTexture_* next;
    ManagedTexture_* prev;
    Uint16 magicTag;
};
ManagedTexture_* managedTextures = NULL;

// SDL Stuff 
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

unsigned int screenWidth  = -1;
unsigned int screenHeight = -1;

/**
 * debug function
 *
 * Return: error
 */

const char* gfxGetError() 
{
    return errstr;
}

void gfxSetError(char* str, char showSdlErr) 
{
    if(showSdlErr)
        sprintf(errstr, "%s: %s", str, SDL_GetError());
    else
        sprintf(errstr, "%s", str);
}

