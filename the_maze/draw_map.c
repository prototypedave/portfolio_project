#include "maze."

/**
 * render - displays worldmap of the gae
 *
 * Return: map
 */

void render() 
{
    if(showMap) 
    {
        clearRenderer();
        renderOverheadMap();
    } 
    else 
    { 
       /* Draw projected scene */
        renderProjectedScene();
    }
} 

