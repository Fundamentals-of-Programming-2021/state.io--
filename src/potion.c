#ifndef __POTION__
#define __POTION__

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

//potion 0 for speeding up unit generation
//potion 1 for unlimit unit generation
//potion 2 for super speed
//potion 3 for freezing others

int active_potion(int player_num)
{
    for (int i = 0; i < 4; i++)
    {
        if (potions[i].owner == player_num)
        {
            return i;
        }
    }
    return -1;
    
}


int only_one_potion(int player_num)
{
    for (int i = 0; i < 4; i++)
    {
        if (potions[i].owner == player_num)
        {
            return 0;
        }
    }
    return 1;
    
}

void potion_check(int num)
{
    if (num == 0)
    {
        if (time(NULL) - potions[0].start_time > 6)
        {
            potions[0].owner = -2;
        }
    }
    else if (num == 1)
    {
        if (time(NULL) - potions[1].start_time > 8)
        {
            potions[1].owner = -2;
        }
    }
    else if (num == 2)
    {
        if (time(NULL) - potions[2].start_time > 7)
        {
            potions[2].owner = -2;
        }
    }
    else if (num == 3)
    {
        if (time(NULL) - potions[3].start_time > 5)
        {
            potions[3].owner = -2;
        }
    }
    
    
    
}

void print_potion(SDL_Renderer *Renderer , int l,int k,int pot_num,int potion_counter)
{
    char *address = malloc(100);
    strcpy(address,"images/potions/3.png");
    if (pot_num == 0) address[15] = 0+'0';
    if (pot_num == 1) address[15] = 1+'0';
    if (pot_num == 2) address[15] = 2+'0';

    potions[pot_num].center.x = 0.35*(state[country[l].capital.x][country[l].capital.y].center.x + state[country[k].capital.x][country[k].capital.y].center.x);
    potions[pot_num].center.y = 0.35*(state[country[l].capital.x][country[l].capital.y].center.y + state[country[k].capital.x][country[k].capital.y].center.y);
    if (potions[pot_num].owner == -2)
    {
        SDL_Texture *texture = IMG_LoadTexture(Renderer,address);
        if (texture == NULL)
        {
            printf("gooz\n");
        }
        
        SDL_Rect dst_rect = texture_position(texture,potions[pot_num].center.x,potions[pot_num].center.y,40,40);
        SDL_RenderCopy(Renderer,texture,NULL,&dst_rect);
        SDL_DestroyTexture(texture);
    }
    _double_coord temp;
    for (int i = 1; i <= atc_num && potions[pot_num].owner == -2; i++)
    {
        if (attacks[i].is_done == 0)
        {
            for (int j = 0; j < attacks[i].passed_unit; j++)
            {
                temp.x = potions[pot_num].center.x+20;
                temp.y = potions[pot_num].center.y+20;
                if (colission_detect(temp,soldier[i][j].center,30))
                {
                    if (only_one_potion(soldier[i][j].player))
                    {
                        Mix_Chunk *drink_chunk = Mix_LoadWAV("music/drinking.wav");
                        Mix_PlayChannel(3,drink_chunk,0);
                        potions[pot_num].owner = soldier[i][j].player;
                        potions[pot_num].start_time = time(NULL);
                        potions[pot_num].center.x = 0;
                        potions[pot_num].center.y = 0;
                        if (Mix_Paused(3))
                        {
                            Mix_FreeChunk(drink_chunk);
                        }
                        
                    }                    
                }
            }
        }
    }
    SDL_Texture *help_texture;
    if (pot_num == 3)
    {
        help_texture = IMG_LoadTexture(Renderer,"menu/freeze.png");
    }
    else if (pot_num == 1)
    {
        help_texture = IMG_LoadTexture(Renderer,"menu/no_limit.png");
        
    }
    else if (pot_num == 2)
    {
        help_texture = IMG_LoadTexture(Renderer,"menu/speed_up.png");
        
    }
    else if (pot_num == 0)
    {
        help_texture = IMG_LoadTexture(Renderer,"menu/boost.png");
        
    }
    SDL_Rect dst_rect = {.x = 5,.y = 10,.w = 200,.h = 50};
    if (potion_counter == 0)
    {
        dst_rect.x = 490;
    }
    else if (potion_counter == 1)
    {
        dst_rect.x =10;
    }
    
    SDL_RenderCopy(Renderer,help_texture,NULL,&dst_rect);
    SDL_DestroyTexture(help_texture);
    free(address);
}


#endif // !__POTION__