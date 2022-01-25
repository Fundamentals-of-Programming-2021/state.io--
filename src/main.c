// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h>
// #include <stdlib.h>
// #include <math.h>
// #include <stdint.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL2_gfxPrimitives.h>

// #define FPS 60
// #define IMG_PATH "images/background.jpeg"

// typedef struct
// {
//     Sint16 x;
//     Sint16 y;

// }_point;

// const int WIDTH = 1800;
// const int HEIGHT = 900;
// const int padding = 30;
// const Uint32 NOSIDESTATECOLOR = 0xaaffffff;
// _point STATECOUNT = {.x = 15 , .y = 5};
// _point MAP_CENTER = {.x = WIDTH/2 , .y = HEIGHT/2};
// const Uint32 BGCOLOR = 0xccffd678;

// typedef struct 
// {
//     Uint32 color;
//     _point initstate;

// }_player;

// typedef struct
// {
//     int num;
//     bool is_capital;
// }_country;
// typedef struct
// {
//     Sint16 points[2][7];
//     _point center;
//     _country country;
//     bool avalable;
//     int unitcount;
//     short int player;

// }_state;

// void armory_place(SDL_Renderer* renderer,_point coord, Uint32 color,int player,int size)
// {
//     Sint8 C_radius = size;
//     Sint8 sq_len = size;
//     Sint8 trig_len = size*1.25;
//         switch (player)
//         {
//             case (0):
//                 filledTrigonColor(renderer,coord.x,coord.y-trig_len,coord.x + trig_len * 0.85, coord.y+trig_len/2,coord.x -trig_len*0.85,coord.y+trig_len/2,color);
//                 break;
//             case (1):
//                 boxColor(renderer,coord.x-sq_len,coord.y-sq_len,coord.x+sq_len,coord.y+sq_len,color);
//                 break;
//             default:
//                 filledCircleColor(renderer,coord.x,coord.y,C_radius,color);
//                 break;
//         }
// }

// void rainmaker(SDL_Renderer *renderer)
// {
//     if (rand()%2 == 1)
//     {
//         int length = 8;
//         for (int i = 0; i < 50; i++)
//         {
//             _point randomplace ={.x = rand()%WIDTH, .y = rand()%HEIGHT};
//             lineColor(renderer,randomplace.x,randomplace.y,randomplace.x+length,randomplace.y+length,0xffff55ff);
//             lineColor(renderer,randomplace.x-1,randomplace.y-1,randomplace.x+length,randomplace.y+length,0xffffff55);
//             lineColor(renderer,randomplace.x-3,randomplace.y-3,randomplace.x+length,randomplace.y+length,0xffff5555);
//         }
//     }
// }

// //makes all of a hex shape points
// void sethex(Sint16 point[][7],_point center,int diameter,_point *state_cent)
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

// void printmap(SDL_Renderer *Renderer,_state state[][100],_player player[])
// {
//     Uint32 groupcolor[100];
    
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x30808080);
//             polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x44ffffff);
            
//             if (state[i][j].avalable)
//             {
//                 filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x338888ff+ state[i][j].country.num * 0x00220000);
//                 if (state[i][j].player == -1 && state[i][j].country.is_capital)
//                 {
//                     armory_place(Renderer,state[i][j].center,0xffffffff,-1,24);
//                 }
//                 else if(state[i][j].player != -1 && state[i][j].country.is_capital)
//                 {
//                     polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,player[state[i][j].player].color);
//                     armory_place(Renderer,state[i][j].center,player[state[i][j].player].color,state[i][j].player,20);
//                 }
//             }
//             else
//             {

//             }
//         }
//     }
// }
// void uninier(int i,int j,_state state[][100],int depth,int group)
// {
//     if (depth > 6)
//     {
//         return;
//     }
//     else
//     {
//         int count = rand() % 4;
//         if (count == 1)
//         {
//             state[i+1][j].country.num = group;
//             uninier(i+1,j,state,depth+1,group);
//         }
//         else if (count == 2)
//         {
//             state[i+1][j+1].country.num = group;
//             uninier(i+1,j+1,state,depth+1,group);
//         }
//         else if (count == 3)
//         {
//             state[i][j+1].country.num = group;
//             uninier(i,j+1,state,depth+1,group);
//         }
//     }
// }

// void setmap(SDL_Renderer *Renderer,_state state[][100],_player player[])
// {    
//     //sin 22.5 = 0.03827 / cos 22.5 = 0.9239
//     //sin 60 = 0.85 / cos60 = 0.5 
//     int diameter = 150;
//     _point step;

//     for (int i = 0 ; i < STATECOUNT.x ; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y ; j++)
//         {
//             if (i % 2 == 1)
//             {
//                 step.x = MAP_CENTER.x + ((i-STATECOUNT.x/2) * diameter * 0.75);
//                 step.y = MAP_CENTER.y + ((j-STATECOUNT.y/2) * diameter *0.85);
//             }
//             else
//             {
//                 step.x = MAP_CENTER.x + ((i-STATECOUNT.x/2) * diameter * 0.75);
//                 step.y = MAP_CENTER.y + ((j-STATECOUNT.y/2) * diameter *0.85) + diameter/2*0.85;
//             }
//             step.y += 10;
//             sethex(state[i][j].points,step,diameter,&state[i][j].center);    
//         }   
//     }
//     int group = 0;
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             if (state[i][j].country.num == -1)
//             {
//                 state[i][j].country.is_capital = 1;
//                 uninier(i,j,state,0,group);
//                 group++;
//             }
            
//         }
//     }
    
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             printf("%d\n",state[i][j].country.num);            
//         }
//     }
// }



// void SetPlayerColor(_player player[],int playernum)
// {
//         player[0].color = 0x55005500;
//         player[1].color = 0x55000055;
// }

// void handling(void)
// {
// 	SDL_Event event;
//     while (SDL_PollEvent(&event)) {
//         if (event.type == SDL_QUIT) exit(0);
//         if (event.type == SDL_KEYDOWN)
//         {
//             const Uint8* keys = SDL_GetKeyboardState(NULL);
//         }
//         if( event.type == SDL_MOUSEMOTION)
//         {
//                 //event.motion.x and event.motion.y 
//         }
//         if(event.type == SDL_MOUSEBUTTONDOWN)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 printf("pressed on (%d,%d)\n", event.button.x, event.button.y);
//             }
//         }
//         if(event.type == SDL_MOUSEBUTTONUP)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 printf("finished on (%d,%d)\n", event.button.x, event.button.y);
//             }
//         }
// 	}
// }


// int main() {

//     srand(time(NULL)*1000);
//     int player_count = 2;

//     _player player[player_count+1];
//     _state state[100][100];

//     SetPlayerColor(player,player_count);

//     int temp;
//     for (int i = 0; i < STATECOUNT.x ; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             temp = rand() ;
//             if(temp % 5 == 1 || temp % 5 == 2)
//             {
//                 state[i][j].avalable = 0;
//             }
//             else
//             {
//                 state[i][j].avalable = 1;
//             }
//             state[i][j].player = -1;
//             state[i][j].country.num = -1;
//             state[i][j].country.is_capital = 0;
//         }
//     }
    

//     for (int i = 0; i < player_count; i++)
//     {
//         _point temp;
//         temp.x = rand() % (STATECOUNT.x-1)+1;
//         temp.y = rand() % (STATECOUNT.y-1)+1;
//         while (state[temp.x][temp.y].avalable == 0 || state[temp.x][temp.y].player != -1)
//         {
//             temp.x = rand()%(STATECOUNT.x-1)+1;
//             temp.y = rand()%(STATECOUNT.y-1)+1;
//         }
//         state[temp.x][temp.y].player = i;
//         player[i].initstate.x = temp.x;
//         player[i].initstate.y = temp.y;
//     }
    

    

//     SDL_Init(SDL_INIT_VIDEO);


// 	SDL_Window *window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
//     HEIGHT, SDL_WINDOW_OPENGL);

//     SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

//     SDL_SetRenderDrawColor(Renderer,255,255,255,255);
//     setmap(Renderer,state,player);
	
//     while(1)
// 	{
//         boxColor(Renderer,0,0,WIDTH,HEIGHT,BGCOLOR);

//         boxColor(Renderer,15,HEIGHT-30,WIDTH-15,HEIGHT-10,0xffffffff);
//         boxColor(Renderer,50,HEIGHT-21,WIDTH-50,HEIGHT-19,0x55101010);
//         // rainmaker(Renderer);
//         printmap(Renderer,state,player);
//         SDL_RenderPresent(Renderer);

// 		handling();
// 		SDL_Delay(1000/FPS);
        
// 	}

//     SDL_RenderClear(Renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
//     return 0;
// }