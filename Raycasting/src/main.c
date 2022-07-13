// includes
#include "main.h"


int screen_width = 1920;
int screen_height = 1080;

int drawincenter = 1080/2 - 100;

int QUALITY = ULTRA;


float dist(float x1, float y1, float x2, float y2){
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

float getScalingFactor(float x1, float y1, float x2, float y2){
    return dist(x1, y1, x2, y2) / (MAPSIZE * sqrt(2)  * BLOCK_SIZE);
}

int running;
int GameOption;

int main(){
    srand(time(NULL));

    running = 1;
    GameOption = MENU;

    SDL_ShowCursor(SDL_DISABLE);
    player.x = 700;
    player.y = 500;
    player.deltax = 0;
    player.deltay = 0;
    player.angle = pi/2;

    SpawnEnnemies(10);

    //writeMap(map);

    // read map
    readMap(map);

    printMap(map);

    BouclePrincipale();
}
