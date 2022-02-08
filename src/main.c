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
    stage = STG_INGAME;
    load_previous = 0;
    atc_num = 0;
    play_chunk = 1;
    explosion_num = 0;
    selected_option = 0;
    map_num = -2;
    win = 1;
    country_count = 0;
    player_count = 4;
    for (int i = 0; i < 7; i++)
    {
        running[i] = 1;
    }
    
    frame = 0;
}
int main() 
{
    init_global();
    srand(time(NULL)*1000);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	SDL_Window *window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
    HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_ShowCursor(0);

    while(running[STG_WHOLEGAME])
    {
        if (stage == STG_FIRSTPAGE)
        {
            main_first_page(Renderer);
        }
        else if (stage == STG_USERINPUT)
        {
            main_username(Renderer);
        }
        else if(stage == STG_SELECTMAP)
        {
            main_selectmap(Renderer);
        }
        else if (stage == STG_INGAME)
        {
            main_map(Renderer);
        }
        else if (stage == STG_LEADERBOARD)
        {
            leaderboeard_main(Renderer);
        }
        SDL_RenderClear(Renderer);
    }
    // SDL_DestroyTexture(Texture);
    SDL_DestroyTexture(mouse_texture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Renderer);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}