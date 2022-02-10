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
//potion 4 for making enemy units ally

int potion_num = 5;

void potion_initializer()
{
    for (int i = 0; i < potion_num; i++)
    {
        potions[i].owner = -2;
    }
    
}

int set_potion(int num)
{
    int l[2],k[2],b[2] = {rand()%5,rand()%5};
    _double_coord difference;

    for (int i = 0; i < 2; i++)
    {   
        l[i] = rand()%(country_count-1);
        k[i] = rand()%(country_count-1);
        if (k[i] == l[i])
        {
            k[i] = rand()%(country_count-1);

        }
        difference.x = state[country[l[i]].capital.x][country[l[i]].capital.y].center.x - state[country[k[i]].capital.x][country[k[i]].capital.y].center.x;
        difference.y = state[country[l[i]].capital.x][country[l[i]].capital.y].center.y - state[country[k[i]].capital.x][country[k[i]].capital.y].center.y;
        b[i] = rand() %potion_num;
        float frac = 1/(rand()%2+2);
        potions[b[i]].center[i].x = (state[country[l[i]].capital.x][country[l[i]].capital.y].center.x + state[country[k[i]].capital.x][country[k[i]].capital.y].center.x)/2 + frac*(difference.x);
        potions[b[i]].center[i].y = (state[country[l[i]].capital.x][country[l[i]].capital.y].center.y + state[country[k[i]].capital.x][country[k[i]].capital.y].center.y)/2 + frac*(difference.y);
    }
    return b[num];
}

int active_potion(int player_num)
{
    for (int i = 0; i < potion_num; i++)
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
    for (int i = 0; i < potion_num; i++)
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
        if (time(NULL) - potions[1].start_time > 9)
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
    else if (num == 4)
    {
        if (time(NULL) - potions[4].start_time > 5)
        {
            potions[4].owner = -2;
        }
    }
    
    
}

void print_potion(SDL_Renderer *Renderer,int pot_num,int potion_counter)
{
    char *address = malloc(100);
    strcpy(address,"images/potions/ .png");
    address[15] = pot_num+'0';
    

    if (potions[pot_num].owner == -2)
    {
        SDL_Texture *texture = IMG_LoadTexture(Renderer,address);
        if (texture == NULL)
        {
            printf("goooooooz\n");
        }
        
        SDL_Rect dst_rect = texture_position(texture,potions[pot_num].center[potion_counter].x,potions[pot_num].center[potion_counter].y,40,40);
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
                temp.x = potions[pot_num].center[potion_counter].x+20;
                temp.y = potions[pot_num].center[potion_counter].y+20;
                if (colission_detect(temp,soldier[i][j].center,30))
                {
                    if (only_one_potion(soldier[i][j].player))
                    {
                        Mix_Chunk *drink_chunk = Mix_LoadWAV("music/drinking.wav");
                        Mix_PlayChannel(3,drink_chunk,0);
                        potions[pot_num].owner = soldier[i][j].player;
                        potions[pot_num].start_time = time(NULL);
                        potions[pot_num].center[potion_counter].x = 0;
                        potions[pot_num].center[potion_counter].y = 0;
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
    else if (pot_num == 4)
    {
        help_texture = IMG_LoadTexture(Renderer,"menu/no_enemy.png");
        
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