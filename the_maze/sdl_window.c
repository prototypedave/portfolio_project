#include "maze.h"

/**
 * setUpWindow - creates a screen for the game
 * x - x-axis
 $ y - y- axis

 * Retuen: TRUE
 */
int setupWindow() 
{
    int x, y;

    if(!initGFX("Raycaster", WINDOW_WIDTH, WINDOW_HEIGHT)) return FALSE;

    screenBuffer = createTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    redXorTexture = generateRedXorTexture(TEXTURE_SIZE);
    greenXorTexture = generateGreenXorTexture(TEXTURE_SIZE);
    blueXorTexture = generateBlueXorTexture(TEXTURE_SIZE);
    grayXorTexture = generateGrayXorTexture(TEXTURE_SIZE);
    TEXTURES[0] = redXorTexture;
    TEXTURES[1] = greenXorTexture;
    TEXTURES[2] = blueXorTexture;
    TEXTURES[3] = grayXorTexture;

    if(!screenBuffer) return FALSE;

    /* Make the texture initially gray */
    for(x = 0; x < WINDOW_WIDTH; x++)
        for(y = 0; y < WINDOW_HEIGHT; y++)
            screenBuffer[(WINDOW_WIDTH * y) + x] = 0xFFAAAAAA;

    return TRUE;
}

/**
 * main - initializes camera/ ray
 *
 * Return: Exit status
 */
int main() 
{
    if(!setupWindow()) 
    {
        fprintf(stderr, "Could not initialize raycaster!\n");
        return EXIT_FAILURE;
    }
    initPlayer();
    initRaycaster();
    runGame();

    destroyGFX();
    return EXIT_SUCCESS;
}
