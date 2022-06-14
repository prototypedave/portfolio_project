#include "maze.h"

Uint32* generateXorTexture(int size, int redmask, int greenmask, int bluemask) 
{
    int x, y;
    float factor = 256.0f / (float)size;
    Uint32* texture = createTexture(size, size);

    for(x = 0; x < size; x++)
        for(y = 0; y < size; y++)
            texture[(size * y) + x] = RGBtoABGR((int)((x ^ y) * factor) & redmask, (int)((x ^ y) * factor) & greenmask, (int)((x ^ y) * factor) & bluemask);

    return texture;
}

Uint32* generateRedXorTexture(int size) 
{
    return generateXorTexture(size, 0xFF, 0x00, 0x00);
}

Uint32* generateGreenXorTexture(int size) 
{
    return generateXorTexture(size, 0x00, 0xFF, 0x00);
}

Uint32* generateBlueXorTexture(int size) 
{
    return generateXorTexture(size, 0x00, 0x00, 0xFF);
}

Uint32* generateGrayXorTexture(int size) 
{
    return generateXorTexture(size, 0xFF, 0xFF, 0xFF);
}
