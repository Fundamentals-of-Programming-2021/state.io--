#ifndef __MOUSE__
#define __MOUSE__

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


_coord mouse_check(SDL_Renderer *renderer)
{
    int diameter = 60;
    _coord temp = {.x = -1,.y = -1};
    for (int i = 0; i < STATECOUNT.x; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            if (power(2,state[i][j].center.x-mouse_pos.x) + power(2,state[i][j].center.y-mouse_pos.y) <= power(2,diameter))
            {   
                // temp.x = country[state[i][j].country_num].capital.x; temp.y=country[state[i][j].country_num].capital.y;
                temp.x = i ; temp.y = j;
                return temp;
            }
        }   
    }
    return temp;
}

int is_mouse_attacking()
{
    if (S_mouse_state.x != -1 && F_mouse_state.x != -1 && S_mouse_state.y != -1 && F_mouse_state.y != -1 && mouse_is_down && state[F_mouse_state.x][F_mouse_state.y].avalable && state[F_mouse_state.x][F_mouse_state.y].country_num != -1  && country[state[F_mouse_state.x][F_mouse_state.y].country_num].player != -1 && state[S_mouse_state.x][S_mouse_state.y].country_num != -1 && state[S_mouse_state.x][S_mouse_state.y].avalable)
    {
        return 1;
    }
    return 0;
}

void mouse_cursor(SDL_Renderer *Renderer)
{
    
    if (mouse_is_down)
    {
        mouse_texture = IMG_LoadTexture(Renderer,"images/cursor/cursor 3.png");
    }
    else
    {
        mouse_texture = IMG_LoadTexture(Renderer,"images/cursor/cursor 1.png");
    } 
    if (stage == STG_INGAME && is_mouse_attacking())
    {
        mouse_texture = IMG_LoadTexture(Renderer,"images/cursor/cursor 2.png");
    }
    
    
    SDL_Rect mouse_rect = texture_position(mouse_texture,mouse_pos.x,mouse_pos.y,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,mouse_texture,NULL,&mouse_rect);
}


#endif