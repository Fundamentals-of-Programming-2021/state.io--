// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h>
// #include <stdlib.h>
// #include <math.h>
// #include <stdint.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL2_gfxPrimitives.h>
// #include <SDL2/SDL_ttf.h>

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


// _point STATECOUNT = {.x = 17 , .y = 7};

// _point MAP_CENTER = {.x = WIDTH/2 , .y = HEIGHT/2};

// const Uint32 BGCOLOR = 0xff602200;

// int Xmouse,Ymouse;
// int Xstate,Ystate;

// _point P_mouse,P_state,R_state;
// bool drawing = 0;
// int attack = -1;

// typedef struct 
// {
//     Uint32 color;
//     _point initstate;

// }_player;

// typedef struct
// {
//     _point start_state;
//     _point stop_state;

// }_attack_info;

// typedef struct
// {
//     int num;
//     bool is_capital;
//     Uint32 color;

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

// typedef struct
// {
//     _point center;
//     int radius;

// }SDL_circ;

// //0 =: for number , 1 =: for text , 2=: for combine

// void print_text(SDL_Renderer *renderer,int flag,int number,char* str,int x , int y)
// {
//     char *buffer = malloc(sizeof(char)*100);
//     if (flag == 0)
//     {
//         sprintf(buffer,"%d",number);
//     }
//     else if(flag == 1)
//     {
//         sprintf(buffer,"%s",str);
//     }
//     else if(flag == 2)
//     {
//         sprintf(buffer,"%s %d",str,number);
//     }
//     stringRGBA(renderer,x,y,buffer,255,255,255,255);
// }

// int power(int power,int base)
// {
//     int res = 1;
//     for (int i = 0; i < power; i++)
//     {
//         res *= base;
//     }
//     return res;
    
// }

// void armory_place(SDL_Renderer* renderer,_point coord, Uint32 color,int player,int size,int soldier_num)
// {
//     Sint8 C_radius = size;
//     Sint8 sq_len = size;
//     Sint8 trig_len = size*1.25;
//     switch (player)
//     {
//         case (0):
//             filledTrigonColor(renderer,coord.x,coord.y-trig_len,coord.x + trig_len * 0.85, coord.y+trig_len/2,coord.x -trig_len*0.85,coord.y+trig_len/2,color);
//             break;
//         case (1):
//             boxColor(renderer,coord.x-sq_len,coord.y-sq_len,coord.x+sq_len,coord.y+sq_len,color);
//             break;
//         default:
//             filledCircleColor(renderer,coord.x,coord.y,C_radius,color);
//             break;
//     }
//     print_text(renderer,0,soldier_num," ",coord.x-3,coord.y+30);
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

// _point mouse_check(SDL_Renderer *renderer,_state state[][100])
// {
//     int diameter = 60;
//     _point temp = {.x = -1,.y = -1};
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             if (power(2,state[i][j].center.x-Xmouse) + power(2,state[i][j].center.y-Ymouse) <= power(2,diameter))
//             {
//                 temp.x = i; temp.y=j;
//                 return temp;
//             }
//         }   
//     }
//     return temp;
// }

// void printmap(SDL_Renderer *Renderer,_state state[][100],_player player[])
// {
//     print_text(Renderer,1,0,"you are squere",MAP_CENTER.x-50,10);
//     Sint16 big_polyg[2][7];
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x02ffffff);
//             polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x03fff00f);

//             if (state[i][j].country.num != -1 && state[i][j].avalable)
//             {
//                 filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,state[i][j].country.color);
//                 if (state[i][j].country.is_capital)
//                 {
//                     armory_place(Renderer,state[i][j].center,0xffffffff,1,18,state[i][j].unitcount);
//                 }
//             }
//             else
//             {

//             }
//         }
//     }
// }

// int uninier(int i,int j,_state state[][100],int group,int chance)
// {
//     if (chance && state[i][j].country.num == -1)
//     {
//         state[i][j].country.num = group;
//         state[i][j].avalable = 1;
//         return 1;
//     }
//     return 0;
// }

// void setmap(SDL_Renderer *Renderer,_state state[][100],_player player[])
// {    
//     //sin 22.5 = 0.03827 / cos 22.5 = 0.9239
//     //sin 60 = 0.85 / cos60 = 0.5 
//     int diameter = 124;
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
//             step.y -= 35;
//             sethex(state[i][j].points,step,diameter,&state[i][j].center);    
//         }   
//     }

//     int country_num = 0;
//     int country_size = 0;
//     for (int i = 1; i < STATECOUNT.x-1; i ++)
//     {
//         for (int j = 1; j < STATECOUNT.y-1; j ++)
//         {
//             country_size = 0;
//             if (state[i][j].country.num == -1 && state[i][j].avalable)
//             {
//                 state[i][j].country.is_capital = 1;
//                 country_size += uninier(i,j,state,country_num,1);
//                 country_size += uninier(i+1,j,state,country_num,rand()%2);
//                 country_size += uninier(i,j+1,state,country_num,rand()%2);
//                 country_size += uninier(i-1,j,state,country_num,rand()%2);
//                 country_size += uninier(i,j-1,state,country_num,rand()%2);
//                 if (country_size == 1)
//                 {
//                     country_size += uninier(i+1,j,state,country_num,1);
//                     country_size += uninier(i,j+1,state,country_num,1);
//                     country_size += uninier(i-1,j,state,country_num,1);
//                     country_size += uninier(i,j-1,state,country_num,1);
//                 }
                
//                 country_num++;
//             }
//         }
//     }
    
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             printf("%d\t",state[i][j].country.num);            
//         }
//         printf("\n");
//     }
// }

// void SetColors(_player player[],int playernum,_state state[][100])
// {
//         player[0].color = 0x55005500;
//         player[1].color = 0x55000055;
//         player[2].color = 0x5500bb00;
//         player[3].color = 0x550000bb;

//         for (int i = 0; i < STATECOUNT.x; i++)
//         {
//             for (int j = 0; j < STATECOUNT.y; j++)
//             {
//                 state[i][j].country.color = 0x338888ff+ state[i][j].country.num * 0x0011aacc;
//             }
//         }
        
// }

// int arrive_check(SDL_circ circle[],int unitcount,_point stop)
// {
//     for (int i = 0; i < unitcount; i++)
//     {
//         if (circle[i].center.x != stop.x && circle[i].center.y != stop.y)
//         {
//             return 0;
//         }
//     }
//     return 1;  
// }

// int passed_unit = 0;
// SDL_circ circle[100];

// void attacker(SDL_Renderer *Renderer,_point start_coord , _point stop_coord , int unitnumber)
// {
    
    
//     _point difference =  {.y = stop_coord.y - start_coord.y , .x = stop_coord.x - start_coord.x};
//     int sin = difference.y/difference.x;

//     if (arrive_check(circle , unitnumber , stop_coord))
//     {
//         passed_unit = 0;
//         attack --;
//     }
    
//     else
//     {
//         for (int i = 0; i < passed_unit; i++)
//         {
//             if (collision_ditect() && collision_detect())
//             {
                
//             }
            
//             printf("circle num %d : %d,%d;\n",i,circle[i].center.x,circle[i].center.y);
//             filledCircleColor(Renderer,circle[i].center.x,circle[i].center.y,circle[i].radius,0xffffffff);
//             circle[i].center.x += (int)(25) ; circle[i].center.y += (int)(20) ;
//         }
//         if (passed_unit != unitnumber)
//         {
//             passed_unit++;            
//         }
        
//     }
// }


// _attack_info attack_info[100];
// void handling(SDL_Renderer *renderer,_state state[][100])
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
//             Xmouse = event.button.x;
//             Ymouse = event.button.y;
//             Xstate = mouse_check(renderer,state).x;
//             Ystate = mouse_check(renderer,state).y;
//         }

//         if(event.type == SDL_MOUSEBUTTONDOWN)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 P_mouse.x = event.motion.x;
//                 P_mouse.y = event.motion.y;
//                 drawing = 1;
//                 P_state.x = mouse_check(renderer,state).x;
//                 P_state.y = mouse_check(renderer,state).y;
//                 printf("%d %d",P_state.x,P_state.y);
//             }
//         }

//         if(event.type == SDL_MOUSEBUTTONUP)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 drawing = 0;
//                 R_state.x = mouse_check(renderer,state).x;
//                 R_state.y = mouse_check(renderer,state).y;
//                 printf(" -> %d %d\n",R_state.x,R_state.y);
//                 attack ++;
//                 attack_info[attack].start_state.x = P_state.x;
//                 attack_info[attack].start_state.y = P_state.y;
//                 attack_info[attack].stop_state.x = R_state.x;
//                 attack_info[attack].stop_state.x = R_state.y;
//             }
//         }
// 	}
// }

// void initializer(_state state[][100])
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
//             state[i][j].player = -1;
//             state[i][j].country.num = -1;
//             state[i][j].country.is_capital = 0;
//             state[i][j].unitcount = 0;
//         }
//     }
// }

// void solder_increasing(_state state[][100],time_t time)
// {

//     int speed = 1;
    
//     if (time % speed == 0)
//     {
//         for (int i = 0; i < STATECOUNT.x; i++)
//         {
//             for (int j = 0; j < STATECOUNT.y; j++)
//             {
//                 if (state[i][j].unitcount < 75)
//                 {
//                     state[i][j].unitcount+= 3;
//                 }                
//             }
//         }
//     }
// }

// void selected_state(SDL_Renderer *Renderer,_state state[][100])
// {
//     if (Xstate != -1 && Ystate != -1)
//     {
//         if (state[Xstate][Ystate].avalable && state[Xstate][Ystate].country.num != -1)
//         {
//             for (int i = 0; i < STATECOUNT.x; i++)
//             {
//                 for (int j = 0; j < STATECOUNT.y; j++)
//                 {
//                     if (state[i][j].country.num == state[Xstate][Ystate].country.num)
//                     {
//                         filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x10ffffff);
//                         polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0xffffffff);
//                     }
//                 }
                
//             } 
//         }
//     }
// }

// void print_dynamic_line(SDL_Renderer *Renderer,_state state[][100])
// {
//     if (drawing && state[P_state.x][P_state.y].avalable && state[Xstate][Ystate].avalable)
//     {
//         lineRGBA(Renderer,state[P_state.x][P_state.y].center.x,state[P_state.x][P_state.y].center.y,state[Xstate][Ystate].center.x,state[Xstate][Ystate].center.y,255,255,255,255);
//     }
// }



// int main() {

//     srand(time(NULL)*1000);
//     int player_count = 4;

//     _player player[player_count+1];
//     _state state[100][100];

//     initializer(state);

//     SDL_Init(SDL_INIT_VIDEO);


// 	SDL_Window *window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
//     HEIGHT, SDL_WINDOW_OPENGL);

//     SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

//     SDL_SetRenderDrawColor(Renderer,255,255,255,255);
//     setmap(Renderer,state,player);
//     SetColors(player,player_count,state);

//     int count = 0;
// 	time_t starting_time = time(NULL);
//     time_t previous_time = starting_time;
    
//     for (int i = 0; i < 50; i++)
//     {
//         circle[i].center.x = 100 ;
//         circle[i].center.y = 100 ;

//         circle[i].radius = 10;
//     }

//     while(1)
// 	{
//         time_t current_time = time(NULL);
//         boxColor(Renderer,0,0,WIDTH,HEIGHT,BGCOLOR);
//         print_text(Renderer,2,(int)(current_time - starting_time),"time passd:",10,10);
//         boxColor(Renderer,15,HEIGHT-30,WIDTH-15,HEIGHT-10,0xffffffff);
//         boxColor(Renderer,50,HEIGHT-21,WIDTH-50,HEIGHT-19,0x55101010);
        
//         if (current_time - previous_time != 0)
//         {
//             solder_increasing(state,current_time - starting_time);
//         }

//         // if (attack != -1)
//         // {
//         //     for (int i = 0; i <= attack; i++)
//         //     {
//         //         attacker(Renderer,state[attack_info[i].start_state.x][attack_info[i].start_state.y].center,state[attack_info[i].stop_state.x][attack_info[i].stop_state.y].center,state[attack_info[i].start_state.x][attack_info[i].start_state.y].unitcount);
//         //     }
//         // }

//         _point s = {.x = 100 , .y = 100} , p = {.x = 600,.y = 500};

//         attacker(Renderer,s,p,50);
        
        
        
//         // rainmaker(Renderer);
//         printmap(Renderer,state,player);

//         print_dynamic_line(Renderer,state);
//         selected_state(Renderer,state);

// 		handling(Renderer,state);
//         SDL_RenderPresent(Renderer);
//         previous_time = current_time;
// 		SDL_Delay(1000/FPS);
// 	}
    
//     SDL_RenderClear(Renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
//     return 0;
// }