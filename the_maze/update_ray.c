#include "maze.h"

void raycast(RayTuple* rays) 
{
    int i;

    for(i = 0; i < VIEWPLANE_LENGTH; i++) 
    {
        Vector3f vnorm = normalizeVector(&rays[i].vRay);
        Vector3f hnorm = normalizeVector(&rays[i].hRay);
        Vector3f vstep = findVerticalRayStepVector(&vnorm);
        Vector3f hstep = findHorizontalRayStepVector(&hnorm);
        Vector3f mapCoord;

        // Cast the vertical ray until it hits something 
        mapCoord = getTileCoordinateForVerticalRay(&rays[i].vRay);
        while(mapCoord.x > 0 && mapCoord.y > 0 && mapCoord.x < MAP_GRID_WIDTH && mapCoord.y < MAP_GRID_HEIGHT && MAP[(int)mapCoord.y][(int)mapCoord.x] < 1) 
        {
            rays[i].vRay = vectorAdd(&rays[i].vRay, &vstep);
            mapCoord = getTileCoordinateForVerticalRay(&rays[i].vRay);
        }

        // Cast the horizontal ray until it hits something 
        mapCoord = getTileCoordinateForHorizontalRay(&rays[i].hRay);
        while(mapCoord.x > 0 && mapCoord.y > 0 && mapCoord.x < MAP_GRID_WIDTH && mapCoord.y < MAP_GRID_HEIGHT && MAP[(int)mapCoord.y][(int)mapCoord.x] < 1) 
        {
            rays[i].hRay = vectorAdd(&rays[i].hRay, &hstep);
            mapCoord = getTileCoordinateForHorizontalRay(&rays[i].hRay);
        }
    }
}

void updateRaycaster() 
{
    // Update the rays 
    initializeRayDirections();

    if (rayCastMode == ONLY_NORMALIZED)
        return;

    // Extend the rays to their first hits 
    extendRaysToFirstHit(rays);
    if (rayCastMode == ONLY_FIRST_HIT)
        return;

    // Perform raycasting 
    raycast(rays);

}

