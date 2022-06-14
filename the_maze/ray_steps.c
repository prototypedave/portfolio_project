#include "maze.h"


void extendRaysToFirstHit(RayTuple* rays) 
{
    int i;

    for(i = 0; i < VIEWPLANE_LENGTH; i++) {
        Vector3f perpVec = HOMOGENEOUS_V3;

        // Extend vertical ray 
        if(rays[i].vRay.x < 0) 
        { 
            // Ray is facing left 
            perpVec.x = ((int)(playerPos.x / (float)WALL_SIZE)) * WALL_SIZE - playerPos.x;
        } else 
        { 
            // Ray is facing right 
            perpVec.x = ((int)(playerPos.x / (float)WALL_SIZE)) * WALL_SIZE - playerPos.x + WALL_SIZE;
        }
        rays[i].vRay = homogeneousVectorScale(&rays[i].vRay, vectorDotProduct(&perpVec, &perpVec) / MAKE_FLOAT_NONZERO(vectorDotProduct(&perpVec, &rays[i].vRay)));

        // Extend horizontal ray 
        perpVec.x = 0.0f;
        if(rays[i].hRay.y < 0) 
        { 
            // Ray is facing up 
            perpVec.y = ((int)(playerPos.y / (float)WALL_SIZE)) * WALL_SIZE - playerPos.y;
        } else 
        {   
            //ray is facing down 
            perpVec.y = ((int)(playerPos.y / (float)WALL_SIZE)) * WALL_SIZE - playerPos.y + WALL_SIZE;
        }
        rays[i].hRay = homogeneousVectorScale(&rays[i].hRay, vectorDotProduct(&perpVec, &perpVec) / MAKE_FLOAT_NONZERO(vectorDotProduct(&perpVec, &rays[i].hRay)));
    }

}

Vector3f findVerticalRayStepVector(Vector3f* ray) {
    Vector3f stepVector = HOMOGENEOUS_V3;
    if(ray->x < 0) 
    { 
        // Ray is facing left 
        stepVector.x = -1 * WALL_SIZE;

    } else 
    { 
        //Ray is facing right 
        stepVector.x = WALL_SIZE;
    }

    return homogeneousVectorScale(ray, vectorDotProduct(&stepVector, &stepVector) / MAKE_FLOAT_NONZERO(vectorDotProduct(&stepVector, ray)));
}

Vector3f findHorizontalRayStepVector(Vector3f* ray) 
{
    Vector3f stepVector = HOMOGENEOUS_V3;
    if(ray->y < 0) 
    { 
        // Ray is facing up 
        stepVector.y = -1 * WALL_SIZE;

    } else 
    {
        // Ray is facing down 
        stepVector.y = WALL_SIZE;
    }

    return homogeneousVectorScale(ray, vectorDotProduct(&stepVector, &stepVector) / MAKE_FLOAT_NONZERO(vectorDotProduct(&stepVector, ray)));
}
