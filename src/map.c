// #ifndef __MAP__
// #define __MAP__

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

// void armory_place(SDL_Renderer* renderer,_double_coord coord, Uint32 color,int player,int size,int soldier_num)
// {
//     SDL_Texture *player_icon_texture;
//     SDL_Rect player_icon_rect;
//     if (player == 0)
//     {
//         player_icon_texture = loadimg("images/player_icon/0.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-19,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     }
//     else if (player == 1)
//     {
//         player_icon_texture = loadimg("images/player_icon/1.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-14,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);        
//     }
//     else if (player == 2)
//     {
//         player_icon_texture = loadimg("images/player_icon/2.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-31,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);        
//     }
//     else if (player == 3)
//     {
//         player_icon_texture = loadimg("images/player_icon/3.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-16,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);        
//     }
//     else
//     {
//         player_icon_texture = loadimg("images/player_icon/4.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-30,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     }
//     SDL_RenderCopy(renderer,player_icon_texture,NULL,&player_icon_rect);
//     SDL_DestroyTexture(player_icon_texture);
//     print_text(renderer,0,soldier_num," ",coord.x-3,coord.y+30);
// }

// void init_country()
// {
//     for (int i = 0; i < country_count; i++)
//     {
//         country[i].player = -1;
//         country[i].color = 0xffffffff;
//         country[i].unitcount = 30;
//     }
// }

// //makes all of a hex shape points
// void sethex(Sint16 point[][7],_double_coord center,int diameter,_double_coord *state_cent)
// {
//     point[0][0] = center.x - diameter/2;
//     point[0][1] = center.x - diameter/4;
//     point[0][2] = center.x + diameter/4;
//     point[0][3] = center.x + diameter/2;
//     point[0][4] = center.x + diameter/4;
//     point[0][5] = center.x - diameter/4;
//     point[1][0] = center.y;
//     point[1][1] = center.y - ((diameter/2)*0.85);
//     point[1][2] = center.y - ((diameter/2)*0.85);
//     point[1][3] = center.y;
//     point[1][4] = center.y + ((diameter/2)*0.85);
//     point[1][5] = center.y + ((diameter/2)*0.85);

//     state_cent->x = center.x;
//     state_cent->y = center.y; 
// }

// void initializer(SDL_Renderer *Renderer)
// {
//     int temp;
//     for (int i = 0; i < STATECOUNT.x ; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             temp = rand() ;
//             if(temp % 5 == 1 || temp % 5 == 2 || temp % 5 == 3)
//             {
//                 state[i][j].avalable = 0;
//             }
//             else
//             {
//                 state[i][j].avalable = 1;
//             }
//             state[i][j].country_num = -1;
//             state[i][j].is_capital = 0;
//         }
//     }
//     for (int i = 0; i < 1000; i++)
//     {
//         explosion[i].is_done = 1;
//         explosion[i].exp_frame = 0;
//     }
    
// }

// void printmap(SDL_Renderer *Renderer)
// {
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x01ffff05);
//             polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x02ffff00);

//             if (state[i][j].country_num != -1 && state[i][j].avalable)
//             {
//                 filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,country[state[i][j].country_num].color);
//                 polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,country[state[i][j].country_num].color);
//                 if (state[i][j].is_capital)
//                 {
//                     armory_place(Renderer,state[i][j].center,0xffffffff,country[state[i][j].country_num].player,18,country[state[i][j].country_num].unitcount);
//                 }
//             }
//         }
//     }
// }

// int uninier(int i,int j,int group,int chance)
// {
//     if (chance && state[i][j].country_num == -1)
//     {
//         state[i][j].country_num = group;
//         state[i][j].avalable = 1;
//         return 1;
//     }
//     return 0;
// }

// void setmap(SDL_Renderer *Renderer)
// {    
//     //sin 22.5 = 0.03827 / cos 22.5 = 0.9239
//     //sin 60 = 0.85 / cos60 = 0.5 
//     int diameter = 124;
//     _coord for_akhavans_sake = {rand()%10-3,rand()%10-5};
//     _double_coord step;
//     if (load_previous)
//     {
//         load_game();
//     }
//     else
//     {
//         for (int i = 0 ; i < STATECOUNT.x ; i++)
//         {
//             for (int j = 0; j < STATECOUNT.y ; j++)
//             {
//                 if (i % 2 == 1)
//                 {
//                     step.x = WIDTH/2 + ((i-STATECOUNT.x/2) * diameter * 0.75);
//                     step.y = HEIGHT/2 + ((j-STATECOUNT.y/2) * diameter *0.85);
//                 }
//                 else
//                 {
//                     step.x = WIDTH/2 + ((i-STATECOUNT.x/2) * diameter * 0.75);
//                     step.y = HEIGHT/2 + ((j-STATECOUNT.y/2) * diameter *0.85) + diameter/2*0.85;
//                 }
//                 step.y += 25 + for_akhavans_sake.y;
//                 step.x += for_akhavans_sake.x;
//                 sethex(state[i][j].points,step,diameter,&state[i][j].center);    
//             }   
//         }

//         int country_size;

//         for (int i = 1; i < STATECOUNT.x-1; i ++)
//         {
//             for (int j = 1; j < STATECOUNT.y-1; j ++)
//             {
//                 country_size = 0;
//                 if (state[i][j].country_num == -1 && state[i][j].avalable)
//                 {
//                     state[i][j].is_capital = 1;
//                     country[country_count].capital.x = i;
//                     country[country_count].capital.y = j;
//                     country_size += uninier(i,j,country_count,1);
//                     country_size += uninier(i+1,j,country_count,rand()%2);
//                     country_size += uninier(i,j+1,country_count,rand()%2);
//                     country_size += uninier(i-1,j,country_count,rand()%2);
//                     country_size += uninier(i,j-1,country_count,rand()%2);
//                     if (country_size == 1)
//                     {
//                         country_size += uninier(i+1,j,country_count,1);
//                         country_size += uninier(i,j+1,country_count,1);
//                         country_size += uninier(i-1,j,country_count,1);
//                         country_size += uninier(i,j-1,country_count,1);
//                     }
//                     country_count++;                    
//                 } 
//             }
//         }

//         init_country();

//         int n = 0;
//         int m = 0;
//         for (int i = 0; i < 4; i++)
//         {
//             if (i < country_count)
//             {       
//                 do
//                 {
//                     n = rand()%STATECOUNT.x;
//                     m = rand()%STATECOUNT.y;
//                 } while (state[n][m].avalable == 0 || country[state[m][n].country_num].player != -1);
//                 country[state[m][n].country_num].player = i;        
//             }
//         }

//     }
// }

// void SetColors()
// {
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             country[state[i][j].country_num].color = 0x88050505+ state[i][j].country_num * 0x00885515;
//         }
//     }
// }

// void light_background(int frame,SDL_Renderer *Renderer)
// {
//     static Uint32 color = 0x50252525;
//     static int temp = 1;

//     if (frame % 3 == 0)
//     {
//         color += temp * 0x00010101;
//     }
    
//     if (color == 0x50000000)
//     {
//         temp = 1;
//     }
//     else if (color == 0x50505050)
//     {
//         temp = -1;
//     }
//     boxColor(Renderer,0,0,WIDTH,HEIGHT,color);
// }

// void rainmaker(SDL_Renderer *renderer)
// {
//     if (rand()%2 == 1)
//     {
//         int length = 8;
//         for (int i = 0; i < 50; i++)
//         {
//             _coord randomplace ={.x = rand()%WIDTH, .y = rand()%HEIGHT};
//             lineColor(renderer,randomplace.x,randomplace.y,randomplace.x+length,randomplace.y+length,0xffff55ff);
//             lineColor(renderer,randomplace.x-1,randomplace.y-1,randomplace.x+length,randomplace.y+length,0xffffff55);
//             lineColor(renderer,randomplace.x-3,randomplace.y-3,randomplace.x+length,randomplace.y+length,0xffff5555);
//         }
//     }
// }

// void selected_state(SDL_Renderer *Renderer)
// {
//     if (F_mouse_state.x != -1 && F_mouse_state.y != -1 && mouse_is_down && country[state[F_mouse_state.x][F_mouse_state.y].country_num].player == 0)
//     {
//         if (state[F_mouse_state.x][F_mouse_state.y].avalable && state[F_mouse_state.x][F_mouse_state.y].country_num != -1)
//         {
//             for (int i = 0; i < STATECOUNT.x; i++)
//             {
//                 for (int j = 0; j < STATECOUNT.y; j++)
//                 {
//                     if (state[i][j].country_num == state[F_mouse_state.x][F_mouse_state.y].country_num)
//                     {
//                         filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x300505ff);
//                         polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0xff0515ff);
//                     }
//                 }
                
//             } 
//         }
//     }

//     if (S_mouse_state.x != -1 && S_mouse_state.y != -1)
//     {
//         if (state[S_mouse_state.x][S_mouse_state.y].avalable && state[S_mouse_state.x][S_mouse_state.y].country_num != -1)
//         {
//             for (int i = 0; i < STATECOUNT.x; i++)
//             {
//                 for (int j = 0; j < STATECOUNT.y; j++)
//                 {
//                     if (state[i][j].country_num == state[S_mouse_state.x][S_mouse_state.y].country_num)
//                     {
//                         filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x1000ffff);
//                         polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0xff00fff2);
//                     }
//                 }
                
//             } 
//         }
//     }
// }

// #endif


