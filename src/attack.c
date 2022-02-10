#ifndef __ATTACK__
#define __ATTACK__

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


void solder_increasing()
{
    int speed = 1;
    
    if (1)
    {
       for(int i = 0; i < country_count ; i++)
       {
            if (potions[1].owner == country[i].player)
            {
                if (!country[i].is_under_attack)
                {
                    if (active_potion(country[i].player) == 0 && potions[0].start_time - time(NULL) <= 3)
                    {
                        country[i].unitcount += 3;
                    }
                    country[i].unitcount += 1;
                }
            }
            else
            {
                if (country[i].unitcount < 75 && !country[i].is_under_attack && country[i].player != -1 )
                {
                    if (active_potion(country[i].player) == 0 && potions[0].start_time - time(NULL) <= 3)
                    {
                        country[i].unitcount += 3;
                    }
                    country[i].unitcount += 1;
                }     
            }
           
                       
       }
    }
}

int reach_check(int atk_num,int count)
{
    for (int i = 0; i < count; i++)
    {
        if (soldier[atk_num][i].reached == 0)
        {
            return 0;
        }
    }
    return 1;
}

int soldier_faced(int atk_num,int sold_num,_coord *res)
{
    for (int i = 1; i <= atc_num; i++)
    {
        if (soldier[i][0].player != soldier[atk_num][sold_num].player && attacks[i].passed_unit > 0)
        {
            for (int m = 0; m < attacks[i].passed_unit; m++)
            {
                if (colission_detect(soldier[i][m].center,soldier[atk_num][sold_num].center,25) && soldier[i][m].damage && soldier[atk_num][sold_num].damage)
                {
                    explosion[explosion_num].center.x = (soldier[i][m].center.x+soldier[atk_num][sold_num].center.x)/2;
                    explosion[explosion_num].center.y = (soldier[i][m].center.y+soldier[atk_num][sold_num].center.y)/2;
                    explosion[explosion_num].exp_frame = 0;
                    explosion[explosion_num].is_done = 0;
                    explosion_num ++;

                    Mix_Chunk *bubble_chunk = Mix_LoadWAV("music/bubble.wav");
                    Mix_PlayChannel(-1,bubble_chunk,0); 
                    res->x = i;
                    res->y = m;
                    return 1;
                }
            }
        }
    }
    return 0;
}

_double_coord set_speed(_double_coord difference)
{
    _double_coord speed;
        if (difference.x == 0)
    {
        if (difference.y > 0)
        {
            speed.y = 1;
        }
        else
        {
            speed.y = -1;
        }        
        speed.x = 0;
    }
    else if (difference.y == 0)
    {
        if (difference.x > 0)
        {
            speed.x = 1;
        }
        else
        {
            speed.x = -1;
        }        
        speed.y = 0;
    }
    else
    {
        speed.y = difference.y/sqrt(pow(difference.x,2)+pow(difference.y,2));
        speed.x = difference.x/sqrt(pow(difference.x,2)+pow(difference.y,2));
    }
    return speed;
}

void attack_initializer(_coord F_state , _coord S_state)
{
    atc_num ++;
    int k = atc_num;
    for (int i = 1; i < atc_num; i++)
    {
        if (attacks[i].is_done)
        {
            k = i;
            atc_num --;
            break;
        }
        
    }
    
    attacks[k].is_done = 0;
    attacks[k].start_state = F_state;
    attacks[k].stop_state = S_state;
    attacks[k].soldier_num = country[state[F_state.x][F_state.y].country_num].unitcount;
    attacks[k].num = k;
    attacks[k].passed_unit = 0;

    for (int i = 0; i < attacks[k].soldier_num; i++)
    {
        soldier[k][i].center.x = state[F_state.x][F_state.y].center.x;
        soldier[k][i].center.y = state[F_state.x][F_state.y].center.y;
        soldier[k][i].damage = 1;
        soldier[k][i].reached = 0;
        soldier[k][i].dest = S_state;
        soldier[k][i].player = country[state[F_state.x][F_state.y].country_num].player;
    }

    country[state[F_state.x][F_state.y].country_num].unitcount = 0;
    country[state[S_state.x][S_state.y].country_num].is_under_attack =1;
}

void free_country(int cntry_num)
{
    for (int i = 1; i <= atc_num; i++)
    {
        if (soldier[i][0].dest.x == country[cntry_num].capital.x && soldier[i][0].dest.y == country[cntry_num].capital.y && attacks[i].is_done == 0)
        {
            return;
        }
    }
    country[cntry_num].is_under_attack = 0;
}

void print_soldier(SDL_Renderer *Renderer,_coord F_state , _coord S_state  ,int number,int Attack_num)
{
    _double_coord difference = {.x = state[S_state.x][S_state.y].center.x - state[F_state.x][F_state.y].center.x , .y = state[S_state.x][S_state.y].center.y - state[F_state.x][F_state.y].center.y};
    _double_coord speed;
    
    char soldier_path[100];

    speed = set_speed(difference);
    
    if (speed.x < 0)
    {
        strcpy(soldier_path,"images/soldier_2_1.png");
    }
    else
    {
        strcpy(soldier_path,"images/soldier_1_2.png");
    }
    
    _coord res;
    SDL_Texture *soldier_texture = IMG_LoadTexture(Renderer,soldier_path);
    for (int i = 0; i < attacks[Attack_num].passed_unit ; i++)
    {
        soldier_path[15] = (char)soldier[Attack_num][i].player + '0';

        if (soldier_faced(Attack_num,i,&res))
        {
            soldier[Attack_num][i].damage = 0;
            soldier[res.x][res.y].center = state[soldier[res.x][res.y].dest.x][soldier[res.x][res.y].dest.y].center;
            soldier[res.x][res.y].damage = 0;
            soldier[Attack_num][i].reached = 1;
            soldier[res.x][res.y].reached = 1;
            soldier[Attack_num][i].center = state[soldier[Attack_num][i].dest.x][soldier[Attack_num][i].dest.y].center;
        }
        if (!colission_detect(soldier[Attack_num][i].center,state[S_state.x][S_state.y].center,30))
        {
            if (potions[3].owner != -2)
            {
                if (soldier[Attack_num][i].player == potions[3].owner)
                {
                    soldier[Attack_num][i].center.y +=  12*speed.y;
                    soldier[Attack_num][i].center.x +=  12*speed.x;
                }
                   
            }
            else
            {
                
                if (active_potion(soldier[Attack_num][i].player) == 2)
                {
                    soldier[Attack_num][i].center.y +=  20*speed.y;
                    soldier[Attack_num][i].center.x +=  20*speed.x;   
                }
                else
                {
                    soldier[Attack_num][i].center.y +=  12*speed.y;
                    soldier[Attack_num][i].center.x +=  12*speed.x;
                }
            }
        }
        else
        {
            soldier[Attack_num][i].reached = 1;
        }
        if (!soldier[Attack_num][i].reached && soldier[Attack_num][i].damage)
        {
            soldier_texture = IMG_LoadTexture(Renderer,soldier_path);
            SDL_Rect soldier_rect = texture_position(soldier_texture,soldier[Attack_num][i].center.x-30,soldier[Attack_num][i].center.y-30,60,60);
            SDL_RenderCopy(Renderer,soldier_texture,NULL,&soldier_rect);
        }
        else if(soldier[Attack_num][i].reached && soldier[Attack_num][i].damage)
        {
            if (soldier[Attack_num][i].player != country[state[soldier[Attack_num][i].dest.x][soldier[Attack_num][i].dest.y].country_num].player)
            {
                if (country[state[S_state.x][S_state.y].country_num].player == potions[4].owner)
                {
                    country[state[S_state.x][S_state.y].country_num].unitcount++;
                }
                else
                {
                    country[state[S_state.x][S_state.y].country_num].unitcount--;
                }
                if (country[state[S_state.x][S_state.y].country_num].unitcount <= 0)
                {
                    country[state[S_state.x][S_state.y].country_num].player = soldier[Attack_num][i].player;
                    country[state[S_state.x][S_state.y].country_num].unitcount = 0;
                }
            }
            else
            {
                country[state[S_state.x][S_state.y].country_num].unitcount++;
            }
            
            soldier[Attack_num][i].damage = 0;
        }        
    }

    if (attacks[Attack_num].passed_unit != number && frame % 5 == 0 && (potions[3].owner == -2 || soldier[Attack_num][0].player == potions[3].owner) )
    {
        attacks[Attack_num].passed_unit++;
    }

    if (reach_check(Attack_num,number))
    {
        attacks[Attack_num].is_done = 1;
        attacks[Attack_num].passed_unit = 0;
        free_country(state[S_state.x][S_state.y].country_num);
    }
    SDL_DestroyTexture(soldier_texture);
}

int lossing()
{
    for (int i = 0; i < country_count; i++)
    {
        if(country[i].player == 0)return 0;
    }
    return 1;
}

int is_enemy_attacking()
{
    for (int i = 1; i <= atc_num; i++)
    {
        if (attacks[i].is_done == 0 && soldier[i][0].player != 0)
        {
            return 1;
        }
    }
    return 0;
}

int is_game_running()
{
    int k= 0;

    if (lossing())
    {
        for (int i = 1; i <= atc_num; i++)
        {
            if (soldier[i][0].player == 0 && attacks[i].is_done == 0)
            {
                return 1;
            }
        }
        return 0;
    }
    else
    {
        while (country[k].player == -1)k++;
        for (int i = 0; i < country_count; i++)
        {
            if(country[i].player != country[k].player && country[i].player != -1)
                return 1;
        }
    }
    return 0;
    
           
    
    

    for (int i = 1; i <= atc_num; i++)
    {
        for (int j = 0; j < attacks[i].passed_unit; j++)
        {
            if (soldier[i][j].player != 0)
            {
                return 1;
            }
        }
    }

    return 0;
    
}

void end_game(SDL_Renderer *Renderer)
{   
    if (!is_game_running() && !is_enemy_attacking())
    {
        Mix_HaltChannel(6);
        Mix_Chunk *end_soundEffect;
        SDL_Texture *texture;
        SDL_Rect rect;

        
        int k= 0;        
        while (country[k].player == -1)k++;
        
        if (country[k].player != 0 && country[k].player != -1 )
        {
            end_soundEffect = Mix_LoadWAV("music/loose.wav");
            texture = text_texture(Renderer,"you loose !",100,TXT_HEADER,255,255,255,255);
            win = 0;

        }
        else
        {
            end_soundEffect = Mix_LoadWAV("music/win.wav");
            texture = text_texture(Renderer,"you won !",100,TXT_HEADER,255,255,255,255);
            win = 1;
        }

        if (play_chunk)
        {
            Mix_PlayChannel(0,end_soundEffect,0);
            play_chunk = 0;
        }
        if (!Mix_Playing(0))
        {
            Mix_FreeChunk(end_soundEffect);
        }
        

        boxColor(Renderer,0,0,WIDTH,HEIGHT,0xef010101);
        rectangleColor(Renderer,380,850,680,950,0xffffffff);
        rect = texture_position(texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        SDL_RenderCopy(Renderer,texture,NULL,&rect);

        texture = IMG_LoadTexture(Renderer,"menu/score board.png");

        if (mouse_pos.x >= 380 && mouse_pos.x <= 680 && mouse_pos.y >= 850 && mouse_pos.y <= 950)
        {
            texture = IMG_LoadTexture(Renderer,"menu/score board_hovered.png");
            
            if (mouse_is_down)
            {
                Mix_Chunk *sword = Mix_LoadWAV("music/sword.wav");
                Mix_PlayChannel(-1,sword,0);
                mouse_is_down = 0;
                running[STG_LEADERBOARD] = 1;
                stage = STG_LEADERBOARD;
                running[STG_INGAME] = 0;
            }
        }
        rect = texture_position(texture,380,850,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        SDL_RenderCopy(Renderer,texture,NULL,&rect);
        SDL_DestroyTexture(texture);
    }    
}

void shift_explosion(int num)
{
    for (int i = 0; i < explosion_num; i++)
    {
        explosion[i] = explosion[i+num];
    }
}

void show_explosion(SDL_Renderer *Renderer,int exp_num)
{   
    if (explosion[exp_num].exp_frame == 4)
    {
        explosion[exp_num].is_done = 1;
        return;
    }
    explosion[exp_num].exp_frame ++;
    
    SDL_Rect explosion_src_rect;
    SDL_Rect explosion_dst_rect;
    SDL_Texture *explosion_texture;
    explosion_texture = IMG_LoadTexture(Renderer,"images/explosion/3.png");
    explosion_src_rect.x = (explosion[exp_num].exp_frame%4)*200 ; explosion_src_rect.y = (explosion[exp_num].exp_frame/4+1)*100 ,explosion_src_rect.w = 100;explosion_src_rect .h = 100;
    explosion_dst_rect.x = explosion[exp_num].center.x-40 ; explosion_dst_rect.y = explosion[exp_num].center.y-40 ; explosion_dst_rect.w = 80 ; explosion_dst_rect.h = 80;
    SDL_RenderCopy(Renderer,explosion_texture,&explosion_src_rect,&explosion_dst_rect);
    SDL_DestroyTexture(explosion_texture);

}

void explosion_check()
{
    int temp = 0;
    for (int i = 0; i < explosion_num; i++)
    {
        if (explosion[i].is_done == 1)
        {
            temp++;
        }
    }
    shift_explosion(temp);
    explosion_num -= temp;
}

//the most simplest AI in the world
void AI()
{
    for (int i = 1; i < player_count; i++)
    {
        for (int j = rand()%country_count; j < country_count; j++)
        {
            if (country[j].player == i)
            {
                for (int l = rand()%country_count; l < country_count; l++)
                {
                    if (is_game_running() && country[l].player != i && country[j].unitcount >= country[l].unitcount && country[j].unitcount > 15)
                    {
                        attack_initializer(country[j].capital,country[l].capital);
                    }
                }
            }
        }
    }
}

#endif




