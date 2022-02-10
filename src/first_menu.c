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

void first_menu_options(SDL_Renderer *Renderer)
{
    SDL_Texture *start_txtr = IMG_LoadTexture(Renderer,"menu/start.png");
    SDL_Texture *start_hovered_txtr = IMG_LoadTexture(Renderer,"menu/start_hovered.png");
    SDL_Rect start_Rect = texture_position(start_txtr,TXR_CENTER,HEIGHT/2,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);

    SDL_Texture *exit_hovered_txtr = IMG_LoadTexture(Renderer,"menu/Exit_hovered.png");
    SDL_Texture *exit_txtr = IMG_LoadTexture(Renderer,"menu/Exit.png");
    SDL_Rect exit_Rect = texture_position(exit_txtr,TXR_CENTER,HEIGHT/2 +200,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
    SDL_Texture *texture = IMG_LoadTexture(Renderer,"menu/leaderboard.png");
    SDL_Rect rect = {.x = WIDTH/2-200 ,.y = HEIGHT/2+100 , .w = 400,.h = 75};
    
    if ((mouse_pos.x >= WIDTH/2-175 && mouse_pos.x <= WIDTH/2+175 && mouse_pos.y >= HEIGHT/2+20 && mouse_pos.y <= HEIGHT/2+60 ) || selected_option == 1)
    {
        SDL_RenderCopy(Renderer,start_hovered_txtr,NULL,&start_Rect);
        if (mouse_is_down || return_is_down)
        {
            Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
            Mix_PlayChannel(-1,sword,0);
            running[STG_FIRSTPAGE] = 0;
            running[STG_USERINPUT] = 1;
            stage = STG_USERINPUT;
        }
    }

    
    else if (mouse_pos.x >= WIDTH/2-175 && mouse_pos.x <= WIDTH/2+175 && mouse_pos.y >= HEIGHT/2+120 && mouse_pos.y <= HEIGHT/2+160 || selected_option == 2)
    {
        texture = IMG_LoadTexture(Renderer,"menu/leaderboard_hovered.png");
        if (mouse_is_down || return_is_down)
        {
            Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
            Mix_PlayChannel(-1,sword,0);
            mouse_is_down = 0;
            running[STG_LEADERBOARD] = 1;
            stage = STG_LEADERBOARD;
            running[STG_FIRSTPAGE] = 0;
            Mix_Quit();
        }
    }
    else if (mouse_pos.x >= WIDTH/2-175 && mouse_pos.x <= WIDTH/2+175 && mouse_pos.y >= HEIGHT/2+220 && mouse_pos.y <= HEIGHT/2+260 || selected_option == 3)
    {
        SDL_RenderCopy(Renderer,exit_hovered_txtr,NULL,&exit_Rect);
        if (mouse_is_down || return_is_down)
        {
            Mix_Chunk *leave = Mix_LoadWAV("music/leave.wav");
            Mix_PlayChannel(-1,leave,0);
            Mix_VolumeChunk(leave,128);
            SDL_Delay(1000);
            kill_program();
        }
    }
    SDL_RenderCopy(Renderer,texture,NULL,&rect);
    SDL_RenderCopy(Renderer,start_txtr,NULL,&start_Rect);
    SDL_RenderCopy(Renderer,exit_txtr,NULL,&exit_Rect);
    SDL_DestroyTexture(start_txtr);
    SDL_DestroyTexture(start_hovered_txtr);
    SDL_DestroyTexture(exit_txtr);
    SDL_DestroyTexture(exit_hovered_txtr);
}

void main_first_page(SDL_Window *window)
{
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    
    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    strcpy(BKG_PATH,"images/background/7.jpg");
    Mix_Music *background_music = Mix_LoadMUS("music/background.mp3");
    if (background_music == NULL)
    {
        printf("%s\n",SDL_GetError());
    }
    

    SDL_Texture *BKG_texture = IMG_LoadTexture(Renderer,BKG_PATH);
    SDL_Rect BKG_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
    Mix_PlayMusic(background_music,-1);

    while(running[STG_FIRSTPAGE])
	{
        frame++;
        if (frame == 8*FPS-1)frame =0;
        
        BKG_texture = dynamic_background(Renderer,BKG_texture,8,18);
        SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);
        
		handling(Renderer);
        first_menu_options(Renderer);
        sound_control(Renderer);
        mouse_cursor(Renderer);
        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS); 
        SDL_RenderClear(Renderer);
	}
    selected_option = -1;
    SDL_DestroyTexture(BKG_texture);
    BKG_texture = NULL;
    SDL_DestroyRenderer(Renderer);
    IMG_Quit();
    TTF_Quit();
}