#include "maze.h"

/* Globals */
Vector3f viewplaneDir = {VIEWPLANE_DIR_X, VIEWPLANE_DIR_Y, 1};
float distFromViewplane;
Matrix3f counterClockwiseRotation = IDENTITY_M;
Matrix3f clockwiseRotation = IDENTITY_M;
RayTuple rays[VIEWPLANE_LENGTH];

/**
*initializeRayDirections - gets the direction the player is facing
*
*Return: direction
*/
void initializeRayDirections() 
{
    int i;
    Vector3f v1,v2,v3;

    for(i = 0; i < VIEWPLANE_LENGTH; i++) 
    {
        v1 = homogeneousVectorScale(&playerDir, distFromViewplane);
        v2 = homogeneousVectorScale(&viewplaneDir, ((VIEWPLANE_LENGTH / 2) - i));
        v3 = vectorSubtract(&v1, &v2);
        rays[i].hRay = normalizeVector(&v3);
        rays[i].vRay = normalizeVector(&v3);

        if (rayCastMode == ONLY_NORMALIZED) 
        {
            rays[i].hRay = homogeneousVectorScale(&rays[i].hRay, 40);
            rays[i].vRay = homogeneousVectorScale(&rays[i].vRay, 40);
        }
    }
}
