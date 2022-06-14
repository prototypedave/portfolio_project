#ifndef _MAZE_H_
#define _MAZE_H_

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#include <math.h>

/* Special settings */
#define ONLY_NORMALIZED 1
#define ONLY_FIRST_HIT 2

/* Misc. constants */
#define FALSE 0
#define TRUE  1
#define PI    3.14159265358979323846 /* C89 does not seem to define this constant */
#define EPS   0.00000001

/* Floating point operations */
#define MAKE_FLOAT_NONZERO(A)  ((fabs((A)) < EPS) ? EPS : A) /* Make any value less than epsilon equal to epsilon */

/* Window parameters*/
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

/* Raycaster parameters */
#define TEXTURE_SIZE           64
#define WALL_SIZE              64
#define HUD_MAP_SIZE           WINDOW_HEIGHT
#define FOV                    (PI / 3.0f)               /* 60 degrees */
#define PLAYER_MOVEMENT_SPEED  5.0f
#define PLAYER_ROT_SPEED       ((3.0f * (PI)) / 180.0f)  /* 3 degrees per frame */
#define PLAYER_SIZE            20

/* Projection parameters */
#define VIEWPLANE_LENGTH  WINDOW_WIDTH
#define VIEWPLANE_DIR_X  -1
#define VIEWPLANE_DIR_Y   0
#define PLAYER_DIR_X      0     /* Player direction must be perpendicular to viewplane */
#define PLAYER_DIR_Y      1
#define PLAYER_START_X    (2.5f * WALL_SIZE)
#define PLAYER_START_Y    (2.5f * WALL_SIZE)

/* Map constants */
#define MAP_GRID_WIDTH    10
#define MAP_GRID_HEIGHT   10
#define MAP_PIXEL_WIDTH   (MAP_GRID_WIDTH * WALL_SIZE)
#define MAP_PIXEL_HEIGHT  (MAP_GRID_HEIGHT * WALL_SIZE)

/* Map wall types */
#define P            -1  /* Player start */
#define R             1  /* Red wall */
#define G             2  /* Green wall */
#define B             3  /* Blue wall */
#define W             4  /* Gray wall */

#define CEILING_COLOR  RGBtoABGR(0x65, 0x65, 0x65)
#define FLOOR_COLOR    RGBtoABGR(0xAA, 0xAA, 0xAA)

/* math */
#define MIN(A, B)      ((A) < (B) ? (A) : (B))
#define MAX(A, B)      ((A) > (B) ? (A) : (B))

/* A 3D identity matrix */
#define IDENTITY_M     {{1,0,0},{0,1,0},{0,0,1}}

/* A 2D homogeneous matrix */
#define HOMOGENEOUS_V3 {0, 0, 1}

/* Macros */
#define XY_TO_SCREEN_INDEX(X, Y)   (((Y) * WINDOW_WIDTH) + (X))
#define XY_TO_TEXTURE_INDEX(X, Y)   (((Y) * TEXTURE_SIZE) + (X))
#define DARKEN_COLOR(C)     ((((C) >> 1) & 0x7F7F7F7F) | 0xFF000000)

/* Constants */
#define RAY_EPS   (WALL_SIZE / 3.0f)

//converts RGB colors to ABGR
#define RGBtoABGR(R,G,B)   (0xFF000000 | ((B) << 16) | ((G) << 8) | (R))

/* types */
typedef struct {
    float x;
    float y;
    float z;
} Vector3f;

typedef float Matrix3f[3][3];

/* Datatypes */
typedef struct {
    Vector3f vRay;
    Vector3f hRay;
} RayTuple;

/* Globals */
extern const short MAP[MAP_GRID_HEIGHT][MAP_GRID_WIDTH];
extern char distortion;
extern char textureMode;
extern Uint32* screenBuffer;
extern const Uint32 COLORS[];
extern Uint32* TEXTURES[];
extern char slowRenderMode;
extern char rayCastMode;

/* Global data */
extern Vector3f playerPos;
extern Vector3f playerDir;

/* Global toggles */
extern char movingForward;
extern char movingBack;
extern char turningLeft;
extern char turningRight;
extern char playerIsRunning;

/* Global data */
extern Vector3f viewplaneDir;
extern float distFromViewplane;
extern Matrix3f counterClockwiseRotation;
extern Matrix3f clockwiseRotation;
extern RayTuple rays[VIEWPLANE_LENGTH];

/* Enums */
typedef enum {HORIZONTAL_RAY, VERTICAL_RAY} RayType;

const char* gfxGetError();
int initGFX(char* title, unsigned int width, unsigned int height);
void* createTexture(unsigned int width, unsigned int height);
int destroyTexture(void* texture);
void displayFullscreenTexture(void* texture);
void destroyGFX();
void setDrawColor(int r, int g, int b, int a);
void drawLine(int x1, int y1, int x2, int y2);
void fillRect(int x, int y, int w, int h);
void drawRect(int x, int y, int w, int h);
void presentRenderer();
void clearRenderer();
Uint32* generateXorTexture(int size, int redmask, int greenmask, int bluemask);
Uint32* generateRedXorTexture(int size);
Uint32* generateGreenXorTexture(int size);
Uint32* generateBlueXorTexture(int size);
Uint32* generateGrayXorTexture(int size);
Vector3f vectorAdd(Vector3f* vec1, Vector3f* vec2);
Vector3f vectorSubtract(Vector3f* vec1, Vector3f* vec2);
Vector3f homogeneousVectorScale(Vector3f* vec, float scalar);
Vector3f normalizeVector(Vector3f* vec);
Vector3f vectorProjection(Vector3f* vec1, Vector3f* vec2);
float homogeneousVectorMagnitude(Vector3f* vec);
float vectorDotProduct(Vector3f* vec1, Vector3f* vec2);
void matrixVectorMultiply(Matrix3f* mat, Vector3f* vec);
void matrixMatrixMultiply(Matrix3f* mat1, Matrix3f* mat2);
void matrix3fCopy(Matrix3f* dst, Matrix3f* src);
void renderOverheadMap();
void initPlayer();
void updatePlayer();
void movePlayer(float dx, float dy);
int clipMovement(float dx, float dy);
float calculateDrawHeight(float rayLength);
void drawTexturedStrip(int x, float wallYStart, float length, int textureX, Uint32* texture, char darken);
void drawUntexturedStrip(int x, float wallYStart, float length, Uint32 ABGRColor, char darken);
int getTextureColumnNumberForRay(Vector3f* ray, RayType rtype);
float getUndistortedRayLength(Vector3f* ray);
void renderProjectedScene();
void initializeRayDirections();
void extendRaysToFirstHit(RayTuple* rays);
Vector3f findVerticalRayStepVector(Vector3f* ray);
Vector3f findHorizontalRayStepVector(Vector3f* ray);
void raycast(RayTuple* rays);
Vector3f getTileCoordinateForVerticalRay(Vector3f* ray);
Vector3f getTileCoordinateForHorizontalRay(Vector3f* ray);
void updateRaycaster();
void initRaycaster();

#endif /*_MAZE_H_ */
























