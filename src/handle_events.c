#ifndef __HANDLE__EVENTS__
#define __HANDLE__EVENTS__

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



void handling(SDL_Renderer *renderer)
{
    
	SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
        {
            kill_program();
        }
        if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN)
        {
            if(event.type == SDL_TEXTINPUT)
            {
                if (stage == STG_USERINPUT)
                {
                    if (strlen(user_name) > 20)
                    {
                        Mix_Chunk *beep = Mix_LoadWAV("music/beep.wav");
                        Mix_PlayChannel(3,beep,0);
                    }

                    else
                    {
                        if (*(event.text.text) != SDLK_SPACE)
                        {
                            Mix_Chunk *button= Mix_LoadWAV("music/button1.wav");
                            if (rand()%2)
                            {
                                button = Mix_LoadWAV("music/button2.wav");
                            }
                            Mix_PlayChannel(-1,button,0);
                            user_name[strlen(user_name)] = *(event.text.text);
                            user_name[strlen(user_name)] = '\0';
                        }
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(user_name) > 0)
                {
                    if (stage == STG_USERINPUT)
                    {
                        user_name[strlen(user_name)-1] = '\0';
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN)
                {
                    return_is_down = 1;
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    if (stage == STG_FIRSTPAGE)
                    {
                        selected_option -= 1;
                        if (selected_option < 1)
                        {
                            selected_option = 1;
                        }                    
                    }
                    else if (stage == STG_SELECTMAP)
                    {
                        map_num -= 2;
                        if (map_num < -1)
                        {
                            map_num = -1;
                        }
                    }
                    
                }
                else if (event.key.keysym.sym == SDLK_DOWN)
                {
                    if (stage == STG_FIRSTPAGE)
                    {
                        selected_option += 1;
                        if (selected_option > 3)
                        {
                            selected_option = 3;
                        }
                    }
                    else if (stage == STG_SELECTMAP)
                    {
                        map_num += 2;
                        if (map_num > 3)
                        {
                            map_num = -1;
                        }
                    }
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    if (stage == STG_USERINPUT)
                    {
                        selected_option += 1;
                        if (selected_option > 1)
                        {
                            selected_option = 1;
                        }
                    }
                    else if (stage == STG_SELECTMAP)
                    {
                        map_num ++;
                        if (map_num > 3)
                        {
                            map_num = -1;
                        }
                    }
                }
                else if (event.key.keysym.sym == SDLK_LEFT)
                {
                    if (stage == STG_USERINPUT)
                    {
                        selected_option -= 1;
                        if (selected_option < 0)
                        {
                            selected_option = 0;
                        }                    
                    }
                    else if (stage == STG_SELECTMAP)
                    {
                        map_num --;
                        if (map_num < -1)
                        {
                            map_num = 3;
                        }
                    }
                }
            }
        }
        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_RETURN)
            {
                return_is_down = 0;
            }
        }
        if( event.type == SDL_MOUSEMOTION)
        {
            mouse_pos.x = event.button.x;
            mouse_pos.y = event.button.y;
            if (stage == STG_INGAME)
            {
                S_mouse_state.x = mouse_check(renderer).x;
                S_mouse_state.y = mouse_check(renderer).y;
            }
            
            
        }
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_is_down = 1;
                if (stage == STG_INGAME)
                {
                    F_mouse_state = S_mouse_state;
                }
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_is_down = 0;
                if (stage == STG_INGAME)
                {
                    if (S_mouse_state.x != -1 && F_mouse_state.x != -1 && S_mouse_state.y != -1 && F_mouse_state.y != -1 && ( S_mouse_state.x != F_mouse_state.x || S_mouse_state.y != F_mouse_state.y) && state[F_mouse_state.x][F_mouse_state.y].avalable && state[S_mouse_state.x][S_mouse_state.y].avalable && is_game_running() && country[state[F_mouse_state.x][F_mouse_state.y].country_num].player == 0)
                    {
                        Mix_Chunk *yes_chunk = Mix_LoadWAV("music/yes.wav");
                        Mix_PlayChannel(0,yes_chunk,0);
                        attack_initializer(F_mouse_state,S_mouse_state);
                    }
                }
            }
        }
	}
}


_coord center = { .x = 200 , .y = 950};
void sound_control(SDL_Renderer *Renderer)
{
    SDL_Texture *sound_texture = IMG_LoadTexture(Renderer,"images/icon/sound_icon.png");
    SDL_Rect sound_rect = texture_position(sound_texture,30,HEIGHT - 70,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,sound_texture,NULL,&sound_rect);
    SDL_DestroyTexture(sound_texture);
    
    boxColor(Renderer,85,44+905,295,46+905,0xccffffff);
    boxColor(Renderer,center.x-10,center.y-10,center.x+10,center.y+10,0xff4040aa);
    static int flag = 0;
    if (mouse_pos.x >= 85 && mouse_pos.x <= 295 && mouse_pos.y >= 940 && mouse_pos.y <= 960)
    {
        if (mouse_is_down)
        {
            flag = 1;
        }
        
    }

    if(flag)
    {
        rectangleColor(Renderer,center.x-10,center.y-10,center.x+10,center.y+10,0xff9090ff);
        if (mouse_pos.x >= 295)
        {
            center.x = 295;
        }
        else if (mouse_pos.x <= 85)
        {
            center.x = 85;
        }
        else
        {
            center.x = mouse_pos.x;
        }            
    }

    if(mouse_is_down == 0)flag = 0;

    double percent = (center.x-85)*128/210;
    Mix_VolumeMusic(percent);
}

#endif // !__HANDLE__EVENTS__
