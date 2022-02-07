// #ifndef __SAVE__LOAD__
// #define __SAVE__LOAD__

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

// void save_game()
// {
//     FILE *save;
//     char temp[100] = "saves/";

//     strcat(temp,user_name);
//     strcpy(user_name,temp);
//     save = fopen(user_name,"w");

//     fprintf(save,"%d %d %d ",STATECOUNT.x,STATECOUNT.y,country_count);
    
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             for (int m = 0; m < 6; m++)
//             {
//                 fprintf(save,"%d %d ",state[i][j].points[0][m],state[i][j].points[1][m]);
//             }
//             fprintf(save,"%f %f %d %d %d ",state[i][j].center.x,state[i][j].center.y,state[i][j].country_num ,state[i][j].is_capital,state[i][j].avalable);
//         }
//     }
//     for (int i = 0; i < country_count; i++)
//     {
//         fprintf(save,"%d %d %x %d %d %d %d %d ",country[i].capital.x,country[i].capital.y,country[i].color,country[i].is_under_attack,country[i].num,country[i].passed_unit,country[i].player,country[i].unitcount);
//     }
//     fclose(save);
// }

// void load_game()
// {
//     FILE *load = fopen(user_name,"r");
//     if (load == NULL)
//     {
//         printf("gooz\n");
//         return;
//     }
//     fscanf(load,"%*d %*d %d ",&country_count);
//     printf("%d\n",country_count);


    
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             for (int m = 0; m < 6; m++)
//             {
//                 fscanf(load,"%hd %hd ",&state[i][j].points[0][m],&state[i][j].points[1][m]);
//                 printf("%d %d\n",state[i][j].points[0][m],state[i][j].points[1][m]);
//             }
//             int temp1,temp2;
            
//             fscanf(load,"%lf %lf %d %d %d ",&state[i][j].center.x,&state[i][j].center.y,&state[i][j].country_num ,&temp1,&temp2);     
//             state[i][j].is_capital = temp1;
//             state[i][j].avalable = temp2;
//         }
//     }

//     for (int i = 0; i < country_count; i++)
//     {
//         int temp;
//         fscanf(load,"%hd %hd %x %d %d %d %d %d ",&country[i].capital.x,&country[i].capital.y,&country[i].color,&temp,&country[i].num,&country[i].passed_unit,&country[i].player,&country[i].unitcount);
//         country[i].is_under_attack = temp;
//     }
//     fclose(load);
    
// }

// int score_counter(int player)
// {
//     int res = 0;
//     for (int i = 0; i < country_count; i++)
//     {
//         if (country[i].player == player)
//         {
//             res += country[i].unitcount;
//         }
//     }
//     return res;
    
// }

// void update_leaderboard()
// {
//     FILE *leaderboard = fopen("saves/leader-board","a");
//     if (leaderboard == NULL)
//     {
//         printf("gooz\n");
//         return;
//     }
//     fprintf(leaderboard,"%s : %d\n",user_name,score_counter(0));
// }

// #endif