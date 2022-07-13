#include "gameplay.h"

Player_t player;
Ennemy_t * ennemy_head;

/**
 * gestMovement - initiates movement of the player
 * x_increment: parameter for x axis
 * y_increment: parameter for y axis
 * newpos_x: parameter for the position after the movement on the x axis
 * newpos_y: position on the y axis after the movement
 */
void gestMovement(){
    float x_increment = (Keys[0] - Keys[2]) * player.deltax + (Keys [3] - Keys[1]) * sin(player.angle);
    float y_increment = (Keys[0] - Keys[2]) * player.deltay + (Keys[1] - Keys[3]) * cos(player.angle);
    float newpos_x = (player.x + + x_increment)/BLOCK_SIZE;
    float newpos_y = (player.y + y_increment)/BLOCK_SIZE;
    if (newpos_x >= 0 && newpos_x < MAPSIZE && newpos_y >= 0 && newpos_y < MAPSIZE){
        if (map[(int)newpos_y][(int)newpos_x] != 1){
            player.x += x_increment * MV_SPEED;
            player.y += y_increment * MV_SPEED;
            player.isMoving = 1;
        }
    }
    if (x_increment == 0 && y_increment == 0){
        player.isMoving = 0;
    }
}
// creates an enemy on the given postion x,y
void initEnnemy(Ennemy_t * ennemy, int x, int y){
    ennemy->x = x;
    ennemy->y = y;
    ennemy->angle = 0;
    ennemy->deltax = 0;
    ennemy->deltay = 0;
    ennemy->hp = 1;
}

void SpawnEnnemies(int n){
    for (int i = 0; i < n; i++){
        Ennemy_t * new_ennemy = (Ennemy_t *) malloc(sizeof(Ennemy_t));
        initEnnemy(new_ennemy, rand()% MAPSIZE * BLOCK_SIZE, rand()% MAPSIZE * BLOCK_SIZE);
        new_ennemy->next = ennemy_head;
        ennemy_head = new_ennemy;
    }
}

// controls enemy attack 
void Shoot(){
    if (player.shoot_timer == 0){
        player.shoot_timer = SHOOT_DELAY;
        Bullet_t * bullet = malloc(sizeof(Bullet_t));
        bullet->x = player.x;
        bullet->y = player.y;
        bullet->angle = player.angle;
        bullet->deltay = sin(player.angle);
        bullet->deltax = cos(player.angle);
        bullet->speed = BULLET_SPEED;
        bullet->next = NULL;
        if (player.bullet_list == NULL){
            player.bullet_list = bullet;
        }
        else {
            Bullet_t * tmp = player.bullet_list;
            // add to head of list
            player.bullet_list = bullet;
            bullet->next = tmp;
        }
    }
}

/**
 * checkHitEnemy - checks if the enemy was shot or attacked
 * Ennemy_t: given enemy and the location
 * Bullet_t: the bullet fired and the position fired to
 * Return: 0
 */
int checkHitEnnemy(Ennemy_t * ennemy, Bullet_t * bullet){
    int return_value = 0;
    if (dist(ennemy->x, ennemy->y, bullet->x, bullet->y) < BLOCK_SIZE/2){
        ennemy->hp--;
        if (ennemy->hp == 0){
            return_value = 1;
        }
    }
    return return_value;
}

// empties the gun after every shot taken
void DeleteBullet(Bullet_t * bullet){
    Bullet_t * curr = player.bullet_list;
    if (curr == bullet){
        player.bullet_list = curr->next;
        free(curr);
    }
    else {
        while (curr->next != bullet){
            curr = curr->next;
        }
        curr->next = bullet->next;
        free(bullet);
    }
}

// removes the enemy after he is dead
void DeleteEnnemy(Ennemy_t * ennemy){
    Ennemy_t * curr = ennemy_head;
    if (curr == ennemy){
        initEnnemy(curr, 0, 0);
    }
    else {
        while (curr->next != ennemy){
            curr = curr->next;
        }
        curr->next = ennemy->next;
        free(ennemy);
    }
}

void gestBullet(){
    Bullet_t * tmp = player.bullet_list;
    Bullet_t * prev = NULL;
    Ennemy_t * tmp_ennemy;
    while (tmp != NULL){
        tmp->x += tmp->deltax * tmp->speed;
        tmp->y += tmp->deltay * tmp->speed;
        tmp_ennemy = ennemy_head;
        while (tmp_ennemy != NULL){
            if (checkHitEnnemy(tmp_ennemy, tmp)){
                DeleteEnnemy(tmp_ennemy);
                break;
            }
            else {
                tmp_ennemy = tmp_ennemy->next;
            }
        }
        tmp = tmp->next;
    }
}


void updatePlayerShootTimer(){
    if (player.shoot_timer > 0){
        player.shoot_timer--;
    }
}


void printBulletList(){
    Bullet_t * tmp = player.bullet_list;
    while (tmp != NULL){
        printf("%f %f\n", tmp->x, tmp->y);
        tmp = tmp->next;
    }
}

void gestAll(){
    gestMovement();
    gestBullet();
    updatePlayerShootTimer();
}
