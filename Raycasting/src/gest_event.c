#include "gest_event.h"

int Keys[NB_KEYS];

// handles key presses and keys for oveent
void * gestInputOnTerrain(SDL_Renderer * renderer){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_z:
                            Keys[0] = 1;
                            continue;
                        case SDLK_d:
                            Keys[1] = 1;
                            continue;
                        case SDLK_s:
                            Keys[2] = 1;
                            continue;
                        case SDLK_q:
                            Keys[3] = 1;
                            // move left
                            continue;
                        default:
                            continue;
                    }
                    continue;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        Shoot();

                        currTime = SDL_GetTicks();
                        elapsedTime = (currTime - startTime) / 1000.0;
                        printf("%f\n", elapsedTime);


                    }
                    continue;
                // mouse movement
                case SDL_MOUSEMOTION:
                    // if mouse moved to right
                    if (event.motion.xrel > 0){
                        player.angle += 0.1 * SENSI;
                        if (player.angle > 2*pi) player.angle -= 2*pi;
                        player.deltax = cos(player.angle);
                        player.deltay = sin(player.angle);
                    }
                    // if mouse move to left
                    if (event.motion.xrel < 0){
                        player.angle -= 0.1 * SENSI;
                        if (player.angle < 0) {player.angle += 2*pi;}
                        player.deltax = cos(player.angle);
                        player.deltay = sin(player.angle);
                    }

                    // if mouse moved to up
                    if (event.motion.yrel > 0){
                        //drawincenter -= 250 * SENSI;
                    }
                    // if mouse moved to down
                    if (event.motion.yrel < 0){
                        //drawincenter += 250 * SENSI;
                    }
                    continue;

                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            GameOption = SETTINGS;
                            break;
                        case SDLK_z:
                            Keys[0] = 0;
                            continue;
                        case SDLK_d:
                            Keys[1] = 0;
                            continue;
                        case SDLK_s:
                            Keys[2] = 0;
                            continue;
                        case SDLK_q:
                            Keys[3] = 0;
                            continue;
                        case SDLK_x:
                            running = 0;
                        default:
                            continue;
                    }

                    continue;
            }
        }
    gestAll();
    SDL_Delay(5);
    return NULL;
}

// creates a Menu window
void * gestMenu(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
            switch(event.type)
            {   
                case SDL_MOUSEBUTTONUP:
                    GameOption = GAMERUNNING;
                    continue;

                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                        screen_height = event.window.data2;
                        screen_width = event.window.data1;
                    }
                    break;

                case SDL_QUIT:
                    running = 0;
                    break;
                
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_x:
                        running = 0;
                        continue;
                    
                    default:
                        continue;
                    }
                    break;

                default:
                    continue;
            }
    }
    SDL_Delay(5);
    return NULL;
}

int low_left_x = 0;

int medium_left_x = 0;

int high_left_x = 0;

int ultra_left_x = 0;

int button_y = 0;

int button_width = 0;
int button_height = 0;

// handles game settings command
void * gestSettings(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
            switch(event.type)
            {   
                default:
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    button_y = (screen_height * 260)/1080;

                    low_left_x = (screen_width * 610)/1920;
                    medium_left_x = (screen_width * 890)/1920;
                    high_left_x = (screen_width * 1200)/1920;
                    ultra_left_x = (screen_width * 1470)/1920;

                    button_width = (screen_width * 80)/1920;
                    button_height = (screen_width * 80)/1080;
                    if (event.button.x > low_left_x && event.button.x < low_left_x + button_width && event.button.y > button_y && event.button.y < button_y + button_height){
                        QUALITY = LOW;
                    }
                    else if (event.button.x > medium_left_x && event.button.x < medium_left_x + button_width && event.button.y > button_y && event.button.y < button_y + button_height){
                        QUALITY = MEDIUM;
                    }
                    else if (event.button.x > high_left_x && event.button.x < high_left_x + button_width && event.button.y > button_y && event.button.y < button_y + button_height){
                        QUALITY = HIGH;
                    }
                    else if (event.button.x > ultra_left_x && event.button.x < ultra_left_x + button_width && event.button.y > button_y && event.button.y < button_y + button_height){
                        QUALITY = ULTRA;
                    }
                    continue;

                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                        screen_height = event.window.data2;
                        screen_width = event.window.data1;
                    }
                    break;

                case SDL_QUIT:
                    running = 0;
                    break;
                
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_x:
                            running = 0;
                            continue;
                        
                        case SDLK_ESCAPE:
                            GameOption = GAMERUNNING;
                            continue;

                        default:
                            continue;
                    }
            }
    }
    SDL_Delay(5);
    return NULL;
}
