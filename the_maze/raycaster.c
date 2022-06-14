#include "maze.h"

Vector3f getTileCoordinateForVerticalRay(Vector3f* ray) 
{
    Vector3f pos = vectorAdd(&playerPos, ray);
    Vector3f coord;
    coord.x = (int)(pos.x + ((ray->x < 0) ? (-1 * RAY_EPS) : (RAY_EPS))) / WALL_SIZE;
    coord.y = (int)(pos.y + ((ray->y < 0) ? (-1 * EPS) : (EPS))) / WALL_SIZE;

    return coord;
}

Vector3f getTileCoordinateForHorizontalRay(Vector3f* ray) 
{
    Vector3f pos = vectorAdd(&playerPos, ray);
    Vector3f coord;
    coord.x = (int)(pos.x + ((ray->x < 0) ? (-1 * EPS) : EPS)) / WALL_SIZE;
    coord.y = (int)(pos.y + ((ray->y < 0) ? (-1 * RAY_EPS) : (RAY_EPS))) / WALL_SIZE;

    return coord;
}

void initRaycaster() 
{

    // Infer viewplane distance from a given field of view angle 
    distFromViewplane = (WINDOW_WIDTH / 2.0f) / (float)(tan(FOV / 2.0f));

    // Setup player rotation matrices 
    counterClockwiseRotation[0][0] = cos(PLAYER_ROT_SPEED);
    counterClockwiseRotation[0][1] = -1.0f * sin(PLAYER_ROT_SPEED);
    counterClockwiseRotation[1][0] = sin(PLAYER_ROT_SPEED);
    counterClockwiseRotation[1][1] = cos(PLAYER_ROT_SPEED);

    clockwiseRotation[0][0] = cos(-1.0f * PLAYER_ROT_SPEED);
    clockwiseRotation[0][1] = -1.0f * sin(-1.0f * PLAYER_ROT_SPEED);
    clockwiseRotation[1][0] = sin(-1.0f * PLAYER_ROT_SPEED);
    clockwiseRotation[1][1] = cos(-1.0f * PLAYER_ROT_SPEED);
}
