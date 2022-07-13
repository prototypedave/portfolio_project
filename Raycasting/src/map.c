#include "map.h"


// declare 50x50 matrix with only 1s and 0s
int map[50][50];

// write map to map.txt
void writeMap(int map[][MAPSIZE])
{
    FILE *fp;
    fp = fopen("map.txt", "w");
    for(int i = 0; i < MAPSIZE; i++)
    {
        for(int j = 0; j < MAPSIZE; j++)
        {
            fprintf(fp, "%d ", map[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

// read map from map.txt
void readMap(int map[][MAPSIZE])
{
    FILE *fp;
    fp = fopen("map.txt", "r");
    for(int i = 0; i < MAPSIZE; i++)
    {
        for(int j = 0; j < MAPSIZE; j++)
        {
            fscanf(fp, "%d", &map[i][j]);
        }
    }
    fclose(fp);
}

// function to generate map
void generateMap(int map[MAPSIZE][MAPSIZE]) {
    // generate map
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            map[i][j] = rand() % 2;
        }
    }
    map[0][0] = 0;
}

// function to print map
void printMap(int map[MAPSIZE][MAPSIZE]){
    // print map
    int pos_x = player.x/BLOCK_SIZE;
    int pos_y = player.y/BLOCK_SIZE;
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            if (j == pos_x && i == pos_y){
                printf("P ");
            }
            else{
                printf("%d ", map[i][j]);
            }
        }
        printf("\n");
    }
}
