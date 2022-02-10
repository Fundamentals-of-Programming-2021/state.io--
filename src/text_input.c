#ifndef __TEXT__INPUT__
#define __TEXT__INPUT__

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

void textinput_show_options(SDL_Renderer *Renderer)
{
    rectangleColor(Renderer,20,650,320,750,0xffffffff);
    rectangleColor(Renderer,380,650,680,750,0xffffffff);
    // rectangleColor(Renderer,200,780,500,880,0xffffffff);
    SDL_Texture *options_texture;
    SDL_Rect options_rect;

    options_texture = IMG_LoadTexture(Renderer,"menu/new game.png");
    if ((mouse_pos.x >= 20 && mouse_pos.y >= 650 && mouse_pos.x <= 320 && mouse_pos.y <= 750 )|| selected_option == 0)
    {
        options_texture = IMG_LoadTexture(Renderer,"menu/new game_hovered.png");
        if ((mouse_is_down || return_is_down ) )
        {
            if (strlen(user_name) != 0)
            {
                Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
                Mix_PlayChannel(-1,sword,0);
                load_previous = 0;
                running[STG_USERINPUT] = 0;
                stage = STG_SELECTMAP;
            }
        }
    }
    options_rect = texture_position(options_texture,20,650,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);    
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);


    options_texture = IMG_LoadTexture(Renderer,"menu/load game.png");    
    if ((mouse_pos.x >= 380 && mouse_pos.y >= 650 && mouse_pos.x <= 680 && mouse_pos.y <= 750) ||  selected_option == 1)
    {
        options_texture = IMG_LoadTexture(Renderer,"menu/load game_hovered.png");
        if ((mouse_is_down || return_is_down) && is_any_load())
        {
            if (strlen(user_name) != 0)
            {
                Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
                Mix_PlayChannel(-1,sword,0);
                load_previous = 1;
                running[STG_USERINPUT] = 0;
                running[STG_INGAME] = 1;
                Mix_PauseMusic();
                stage = STG_INGAME;
            }
        }        
    }
    options_rect = texture_position(options_texture,380,650,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);
    
    SDL_DestroyTexture(options_texture);

}

void main_username(SDL_Window *window)
{
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
	SDL_StartTextInput();
    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_Texture *BKG_texture = IMG_LoadTexture(Renderer,BKG_PATH);
    SDL_Rect BKG_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);

    
    SDL_Rect userTXT_rect;
    SDL_Texture *userTXT_texture;
    
    SDL_Texture *message_texture = text_texture(Renderer,"please ENTER username :",60,TXT_HEADER,255,255,255,150);
    SDL_Rect messsage_rect = texture_position(message_texture,TXR_CENTER,350,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
    while(running[STG_USERINPUT])
	{
        frame++;
        if (frame == 8*FPS-1) frame = 0;


        BKG_texture = dynamic_background(Renderer,BKG_texture,8,18);
        
        SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);
        sound_control(Renderer);

        boxColor(Renderer,100,474,600,476,0x332288aa);
        boxColor(Renderer,100,574,600,576,0x332288aa);
        userTXT_texture = text_texture(Renderer,user_name,50,TXT_BODY,255,255,255,255);
        userTXT_rect = texture_position(userTXT_texture,TXR_CENTER,500,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        
        textinput_show_options(Renderer);
		handling(Renderer);
        message_texture = text_texture(Renderer,"please ENTER username :",60,TXT_HEADER,255,255,255,200);
        messsage_rect = texture_position(message_texture,TXR_CENTER,350,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        SDL_RenderCopy(Renderer,message_texture,NULL,&messsage_rect);
        boxColor(Renderer,10,590,WIDTH - 10,640,0xcf010101);
        rectangleColor(Renderer,10,590,WIDTH - 10,640,0xff010150);
        message_texture = text_texture(Renderer,"! : load game is not allowed with new username !",40,TXT_HANDWRITE,255,255,255,200);
        messsage_rect = texture_position(message_texture,TXR_CENTER,590,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        SDL_RenderCopy(Renderer,message_texture,NULL,&messsage_rect);

        SDL_RenderCopy(Renderer,userTXT_texture,NULL,&userTXT_rect);
        
        mouse_cursor(Renderer);
        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS); 
        SDL_DestroyTexture(userTXT_texture);
        SDL_RenderClear(Renderer);

	}
    SDL_DestroyTexture(message_texture);
    SDL_DestroyTexture(userTXT_texture);
    SDL_DestroyTexture(BKG_texture);
    BKG_texture = NULL;
    SDL_StopTextInput();
    SDL_DestroyRenderer(Renderer);
    TTF_Quit();
    IMG_Quit();
}
#endif // !__TEXT__INPUT__