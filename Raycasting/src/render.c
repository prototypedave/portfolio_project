#include "render.h"

/**
 * Handles SDL2
 * Uses Raycasting to render 3D
 */

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;


int startTime = 0;
int currTime = 0;
double elapsedTime = 0;


int Window_Height;
int Window_Width;

int DrawHitEffect = 0;

TTF_Font *RobotoFont;

SDL_Color Color = {255, 255, 255};

SDL_Rect rect;
SDL_Rect ground;
SDL_Rect sky;

// ennemy texture and surface
SDL_Texture *EnnemyTexture = NULL;
SDL_Surface *EnnemySurface = NULL;

SDL_Surface *WallSurface = NULL;
SDL_Texture *WallTexture = NULL;

SDL_Surface *GameName = NULL;
SDL_Texture *GameNameTexture = NULL;

SDL_Surface *SettingsSurface = NULL;
SDL_Texture *SettingsTexture = NULL;

SDL_Surface *XSurface = NULL;
SDL_Texture *XTexture = NULL;

SDL_Surface *CircleSurface = NULL;
SDL_Texture *CircleTexture = NULL;

SDL_Surface *POVSurface = NULL;
SDL_Texture *POVTexture = NULL;

// Initiates game window surface
void CreateWindow(){
    SDL_DisplayMode ScreenDimension;

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Couldn't create window.");
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &ScreenDimension);

    window = SDL_CreateWindow("Explorateur 3000", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenDimension.w, ScreenDimension.h, SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == NULL){
        printf("Couldn't create window");
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL){
        printf("Couldn't create renderer.");
        exit(EXIT_FAILURE);
    }


    if (TTF_Init() == -1)
    {
        exit(EXIT_FAILURE);
    }


    RobotoFont = TTF_OpenFont("Res/Roboto-Black.ttf", 50);

    SDL_GetWindowSize(window, &screen_width, &screen_height);
}

// creates a player in the given map position
void drawRay(Player_t * player, int map[MAPSIZE][MAPSIZE], SDL_Renderer *renderer){
    float htexture;
    int r, mx, my, dof;
    double rx, ry, xo, yo, distT;
    double ra = player->angle - DR * FOV_ANGLE/4;
    if (ra < 0) ra += 2*pi;
    if (ra > 2*pi) ra -= 2*pi;
    for (r = 0; r<NB_RAYS; r++){
        // check horizontal line
        
        dof = 0;
        float disH=100000, hx = player->x, hy = player->y;
        float aTan = -1/tan(ra);
        if (ra>pi){ // looking up
            ry = (((int)player->y>>6)<<6) - 0.0001;
            rx = (player->y - ry) * aTan + player->x;
            yo = -BLOCK_SIZE;
            xo = -yo*aTan;
        }
        if (ra<pi){ // looking down
            ry = (((int)player->y>>6)<<6) + BLOCK_SIZE;
            rx = (player->y - ry) * aTan + player->x;
            yo = BLOCK_SIZE;
            xo = -yo*aTan;
        }
        if (ra==pi){ // looking horizontal
            ry = player->y;
            rx = player->x;
            dof = DOF;
        }
        while (dof < DOF){
            mx = (int)rx>>6;
            my = (int)ry>>6;
            if (mx>=0 && mx<MAPSIZE && my>=0 && my<MAPSIZE && map[my][mx]==1){ 
                hx = rx;
                hy = ry;
                disH = dist(player->x, player->y, hx, hy);
                dof = DOF;
            }
            else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        

        // check vertical line
        dof = 0;
        float disV=100000, vx = player->x, vy = player->y;
        float nTan = -tan(ra);
        if (ra>pi2 && ra < pi3){ // looking left
            rx = (((int)player->x>>6)<<6) - 0.0001;
            ry = (player->x - rx) * nTan + player->y;
            xo = -BLOCK_SIZE;
            yo = -xo*nTan;
        }
        if (ra<pi2 || ra>pi3){ // looking right
            rx = (((int)player->x>>6)<<6) + BLOCK_SIZE;
            ry = (player->x - rx) * nTan + player->y;
            xo = BLOCK_SIZE;
            yo = -xo*nTan;
        }
        if (ra==pi || ra == 0){ // looking horizontal
            ry = player->y;
            rx = player->x;
            dof = DOF;
        }
        while (dof < DOF){
            mx = (int)rx>>6;
            my = (int)ry>>6;
            if (mx>=0 && mx<MAPSIZE && my>=0 && my<MAPSIZE && map[my][mx]==1){
                vx = rx;
                vy = ry;
                disV = dist(player->x, player->y, vx, vy);
                dof = DOF;
            }
            else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        if (disH<disV){
            rx = hx;
            ry = hy;
            distT = disH;
        }
        else {
            rx = vx;
            ry = vy;
            distT = disV;
        }
        ra = ra + ANGLE_INC/2;
        if (ra < 0) ra += 2*pi;
        if (ra > 2*pi) ra -= 2*pi;

        // draw collumn
        float ca = player->angle - ra;
        if (ca < 0) ca += 2*pi;
        if (ca > 2*pi) ca -= 2*pi;
        distT = distT * cos(ca);
        float lineH = (15 * screen_height) / distT;
        float factor = getScalingFactor(player->x, player->y, rx, ry);

        int width = QUALITY;

        rect.x = r * width;
        rect.y = drawincenter - (int)lineH;
        rect.w = width;
        rect.h = (int)(2 * screen_height * lineH/200);
        // draw rect
        if (disH < disV){
            SDL_SetTextureColorMod(WallTexture, 255 * (1 - factor), 255 * (1 - factor), 255 * (1 - factor));
            htexture = (int)(rx)%BLOCK_SIZE;
            //SDL_SetRenderDrawColor(renderer, 255 * (1 - factor), 255 * (1 - factor), 255 * (1 - factor) , 255);
        }
        else {
            //SDL_SetRenderDrawColor(renderer, 155 * (1 - factor), 155 * (1 - factor), 155 * (1 - factor) , 255);
            htexture = (int)(ry)%BLOCK_SIZE;
            SDL_SetTextureColorMod(WallTexture, 150 * (1 - factor), 150 * (1 - factor), 150 * (1 - factor));
        }
        SDL_Rect dstrect = {htexture,0,1,100};
        SDL_RenderCopy(renderer, WallTexture, &dstrect, &rect);

        //SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        //SDL_RenderDrawLine(renderer, player->x, player->y, rx, ry);


        //SDL_RenderFillRect(renderer, &rect);


    }
}

// creates a fired bullet on the screen
void drawBullet(Bullet_t * bullet, SDL_Renderer *renderer){
    Bullet_t * b = bullet;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    while (b != NULL){
        SDL_Rect rect = {b->x, b->y, 1, 1};
        SDL_RenderFillRect(renderer, &rect);
        b = b->next;
    }
}


// draw crosshair
void drawCrosshair(Player_t * player, SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, screen_width/2, screen_height/2-10, screen_width/2, screen_height/2 + 10);
    SDL_RenderDrawLine(renderer, screen_width/2-10, screen_height/2, screen_width/2 + 10, screen_height/2);
}


// draw ennemy 
void drawEnnemyonMap(Ennemy_t * ennemy, Player_t * player, SDL_Renderer *renderer){
    float ennemy_angle = atan2(ennemy->y - player->y, ennemy->x - player->x);
    float ennemy_dist = dist(ennemy->x, ennemy->y, player->x, player->y);
    if (ennemy_angle < 0) ennemy_angle += 2*pi;
    if (ennemy_angle > 2*pi) ennemy_angle -= 2*pi;
    if (ennemy_angle >= player->angle - 30 * DR && ennemy_angle <= player->angle + 30 * DR){
        // draw ennemy
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect rect = {ennemy->x - ennemy_dist * cos(ennemy_angle), ennemy->y - ennemy_dist * sin(ennemy_angle), 10, 10};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void drawEnnemy(Ennemy_t * ennemy, Player_t * player, SDL_Renderer *renderer){
    int sens = 1;
    float ennemy_angle = atan2(ennemy->y - player->y, ennemy->x - player->x);
    if (ennemy_angle < 0) ennemy_angle += 2*pi;
    if (ennemy_angle > 2*pi) ennemy_angle -= 2*pi;
    float ennemy_dist = dist(ennemy->x, ennemy->y, player->x, player->y);
    float ennemy_dist_x;
    float ennemy_dist_y  = ennemy_dist * fabs(sin(ennemy_angle - player->angle));
    int ennemy_width = 20;
    float tot;
    
    ennemy_dist_x = ennemy_dist * cos(ennemy_angle - player->angle);

    tot = sqrt(3) * ennemy_dist_x;
    
    float base_triangle = 2 * ennemy_dist_x / sqrt(3);

    if (ennemy_angle >= player->angle - FOV_ANGLE/2 * DR && ennemy_angle <= player->angle + FOV_ANGLE/2 * DR){
        if (ennemy_angle < player->angle){
            sens = -1;
        }
        float ennemy_length = 3 * (10 * screen_height) / ennemy_dist_x;
        float draw_width = 5 * ennemy_width * screen_width / tot;
        float draw_y =  drawincenter - MAPSIZE * ennemy_dist/100000;

        //SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect rect = {screen_width/2 + sens * (screen_width * 2 * ennemy_dist_y)/base_triangle - draw_width/2, draw_y, draw_width, 2.5 * 3 *ennemy_length};
        //SDL_RenderFillRect(renderer, &rect);
        SDL_RenderCopy(renderer, EnnemyTexture, NULL, &rect);
    }
}


void drawBullet2(Bullet_t * b, Player_t * player, SDL_Renderer *renderer){
    int sens = 1;
    float ennemy_angle = atan2(b->y - player->y, b->x - player->x);
    if (ennemy_angle < 0) ennemy_angle += 2*pi;
    if (ennemy_angle > 2*pi) ennemy_angle -= 2*pi;
    float ennemy_dist = dist(b->x, b->y, player->x, player->y);
    float ennemy_dist_x;
    float ennemy_dist_y  = ennemy_dist * fabs(sin(ennemy_angle - player->angle));
    int ennemy_width = 20;
    float tot;
    
    ennemy_dist_x = ennemy_dist * cos(ennemy_angle - player->angle);

    tot = sqrt(3) * ennemy_dist_x;
    
    float base_triangle = 2 * ennemy_dist_x / sqrt(3);

    if (ennemy_angle >= player->angle - FOV_ANGLE/2 * DR && ennemy_angle <= player->angle + FOV_ANGLE/2 * DR){
        if (ennemy_angle < player->angle){
            sens = -1;
        }
        float ennemy_length = 9 * (10 * screen_height) / ennemy_dist_x;
        float draw_width = ennemy_width * screen_width / tot;
        float draw_y =  drawincenter - MAPSIZE * ennemy_dist/100000;

        if (ennemy_length < 10) {
           // DeleteBullet(b);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect = {screen_width/2 + sens * (screen_width * 2 * ennemy_dist_y)/base_triangle, draw_y, 5 * draw_width, ennemy_length};
        SDL_RenderFillRect(renderer, &rect);
        //SDL_RenderCopy(renderer, EnnemyTexture, NULL, &rect);
    }
}

// function to draw the map
void drawMap(int map[MAPSIZE][MAPSIZE], SDL_Renderer *renderer){
    // draw map
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            if (map[i][j] == 1){
                SDL_Rect rect = {j*BLOCK_SIZE/MAPSIZE, i*BLOCK_SIZE/MAPSIZE, BLOCK_SIZE/MAPSIZE, BLOCK_SIZE/MAPSIZE};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
                    // draw player
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = {player.x, player.y, 10, 10};
    SDL_RenderFillRect(renderer, &rect);

        // draw ennemy
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect2 = {ennemy_head->x, ennemy_head->y, 10, 10};
    SDL_RenderFillRect(renderer, &rect2);

} 

void DrawFPS(float fps){
    char ScoreString[10];
    sprintf(ScoreString,"%d",(int)fps);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(RobotoFont, ScoreString, Color); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.w = 100;
    Message_rect.h = 100;
    Message_rect.x = 0; 
    Message_rect.y = 0;  
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}

void AffichageMenu(){
    SDL_RenderCopy(renderer, GameNameTexture , NULL, NULL);
    SDL_RenderPresent(renderer);
}

void drawX(){
    int button_y = (screen_height * 260)/1080;
    int button_width = (screen_width * 80)/1920;
    int button_height = (screen_width * 40)/1080;
    switch (QUALITY)
    {
        case LOW:
            rect.x = (screen_width * 610)/1920;
            rect.y = button_y;
            rect.h = button_height;
            rect.w = button_width;
            break;
        case MEDIUM:
            rect.x = (screen_width * 890)/1920;
            rect.y = button_y;
            rect.h = button_height;
            rect.w = button_width;
            break;
        
        case HIGH:
            rect.x = (screen_width * 1200)/1920;
            rect.y = button_y;
            rect.h = button_height;
            rect.w = button_width;
            break;
        
        case ULTRA:
            rect.x = (screen_width * 1470)/1920;
            rect.y = button_y;
            rect.h = button_height;
            rect.w = button_width;
            break;
    }
    
    SDL_RenderCopy(renderer, XTexture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

void AffichageSettings(){
    SDL_RenderCopy(renderer, SettingsTexture , NULL, NULL);
    drawX(0,0,0,0);
    SDL_RenderPresent(renderer);
}

void drawSkyGround(){
            // draw ground
        SDL_SetRenderDrawColor(renderer, 50, 55, 0, 255);
        ground.x = 0;
        ground.y = 0;
        ground.w = screen_width;
        ground.h = screen_height;
        SDL_RenderFillRect(renderer, &ground);
                // draw sky
        SDL_SetRenderDrawColor(renderer, 50, 55, 255, 255);
        sky.x = 0;
        sky.y = 0;
        sky.w = screen_width;
        sky.h = drawincenter;
        SDL_RenderFillRect(renderer, &sky);
}

void drawPOVHands(){
    // if player is moving
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 20;
    rect.w = screen_width;
    rect.h = screen_height;
    if (player.isMoving){
        rect.y = 0;
    }
    SDL_RenderCopy(renderer, POVTexture, NULL, &rect);
}

void AffichageNormal(float fps){
    Bullet_t *b = player.bullet_list;
    Ennemy_t *e = ennemy_head;
    SDL_RenderClear(renderer);

    drawSkyGround();
    drawRay(&player, map, renderer);
    while (e != NULL){
        drawEnnemy(e, &player, renderer);
        e = e->next;
    }

    drawCrosshair(&player, renderer);
    DrawFPS(fps);

    while (b != NULL){
        drawBullet2(b, &player, renderer);
        b = b->next;
    }

    //drawMap(map, renderer);
    drawPOVHands();
    SDL_RenderPresent(renderer);
}

void *BoucleGestInput(void *arg){
    while(running){
      switch(GameOption){
          case GAMERUNNING : gestInputOnTerrain(renderer);break;
          case MENU : gestMenu();break;
          case SETTINGS : gestSettings();break;
          case END_SCREEN : gestMenu();break;
          default:printf("game option fault");break;
      }
    }
    return NULL;
}

// loads the provided resources in the res directory
int BouclePrincipale(){
    CreateWindow();

    EnnemySurface = IMG_Load("Res/character.png");
    WallSurface = IMG_Load("Res/texture2.png");
    GameName = IMG_Load("Res/GreenHoleMain.png");
    SettingsSurface = IMG_Load("Res/Menu.png");
    XSurface = IMG_Load("Res/X.png");
    CircleSurface = IMG_Load("Res/shadow.png");
    POVSurface = IMG_Load("Res/hands.png");

    EnnemyTexture = SDL_CreateTextureFromSurface(renderer, EnnemySurface);
    WallTexture = SDL_CreateTextureFromSurface(renderer, WallSurface);
    GameNameTexture = SDL_CreateTextureFromSurface(renderer, GameName);
    SettingsTexture = SDL_CreateTextureFromSurface(renderer, SettingsSurface);
    XTexture = SDL_CreateTextureFromSurface(renderer, XSurface);
    CircleTexture = SDL_CreateTextureFromSurface(renderer, CircleSurface);
    POVTexture = SDL_CreateTextureFromSurface(renderer, POVSurface);

    SDL_FreeSurface(EnnemySurface);
    SDL_FreeSurface(WallSurface);
    SDL_FreeSurface(GameName);
    SDL_FreeSurface(SettingsSurface);
    SDL_FreeSurface(XSurface);
    SDL_FreeSurface(CircleSurface);
    SDL_FreeSurface(POVSurface);
    
    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;


    pthread_t threadGest;
    int RetourDuThreadGest = pthread_create(&threadGest, NULL, BoucleGestInput, NULL);
    if (RetourDuThreadGest){
        return 1;
    }

    //GameOption = ON_MAP;

    startTime = SDL_GetTicks();

    while (running)
    {
        currTime = SDL_GetTicks();
        elapsedTime = (currTime - startTime) / 1000.0;
        a = SDL_GetTicks();
        delta = a - b;
        if (delta > FPS_TO_GET){
            //printf("fps : %f\n", 1000/delta);
            b = a;
            switch (GameOption)
            {
                case GAMERUNNING:
                    AffichageNormal(1000/delta);
                    break;

                case MENU:
                    AffichageMenu();
                    break;

                case SETTINGS:
                    AffichageSettings();
                    break;

                case END_SCREEN:
                    //AffichageEnd();
                    break;

                default:
                    //printf("gameoption fault");
                    exit(EXIT_FAILURE);
            }
        }
        else{

            // sleep the thread
            usleep(1000 * (FPS_TO_GET - delta));
        } 

    }
    SDL_DestroyTexture(GameNameTexture);
    SDL_DestroyTexture(WallTexture);
    SDL_DestroyTexture(EnnemyTexture);
    SDL_DestroyTexture(SettingsTexture);
    SDL_DestroyTexture(XTexture);
    SDL_DestroyTexture(CircleTexture);
    return 0;
}
