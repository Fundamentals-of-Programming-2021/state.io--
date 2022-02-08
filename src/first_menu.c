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
    SDL_Texture *start_txtr = IMG_LoadTexture(Renderer,"menu/Start.bmp");
    SDL_Texture *start_hovered_txtr = IMG_LoadTexture(Renderer,"menu/start_hovered.bmp");
    SDL_Rect start_Rect = texture_position(start_txtr,TXR_CENTER,HEIGHT/2,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);

    SDL_Texture *exit_hovered_txtr = IMG_LoadTexture(Renderer,"menu/Exit_hovered.bmp");
    SDL_Texture *exit_txtr = IMG_LoadTexture(Renderer,"menu/Exit.bmp");
    SDL_Rect exit_Rect = texture_position(exit_txtr,TXR_CENTER,HEIGHT/2 +100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);

    if ((mouse_pos.x >= WIDTH/2-175 && mouse_pos.x <= WIDTH/2+175 && mouse_pos.y >= HEIGHT/2+20 && mouse_pos.y <= HEIGHT/2+60 ) || selected_option == 1)
    {
        SDL_RenderCopy(Renderer,start_hovered_txtr,NULL,&start_Rect);
        if (mouse_is_down || return_is_down)
        {
            running[STG_FIRSTPAGE] = 0;
            stage = STG_USERINPUT;
        }
    }
    
    else if (mouse_pos.x >= WIDTH/2-175 && mouse_pos.x <= WIDTH/2+175 && mouse_pos.y >= HEIGHT/2+120 && mouse_pos.y <= HEIGHT/2+160 || selected_option == 2)
    {
        SDL_RenderCopy(Renderer,exit_hovered_txtr,NULL,&exit_Rect);
        if (mouse_is_down || return_is_down)
        {
            kill_program();
        }
    }

    SDL_RenderCopy(Renderer,start_txtr,NULL,&start_Rect);
    SDL_RenderCopy(Renderer,exit_txtr,NULL,&exit_Rect);
    SDL_DestroyTexture(start_txtr);
    SDL_DestroyTexture(start_hovered_txtr);
    SDL_DestroyTexture(exit_txtr);
    SDL_DestroyTexture(exit_hovered_txtr);
}


void main_first_page(SDL_Renderer *Renderer)
{
    strcpy(BKG_PATH,"images/background/7.jpg");
    Mix_Music *background_music = Mix_LoadMUS("music/back ground.mp3");
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
}