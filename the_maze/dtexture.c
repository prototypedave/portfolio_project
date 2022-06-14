#include "maze.h"

/**
* destroyTexture - destroys the current texture
*
* Return: 1 on success, 0 on failure
*/
int destroyTexture(void* ptr) 
{
    /* Recover the memory management structure before freeing anything */
    ManagedTexture_* mtex = *(((ManagedTexture_**)ptr) - 1);

    /* Don't do anything if it's not actually a managed structure */
    if(mtex->magicTag != TEX_TAG) 
    {
        gfxSetError("Not a valid texture pointer", 0);
        return 0;
    }

    /* Prevent this structure from being somehow sent here again */
    mtex->magicTag = 0;

    /* Actual cleanup */
    free(((ManagedTexture_**)ptr) - 1);

    SDL_DestroyTexture(mtex->texture);

    if(mtex->prev) mtex->prev->next = mtex->next;
    if(mtex->next) mtex->next->prev = mtex->prev;
    if(managedTextures == mtex) managedTextures = mtex->next;
    free(mtex);

    return 1;
}

void displayFullscreenTexture(void* texture) 
{
    ManagedTexture_* mtex;

    if(!window || !renderer) {
        gfxSetError("SDL window has not been initialized yet", 0);
        return;
    }

    // Recover the managed texture structure 
    mtex = *(((ManagedTexture_**)texture) - 1);

    // Don't do anything if it's not actually a managed texture 
    if(mtex->magicTag != TEX_TAG) {
        gfxSetError("Not a valid texture pointer", 0);
        return;
    }

    SDL_UpdateTexture(mtex->texture, NULL, mtex->pixelData, mtex->pitch);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, mtex->texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}


void destroyGFX() {
    // Destroy all allocated textures 
    while(managedTextures) destroyTexture(managedTextures->pixelData);

    // Clean everything else up 
    if(window && renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        SDL_DestroyWindow(window);
        window = NULL;

        SDL_Quit();
    }
}
