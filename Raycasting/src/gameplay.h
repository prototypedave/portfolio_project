#ifndef _GAMEPLAY_HEADER_
#define _GAMEPLAY_HEADER_

#include "main.h"
#include "gest_event.h"

typedef struct Bullet {
    float x;
    float y;
    float angle;
    float deltax;
    float deltay;
    float speed;
    struct Bullet * next;
} Bullet_t;

typedef struct Player {
    float x;
    float y;
    double angle;
    float deltax;
    float deltay;
    int shoot_timer;
    int isMoving;
    struct Bullet * bullet_list;
} Player_t;

typedef struct Ennemy {
    float x;
    float y;
    int hp;
    float angle;
    float deltax;
    float deltay;
    struct Ennemy * next;
} Ennemy_t;

extern Player_t player;
extern Ennemy_t * ennemy_head;


#define MV_SPEED (1)
#define BULLET_SPEED (200)
#define SHOOT_DELAY (10)

void gestMovement();
void Shoot();
void gestAll();
void printBulletList();
void initEnnemy();
void SpawnEnnemies(int n);
void DeleteBullet(Bullet_t * bullet);

#endif
