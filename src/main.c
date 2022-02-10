#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "state_io.h"

void init_global()
{
    STATECOUNT.x = 7;
    STATECOUNT.y = 8;
    mouse_is_down = 0;
    saved_map =0;
    return_is_down = 0;
    stage = STG_FIRSTPAGE;
    load_previous = 0;
    atc_num = 0;
    play_chunk = 1;
    explosion_num = 0;
    selected_option = 0;
    map_num = -2;
    win = 1;
    country_count = 0;
    player_count = rand()%3+2;
    for (int i = 0; i < 7; i++)
    {
        running[i] = 1;
    }
    
    frame = 0;
}

int main() 
{
    srand(time(NULL)*1000);

    init_global();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_Window *window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
    HEIGHT, SDL_WINDOW_OPENGL);
    SDL_ShowCursor(0);

    while(running[STG_WHOLEGAME])
    {
        if (stage == STG_FIRSTPAGE)
        {
            main_first_page(window);
        }
        else if (stage == STG_USERINPUT)
        {
            main_username(window);
        }
        else if(stage == STG_SELECTMAP)
        {
            main_selectmap(window);
        }
        else if (stage == STG_INGAME)
        {
            main_map(window);
        }
        else if (stage == STG_LEADERBOARD)
        {
            leaderboeard_main(window);
        }
    }
    // SDL_DestroyTexture(Texture);
    SDL_DestroyTexture(mouse_texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}