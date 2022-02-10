#ifndef __SELECT__MAP__
#define __SELECT__MAP__


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

void selectmap_show_options(SDL_Renderer *Renderer)
{
    rectangleColor(Renderer,200,300-100,500,400-100,0xffffffff);
    rectangleColor(Renderer,20,450-100,320,550-100,0xffffffff);
    rectangleColor(Renderer,380,450-100,680,550-100,0xffffffff);
    rectangleColor(Renderer,20,600-100,320,700-100,0xffffffff);
    rectangleColor(Renderer,380,600-100,680,700-100,0xffffffff);
    rectangleColor(Renderer,0,750,WIDTH,850,0xffffffff);
    SDL_Texture *options_texture;
    SDL_Rect options_rect;
    
    options_texture = text_texture(Renderer,"TA map",80,TXT_HANDWRITE,255,255,255,255);
    options_rect = texture_position(options_texture,20+20,450-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

    options_texture = text_texture(Renderer,"map 1",80,TXT_HANDWRITE,255,255,255,255);
    options_rect = texture_position(options_texture,380+50,450-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

    options_texture = text_texture(Renderer,"map 2",80,TXT_HANDWRITE,255,255,255,255);
    options_rect = texture_position(options_texture,20+50,600-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

    options_texture = text_texture(Renderer,"map 3",80,TXT_HANDWRITE,255,255,255,255);
    options_rect = texture_position(options_texture,380+50,600-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

    options_texture = IMG_LoadTexture(Renderer,"menu/new map.png");
    if ((mouse_pos.x >= 200 && mouse_pos.y >= 300-100 && mouse_pos.x <= 500 && mouse_pos.y <= 400-100) || map_num == -1)
    {
        options_texture = IMG_LoadTexture(Renderer,"menu/new map_hovered.png");
        if (mouse_is_down || return_is_down)
        {
            load_previous = 0;
            saved_map = 0;
            Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
            Mix_PlayChannel(-1,sword,0);
            running[STG_SELECTMAP] = 0;
            running[STG_INGAME] = 1;
            Mix_PauseMusic();
            stage = STG_INGAME;
        }
        
    }
    options_rect = texture_position(options_texture,200,300-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);    
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);
    
    options_texture = IMG_LoadTexture(Renderer,"menu/select map.png");
    if (return_is_down && map_num != -1)
    {
        options_texture = IMG_LoadTexture(Renderer,"menu/select map_hovered.png");
    }

    if ((mouse_pos.x >= 380 && mouse_pos.y >= 450-100 && mouse_pos.x <= 680 && mouse_pos.y <= 550-100) || map_num == 1)
    {
        rectangleColor(Renderer,380,450-100,680,550-100,0xffff11ff);
        if (mouse_is_down || return_is_down)
        {
            load_previous = 1;
            saved_map = 1;
            load_game("saves/saved_map 1");
            Mix_PauseMusic();
            running[STG_SELECTMAP] = 0;
            running[STG_INGAME] = 1;
            Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
            Mix_PlayChannel(-1,sword,0);
            stage = STG_INGAME;
        }
        
    }
    else if ((mouse_pos.x >= 20 && mouse_pos.y >= 450-100 && mouse_pos.x <= 350 && mouse_pos.y <= 550-100) || map_num == 0)
    {
        rectangleColor(Renderer,20,450-100,320,550-100,0xffff11ff);
        if (mouse_is_down || return_is_down)
        {
            load_previous = 1;
            saved_map =1;
            Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
            Mix_PlayChannel(-1,sword,0);

            load_game("saves/test_map");
            running[STG_SELECTMAP] = 0;
            stage = STG_INGAME;
            Mix_PauseMusic();

        }
    }
    else if ((mouse_pos.x >= 380 && mouse_pos.y >= 600-100 && mouse_pos.x <= 680 && mouse_pos.y <= 700-100) || map_num == 3)
    {
        rectangleColor(Renderer,380,600-100,680,700-100,0xffff11ff);
        if (mouse_is_down || return_is_down)
        {
            load_previous = 1;
            saved_map =1;
            Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
            Mix_PlayChannel(-1,sword,0);

            load_game("saves/saved_map 3");
            running[STG_SELECTMAP] = 0;
            stage = STG_INGAME;
            Mix_PauseMusic();

        }
    }
    else if ((mouse_pos.x >= 20 && mouse_pos.y >= 600-100 && mouse_pos.x <= 350 && mouse_pos.y <= 700-100) || map_num == 2)
    {
        rectangleColor(Renderer,20,600-100,320,700-100,0xffff11ff);
        if (mouse_is_down || return_is_down)
        {
            load_previous = 1;
            saved_map =1;
            Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
            Mix_PlayChannel(-1,sword,0);
            load_game("saves/saved_map 2");
            running[STG_SELECTMAP] = 0;
            stage = STG_INGAME;
            Mix_PauseMusic();

        }
    }
    options_rect = texture_position(options_texture,200,750,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);
    
    SDL_DestroyTexture(options_texture);

}

int main_selectmap(SDL_Window *window)
{
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    strcpy(BKG_PATH,"images/background/1.jpg");
    SDL_Texture *BKG_texture = IMG_LoadTexture(Renderer,BKG_PATH);
    SDL_Rect BKG_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    while(running[STG_SELECTMAP])
	{
        frame++;
        if (frame == 8*FPS-1) frame = 0;

        BKG_texture = dynamic_background(Renderer,BKG_texture,8,18);
        
        SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);
        sound_control(Renderer);

        
        selectmap_show_options(Renderer);
		handling(Renderer);
        
        mouse_cursor(Renderer);

        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS); 
        SDL_RenderClear(Renderer);

	}
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyTexture(BKG_texture);
    BKG_texture = NULL;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}


#endif // !__SELECT__MAP__