#include "maze.h"

// function to keep the game running
void runGame() 
{
    long gameTicks = 0;
    long time;

    do {
        time = SDL_GetTicks();

        /* Handle SDL key events */
        consumeSDLEvents();

        /* Update the player */
        updatePlayer();

        /* Update the raycaster */
        updateRaycaster();

        /* Render a frame */
        render();

        /* Fixed delay before next frame */
        SDL_Delay(10);

        /* Print FPS every 500 frames */
        if(!(gameTicks++ % 500))
            fprintf(stderr, "FPS: %.2f\n", 1000.0f / (float)(SDL_GetTicks() - time));
    } while(gameIsRunning);
}
