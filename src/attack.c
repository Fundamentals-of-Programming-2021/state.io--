// #ifndef __ATTACK__
// #define __ATTACK__

// #pragma once
// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h>
// #include <stdlib.h>
// #include <math.h>
// #include <stdint.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL2_gfxPrimitives.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_image.h>
// #ifndef __STATE__IO
// #include "state_io.h"
// #endif // !__STATE__IO

// int colission_detect(_double_coord obj,_double_coord dest,int diameter)
// {
//     if ((pow(obj.x-dest.x,2) + pow(obj.y-dest.y,2))<= pow(diameter,2))
//     {
//         return 1;
//     }
//     return 0;
// }

// void solder_increasing(time_t time)
// {
//     int speed = 1;
    
//     if (time)
//     {
//        for(int i = 0; i < country_count ; i++)
//        {
//             if (country[i].unitcount < 75 && !country[i].is_under_attack && country[i].player != -1 )
//             {
//                 if(country[i].player == 0)country[i].unitcount += 2;
//                 else country[i].unitcount+= 1;
//             }                
//        }
//     }
// }

// void shift_attack(int num)
// {
//     _attack_info temp;
//     for (int i = num; i <= atc_num; i++)
//     {
//         temp = attacks[i];
//         attacks[i] = attacks[i+1];
//         attacks[i+1] = temp;
//     }
    
// }

// int reach_check(int cntry_num,int count)
// {
//     for (int i = 0; i < count; i++)
//     {
//         if (soldier[cntry_num][i].reached == 0)
//         {
//             return 0;
//         }
//     }
//     return 1;
// }

// int soldier_faced(int cntry_num,int sold_num,_coord *res)
// {
//     for (int i = 0; i <= country_count; i++)
//     {
//         if (soldier[i][0].player != soldier[cntry_num][sold_num].player && country[i].passed_unit > 0)
//         {
//             for (int m = 0; m < country[i].passed_unit; m++)
//             {
//                 if (colission_detect(soldier[i][m].center,soldier[cntry_num][sold_num].center,25) && soldier[i][m].damage && soldier[cntry_num][sold_num].damage)
//                 {
//                     explosion[explosion_num].center.x = (soldier[i][m].center.x+soldier[cntry_num][sold_num].center.x)/2;
//                     explosion[explosion_num].center.y = (soldier[i][m].center.y+soldier[cntry_num][sold_num].center.y)/2;
//                     explosion[explosion_num].exp_frame = 0;
//                     explosion[explosion_num].is_done = 0;
//                     explosion_num ++;

//                     Mix_Chunk *bubble_chunk = Mix_LoadWAV("music/bubble.wav");
//                     Mix_PlayChannel(-1,bubble_chunk,0); 
//                     res->x = i;
//                     res->y = m;
//                     return 1;
//                 }
//             }
//         }
//     }
//     return 0;
// }

// void attack_check()
// {
//     int temp = 0;
//     for (int i = 1; i < atc_num; i++)
//     {
//         if (attacks[i].is_done == 1)
//         {
//             shift_attack(i);
//             attacks[i].is_done = 0;
//             temp++;
//         }
//     }
//     atc_num -= temp;
// }

// _double_coord set_speed(_double_coord difference)
// {
//     _double_coord speed;
//         if (difference.x == 0)
//     {
//         if (difference.y > 0)
//         {
//             speed.y = 1;
//         }
//         else
//         {
//             speed.y = -1;
//         }        
//         speed.x = 0;
//     }
//     else if (difference.y == 0)
//     {
//         if (difference.x > 0)
//         {
//             speed.x = 1;
//         }
//         else
//         {
//             speed.x = -1;
//         }        
//         speed.y = 0;
//     }
//     else
//     {
//         speed.y = difference.y/sqrt(pow(difference.x,2)+pow(difference.y,2));
//         speed.x = difference.x/sqrt(pow(difference.x,2)+pow(difference.y,2));
//     }
//     return speed;
// }

// void attack_initializer(_coord F_state , _coord S_state)
// {
//     atc_num ++;

//     attacks[atc_num].is_done = 0;
//     attacks[atc_num].start_state = F_state;
//     attacks[atc_num].stop_state = S_state;
//     attacks[atc_num].soldier_num = country[state[F_state.x][F_state.y].country_num].unitcount;
//     attacks[atc_num].passed_unit = 0;

//     for (int i = 0; i < attacks[atc_num].soldier_num; i++)
//     {
//         soldier[state[F_state.x][F_state.y].country_num][i].center.x = state[F_state.x][F_state.y].center.x;
//         soldier[state[F_state.x][F_state.y].country_num][i].center.y = state[F_state.x][F_state.y].center.y;
//         soldier[state[F_state.x][F_state.y].country_num][i].damage = 1;
//         soldier[state[F_state.x][F_state.y].country_num][i].reached = 0;
//         soldier[state[F_state.x][F_state.y].country_num][i].dest = S_state;
//         soldier[state[F_state.x][F_state.y].country_num][i].player = country[state[F_state.x][F_state.y].country_num].player;

//     }

//     country[state[F_state.x][F_state.y].country_num].passed_unit = 0;
//     country[state[S_state.x][S_state.x].country_num].is_under_attack = 0;
//     country[state[F_state.x][F_state.y].country_num].unitcount = 0;
//     country[state[S_state.x][S_state.y].country_num].is_under_attack =1;
// }

// void print_soldier(SDL_Renderer *Renderer,_coord F_state , _coord S_state  ,int number,int Attack_num)
// {
//     _double_coord difference = {.x = state[S_state.x][S_state.y].center.x - state[F_state.x][F_state.y].center.x , .y = state[S_state.x][S_state.y].center.y - state[F_state.x][F_state.y].center.y};
//     _double_coord speed;
    
//     char soldier_path[100];

//     speed = set_speed(difference);
    
//     if (speed.x < 0)
//     {
//         strcpy(soldier_path,"images/soldier_2_1.png");
//     }
//     else
//     {
//         strcpy(soldier_path,"images/soldier_1_2.png");
//     }
    
//     //just for less typing 
//     _coord res;
//     SDL_Texture *soldier_texture = loadimg(soldier_path,Renderer);
//     for (int i = 0; i < attacks[Attack_num].passed_unit ; i++)
//     {
//         soldier_path[15] = (char)soldier[state[F_state.x][F_state.y].country_num][i].player + '1';

//         if (soldier_faced(state[F_state.x][F_state.y].country_num,i,&res))
//         {
            
//             soldier[state[F_state.x][F_state.y].country_num][i].damage = 0;
//             soldier[res.x][res.y].center = state[soldier[res.x][res.y].dest.x][soldier[res.x][res.y].dest.y].center;
//             soldier[res.x][res.y].damage = 0;
//             soldier[state[F_state.x][F_state.y].country_num][i].reached = 1;
//             soldier[res.x][res.y].reached = 1;
//             soldier[state[F_state.x][F_state.y].country_num][i].center = soldier[state[S_state.x][S_state.y].country_num][i].center;
//         }
//         if (!colission_detect(soldier[state[F_state.x][F_state.y].country_num][i].center,state[S_state.x][S_state.y].center,30))
//         {
//             soldier[state[F_state.x][F_state.y].country_num][i].center.y +=  8*speed.y;
//             soldier[state[F_state.x][F_state.y].country_num][i].center.x +=  8*speed.x;
//         }
//         else
//         {
//             soldier[state[F_state.x][F_state.y].country_num][i].reached = 1;
//         }
//         if (!soldier[state[F_state.x][F_state.y].country_num][i].reached && soldier[state[F_state.x][F_state.y].country_num][i].damage)
//         {
//             soldier_texture = loadimg(soldier_path,Renderer);
//             SDL_Rect soldier_rect = texture_position(soldier_texture,soldier[state[F_state.x][F_state.y].country_num][i].center.x-30,soldier[state[F_state.x][F_state.y].country_num][i].center.y-30,60,60);
//             SDL_RenderCopy(Renderer,soldier_texture,NULL,&soldier_rect);
//         }
//         else if(soldier[state[F_state.x][F_state.y].country_num][i].reached && soldier[state[F_state.x][F_state.y].country_num][i].damage)
//         {
//             if (soldier[state[F_state.x][F_state.y].country_num][i].player != country[state[soldier[state[F_state.x][F_state.y].country_num][i].dest.x][soldier[state[F_state.x][F_state.y].country_num][i].dest.y].country_num].player)
//             {
//                 country[state[S_state.x][S_state.y].country_num].unitcount--;
//                 if (country[state[S_state.x][S_state.y].country_num].unitcount <= 0)
//                 {
//                     country[state[S_state.x][S_state.y].country_num].player = soldier[state[F_state.x][F_state.y].country_num][i].player;
//                     country[state[S_state.x][S_state.y].country_num].unitcount = 0;
//                 }
//             }
//             else
//             {
//                 country[state[S_state.x][S_state.y].country_num].unitcount++;
//             }
            
//             soldier[state[F_state.x][F_state.y].country_num][i].damage = 0;
//         }        
//     }

//     if (attacks[Attack_num].passed_unit != number && frame % 7 == 0)
//     {
//         attacks[Attack_num].passed_unit++;
//         country[state[F_state.x][F_state.y].country_num].passed_unit++;
//     }

//     if (reach_check(state[F_state.x][F_state.y].country_num,number))
//     {
//         attacks[Attack_num].is_done = 1;
//         country[state[S_state.x][S_state.y].country_num].is_under_attack = 0;
//         country[state[F_state.x][F_state.y].country_num].passed_unit = 0;
//     }
//     SDL_DestroyTexture(soldier_texture);
// }

// void show_help_message(SDL_Renderer *Renderer)
// {
//     SDL_Texture *TXT_texture = text_texture(Renderer,"your icon is : ",20,TXT_HEADER,255,255,255,255);
//     SDL_Rect text_rect = texture_position(TXT_texture,WIDTH/2-60,10,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,TXT_texture,NULL,&text_rect);
//     SDL_DestroyTexture(TXT_texture);
//     SDL_Texture *icon_texture = loadimg("images/player_icon/0.png",Renderer);
//     SDL_Rect icon_rect = texture_position(icon_texture,WIDTH/2 + 60,0,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,icon_texture,NULL,&icon_rect);
//     SDL_DestroyTexture(icon_texture);
// }

// int is_game_running()
// {
//     int k= 0;        
//     while (country[k].player == -1)k++;

//     for (int i = 0; i < country_count; i++)
//     {   
//         if (country[i].player != -1)
//         {
//             if (country[i].player != country[k].player)
//             {
//                 return 1;
//             }
//         }
//     }
//     return 0;
    
// }

// void end_game(SDL_Renderer *Renderer)
// {   
//     if (!is_game_running())
//     {
//         Mix_Chunk *end_soundEffect;
//         SDL_Texture *texture;
//         SDL_Rect rect;

        
//         int k= 0;        
//         while (country[k].player != -1)k++;
        
//         if (country[k].player != 0 && country[k].player != -1)
//         {
//             end_soundEffect = Mix_LoadWAV("music/loose.wav");
//             texture = text_texture(Renderer,"you loose !",100,TXT_HEADER,255,255,255,255);

//         }
//         else
//         {
//             end_soundEffect = Mix_LoadWAV("music/win.wav");
//             texture = text_texture(Renderer,"you won !",100,TXT_HEADER,255,255,255,255);

//         }

//         if (play_chunk)
//         {
//             Mix_PlayChannel(0,end_soundEffect,0);
//             play_chunk = 0;
//         }
//         if (!Mix_Playing(0))
//         {
//             Mix_FreeChunk(end_soundEffect);
//         }
        

//         boxColor(Renderer,0,0,WIDTH,HEIGHT,0xef010101);
//         rectangleColor(Renderer,380,850,680,950,0xffffffff);
//         rect = texture_position(texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//         SDL_RenderCopy(Renderer,texture,NULL,&rect);

//         texture = loadimg("menu/back.png",Renderer);

//         if (mouse_pos.x >= 380 && mouse_pos.x <= 680 && mouse_pos.y >= 850 && mouse_pos.y <= 950)
//         {
//             texture = loadimg("menu/back_hovered.png",Renderer);
            
//             if (mouse_is_down)
//             {
//                 running[STG_INGAME] = 0;
//                 stage = STG_FIRSTPAGE;
//             }
//         }
//         rect = texture_position(texture,380,850,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//         SDL_RenderCopy(Renderer,texture,NULL,&rect);
        
        
//         SDL_DestroyTexture(texture);
    
//     }    
// }

// void shift_explosion(int num)
// {
//     for (int i = 0; i < explosion_num; i++)
//     {
//         explosion[i] = explosion[i+num];
//     }
// }

// void show_explosion(SDL_Renderer *Renderer,int exp_num)
// {   
//     if (explosion[exp_num].exp_frame == 4)
//     {
//         explosion[exp_num].is_done = 1;
//         return;
//     }
//     explosion[exp_num].exp_frame ++;
    
//     SDL_Rect explosion_src_rect;
//     SDL_Rect explosion_dst_rect;
//     SDL_Texture *explosion_texture;
//     explosion_texture = loadimg("images/explosion/3.png",Renderer);
//     explosion_src_rect.x = (explosion[exp_num].exp_frame%4)*200 ; explosion_src_rect.y = (explosion[exp_num].exp_frame/4+1)*100 ,explosion_src_rect.w = 100;explosion_src_rect .h = 100;
//     explosion_dst_rect.x = explosion[exp_num].center.x-40 ; explosion_dst_rect.y = explosion[exp_num].center.y-40 ; explosion_dst_rect.w = 80 ; explosion_dst_rect.h = 80;
//     SDL_RenderCopy(Renderer,explosion_texture,&explosion_src_rect,&explosion_dst_rect);
//     SDL_DestroyTexture(explosion_texture);

// }

// void explosion_check()
// {
//     int temp = 0;
//     for (int i = 0; i < explosion_num; i++)
//     {
//         if (explosion[i].is_done == 1)
//         {
//             temp++;
//         }
//     }
//     shift_explosion(temp);
//     explosion_num -= temp;
// }

// //the most simplest AI in the world
// void AI()
// {
//     for (int i = 1; i < 4; i++)
//     {
//         for (int j = rand()%country_count; j < country_count; j++)
//         {
//             if (country[j].player == i && country[j].passed_unit == 0)
//             {
//                 for (int l = rand()%country_count; l < country_count; l++)
//                 {
//                     if (is_game_running() && country[l].player != i && country[j].unitcount >= country[l].unitcount && country[j].unitcount > 10)
//                     {
//                         attack_initializer(country[j].capital,country[l].capital);
//                     }
//                 }
//             }
//         }
//     }
// }

// #endif




