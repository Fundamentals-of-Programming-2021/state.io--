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

// #define FPS 60
// #define TXT_HEADER 0
// #define TXT_HANDWRITE 1
// #define TXT_BODY 2
// #define TXR_CENTER -1
// #define TXR_DEFAULT_SIZE -1
// typedef struct
// {
//     Sint16 x;
//     Sint16 y;

// }_coord;


// char BKG_PATH[100] = {"images/background/bg 1.jpg"};
// const int WIDTH = 700;
// const int HEIGHT = 1000;
// int frame = 0;
// bool running = 1;
// _coord STATECOUNT = {.x = 7 , .y = 8};
// _coord mouse_pos,F_mouse_state,S_mouse_state;
// bool mouse_is_down = 0;
// int atc_num = 0;
// int country_count = 0;
// char user_name[100] = "amir";
// bool load_previous = 0;

// typedef struct 
// {
//     _coord initstate;

// }_player;

// typedef struct
// {
//     _coord start_state;
//     _coord stop_state;
//     int soldier_num;
//     bool is_done;
//     int passed_unit;

// }_attack_info;

// typedef struct
// {
//     int num;
//     Uint32 color;
//     int passed_unit;
//     _coord capital;
//     bool is_under_attack;
//     int player;
//     int unitcount;

// }_country;

// typedef struct
// {
//     double x;
//     double y;

// }_double_coord;

// _country country[100];
// typedef struct
// {
//     Sint16 points[2][7];
//     _double_coord center;
//     int country_num;
//     bool is_capital;
//     bool avalable;

// }_state;

// _state state[100][100];
// typedef struct
// {
//     _double_coord center;
//     int radius;
//     bool reached;
//     bool damage;
//     _coord dest;
//     int player;

// }_soldier;

// _soldier soldier[100][1000];

// int sign(int num)
// {
//     return (num > 0 ? 1 : -1);
// }

// SDL_Texture *text_texture(SDL_Renderer *Renderer,char* str,int ptrsize,int flag,int r,int g,int b ,int a)
// {
//     TTF_Font *font;
//     if (flag == TXT_HEADER)
//     {
//         font = TTF_OpenFont("fonts/header/2.ttf",ptrsize);
//         if (font == NULL)printf("ERROR : %s\n",SDL_GetError());
//         // TTF_SetFontStyle(font,TTF_STYLE_BOLD);
//     }
//     else if(flag == TXT_BODY)
//     {

//         font = TTF_OpenFont("fonts/body/2.ttf",ptrsize);
//         if (font == NULL)printf("ERROR : %s\n",SDL_GetError());
    
//     }
//     else if(flag == TXT_HANDWRITE)
//     {
//         font = TTF_OpenFont("fonts/hand_write/2.ttf",ptrsize);
//         if (font == NULL)printf("ERROR : %s\n",SDL_GetError());
//     }

//     SDL_Color color = {r,g,b,a};
//     SDL_Surface *txtsurface = TTF_RenderText_Solid(font,str,color);
//     SDL_Texture *txtTexture = SDL_CreateTextureFromSurface(Renderer,txtsurface);
//     SDL_FreeSurface(txtsurface);
//     return txtTexture;    
// }

// SDL_Texture *loadimg(char* file_location,SDL_Renderer *Renderer)
// {
//     SDL_Surface *imgsurface = IMG_Load(file_location);
//     if (imgsurface == NULL)
//     {
//         printf("can not open image: %s \n",file_location);
//         return NULL;
//     }
    
//     SDL_Texture *Texture = SDL_CreateTextureFromSurface(Renderer,imgsurface);
//     SDL_FreeSurface(imgsurface);
//     return Texture;
// }

// SDL_Rect texture_position(SDL_Texture *txt_texture,int x,int y,int w,int h)
// {
//     SDL_Rect txt_rect = {.x = x , .y = y , .h = h , .w = w};
//     SDL_Rect txt_info;
//     SDL_QueryTexture(txt_texture,NULL,NULL,&txt_info.w,&txt_info.h);

//     if (x == TXR_CENTER)
//     {
//         txt_rect.x = WIDTH/2 - txt_info.w/2;
//     }
//     if (y == TXR_CENTER)
//     {
//         txt_rect.y = HEIGHT/2 - txt_info.h/2;
//     }
//     if (w == TXR_DEFAULT_SIZE)
//     {
//         txt_rect.w = txt_info.w;
//     }
//     if (h == TXR_DEFAULT_SIZE)
//     {
//         txt_rect.h = txt_info.h;
//     }
//     return txt_rect;
// }

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

// void armory_place(SDL_Renderer* renderer,_double_coord coord, Uint32 color,int player,int size,int soldier_num)
// {
//     SDL_Texture *player_icon_texture;
//     SDL_Rect player_icon_rect;
//     if (player == 0)
//     {
//         player_icon_texture = loadimg("images/player_icon/1.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-18,coord.y-20,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     }
//     else if (player == 1)
//     {
//         player_icon_texture = loadimg("images/player_icon/7.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-15,coord.y-40,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);        
//     }
//     else if (player == 2)
//     {
//         player_icon_texture = loadimg("images/player_icon/8.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-21,coord.y-20,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);        
//     }
//     else if (player == 3)
//     {
//         player_icon_texture = loadimg("images/player_icon/2.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-6,coord.y-20,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);        
//     }
//     else
//     {
//         player_icon_texture = loadimg("images/player_icon/5.png",renderer);
//         player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-20,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     }
//     SDL_RenderCopy(renderer,player_icon_texture,NULL,&player_icon_rect);
//     SDL_DestroyTexture(player_icon_texture);
//     print_text(renderer,0,soldier_num," ",coord.x-3,coord.y+30);
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

// _coord mouse_check(SDL_Renderer *renderer)
// {
//     int diameter = 60;
//     _coord temp = {.x = -1,.y = -1};
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             if (power(2,state[i][j].center.x-mouse_pos.x) + power(2,state[i][j].center.y-mouse_pos.y) <= power(2,diameter))
//             {   
//                 temp.x = country[state[i][j].country_num].capital.x; temp.y=country[state[i][j].country_num].capital.y;
//                 return temp;
//             }
//         }   
//     }
//     return temp;
// }

// void printmap(SDL_Renderer *Renderer,_player player[])
// {
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x03ffff05);
//             polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x09ffff00);

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

// void init_country()
// {
//     for (int i = 0; i < country_count; i++)
//     {
//         country[i].player = -1;
//         country[i].color = 0xffffffff;
//         country[i].unitcount = 30;
//     }
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

// void setmap(SDL_Renderer *Renderer,_player player[])
// {    
//     //sin 22.5 = 0.03827 / cos 22.5 = 0.9239
//     //sin 60 = 0.85 / cos60 = 0.5 
//     int diameter = 124;
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
//                 step.y += 25;
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

// void SetColors(_player player[],int playernum)
// {
//     for (int i = 0; i < STATECOUNT.x; i++)
//     {
//         for (int j = 0; j < STATECOUNT.y; j++)
//         {
//             country[state[i][j].country_num].color = 0xdd8888ff+ state[i][j].country_num * 0x006655ff;
//         }
//     }
// }



// _attack_info attacks[150];
// void attack_initializer()
// {
//     atc_num ++;

//     attacks[atc_num].is_done = 0;
//     attacks[atc_num].start_state = F_mouse_state;
//     attacks[atc_num].stop_state = S_mouse_state;
//     attacks[atc_num].soldier_num = country[state[F_mouse_state.x][F_mouse_state.y].country_num].unitcount;
//     attacks[atc_num].passed_unit = 0;

//     for (int i = 0; i < attacks[atc_num].soldier_num; i++)
//     {
//         soldier[state[F_mouse_state.x][F_mouse_state.y].country_num][i].center.x = state[F_mouse_state.x][F_mouse_state.y].center.x;
//         soldier[state[F_mouse_state.x][F_mouse_state.y].country_num][i].center.y = state[F_mouse_state.x][F_mouse_state.y].center.y;
//         soldier[state[F_mouse_state.x][F_mouse_state.y].country_num][i].damage = 1;
//         soldier[state[F_mouse_state.x][F_mouse_state.y].country_num][i].reached = 0;
//         soldier[state[F_mouse_state.x][F_mouse_state.y].country_num][i].dest = S_mouse_state;
//         soldier[state[F_mouse_state.x][F_mouse_state.y].country_num][i].player = country[state[F_mouse_state.x][F_mouse_state.y].country_num].player;

//     }

//     country[state[F_mouse_state.x][F_mouse_state.y].country_num].passed_unit = 0;
//     country[state[S_mouse_state.x][S_mouse_state.x].country_num].is_under_attack = 0;
//     country[state[F_mouse_state.x][F_mouse_state.y].country_num].unitcount = 0;
//     country[state[S_mouse_state.x][S_mouse_state.y].country_num].is_under_attack =1;
// }

// void handling(SDL_Renderer *renderer)
// {
// 	SDL_Event event;
//     while (SDL_PollEvent(&event)) {
//         if (event.type == SDL_QUIT) running = 0;
//         if (event.type == SDL_KEYDOWN)
//         {
//             const Uint8* keys = SDL_GetKeyboardState(NULL);
//         }
//         if( event.type == SDL_MOUSEMOTION)
//         {
//             mouse_pos.x = event.button.x;
//             mouse_pos.y = event.button.y;
//             S_mouse_state.x = mouse_check(renderer).x;
//             S_mouse_state.y = mouse_check(renderer).y;
//         }
//         if(event.type == SDL_MOUSEBUTTONDOWN)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 mouse_is_down = 1;
//                 F_mouse_state = S_mouse_state;
//             }
//         }
//         if(event.type == SDL_MOUSEBUTTONUP)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 mouse_is_down = 0;
//                 if ((S_mouse_state.x != F_mouse_state.x || S_mouse_state.y != F_mouse_state.y) && state[F_mouse_state.x][F_mouse_state.y].avalable && state[S_mouse_state.x][S_mouse_state.y].avalable && country[state[F_mouse_state.x][F_mouse_state.y].country_num].passed_unit == 0 && country[state[F_mouse_state.x][F_mouse_state.y].country_num].player != -1)
//                 {      
//                     attack_initializer();
//                 }
//             }
//         }
// 	}
// }

// int colission_detect(_double_coord obj,_double_coord dest,int diameter)
// {
//     if ((pow(obj.x-dest.x,2) + pow(obj.y-dest.y,2))<= pow(diameter,2))
//     {
//         return 1;
//     }
//     return 0;
// }

// //sets map and intializes the map
// void initializer(SDL_Renderer *Renderer,_player player[])
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
//                 country[i].unitcount+= 1;
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

// void attack_check()
// {
//     int temp = 0;
//     for (int i = 0; i < atc_num; i++)
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

// void selected_state(SDL_Renderer *Renderer)
// {
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
//                         filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x10ffffff);
//                         polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0xffffffff);
//                     }
//                 }
                
//             } 
//         }
//     }
// }

// void print_dynamic_line(SDL_Renderer *Renderer)
// {
//     if (mouse_is_down && state[F_mouse_state.x][F_mouse_state.y].avalable && state[F_mouse_state.x][F_mouse_state.y].country_num != -1  && country[state[F_mouse_state.x][F_mouse_state.y].country_num].player != -1 && state[S_mouse_state.x][S_mouse_state.y].country_num != -1 && state[S_mouse_state.x][S_mouse_state.y].avalable)
//     {
//         lineRGBA(Renderer,state[F_mouse_state.x][F_mouse_state.y].center.x,state[F_mouse_state.x][F_mouse_state.y].center.y,mouse_pos.x,mouse_pos.y,0,160,200,255);
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
//         if (country[i].player != soldier[cntry_num][sold_num].player && country[i].passed_unit > 0)
//         {
//             for (int m = 0; m < country[i].passed_unit; m++)
//             {
//                 if (colission_detect(soldier[i][m].center,soldier[cntry_num][sold_num].center,13))
//                 {
//                     res->x = i;
//                     res->y = m;
//                     return 1;
//                 }
//             }
//         }
//     }
//     return 0;
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
//             soldier[state[F_state.x][F_state.y].country_num][i].center.y +=  10*speed.y;
//             soldier[state[F_state.x][F_state.y].country_num][i].center.x +=  10*speed.x;
//         }
//         else
//         {
//             soldier[state[F_state.x][F_state.y].country_num][i].reached = 1;
//         }
//         if (!soldier[state[F_state.x][F_state.y].country_num][i].reached && soldier[state[F_state.x][F_state.y].country_num][i].damage)
//         {
//             SDL_Texture *soldier_texture = loadimg(soldier_path,Renderer);
//             SDL_Rect soldier_rect = texture_position(soldier_texture,soldier[state[F_state.x][F_state.y].country_num][i].center.x-30,soldier[state[F_state.x][F_state.y].country_num][i].center.y-30,60,60);
//             SDL_RenderCopy(Renderer,soldier_texture,NULL,&soldier_rect);
//             SDL_DestroyTexture(soldier_texture);
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

//     if (attacks[Attack_num].passed_unit != number && frame % 5 == 0)
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
    
// }

// void show_help_message(SDL_Renderer *Renderer)
// {
//     SDL_Texture *TXT_texture = text_texture(Renderer,"your icon is : ",20,TXT_HEADER,255,255,255,255);
//     SDL_Rect text_rect = texture_position(TXT_texture,WIDTH/2-60,10,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,TXT_texture,NULL,&text_rect);
//     SDL_DestroyTexture(TXT_texture);
//     SDL_Texture *icon_texture = loadimg("images/player_icon/1.png",Renderer);
//     SDL_Rect icon_rect = texture_position(icon_texture,WIDTH/2 + 60,0,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,icon_texture,NULL,&icon_rect);
//     SDL_DestroyTexture(icon_texture);
// }

// int is_game_running()
// {
//     for (int i = 0; i < country_count; i++)
//     {
//         if (country[i].player != country[1].player)
//         {
//             return 1;
//         }
//     }
//     return 0;
    
// }

// void end_game(SDL_Renderer *Renderer)
// {
//     if (!is_game_running())
//     {
//         boxColor(Renderer,0,0,WIDTH,HEIGHT,0xef010101);
//         SDL_Texture *winner_message_texture = text_texture(Renderer,"winner is :",100,TXT_HEADER,255,255,255,255);
//         SDL_Rect winner_message_rect = texture_position(winner_message_texture,WIDTH/2-320,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//         SDL_RenderCopy(Renderer,winner_message_texture,NULL,&winner_message_rect);
//         SDL_DestroyTexture(winner_message_texture);
//         SDL_Texture *winner_icon_texture = loadimg("images/player_icon/9.png",Renderer);
//         winner_message_rect = texture_position(winner_icon_texture,WIDTH-200,HEIGHT/2-100,150,200);
//         SDL_RenderCopy(Renderer,winner_icon_texture,NULL,&winner_message_rect);
//         SDL_DestroyTexture(winner_icon_texture);
    
//     }    
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

// int main() {

//     srand(time(NULL)*1000);
//     int player_count = 4;
//     _player player[player_count+1];
    
//     SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
//     IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    
//     TTF_Init();
//     Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC);
//     Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
// 	SDL_Window *window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
//     HEIGHT, SDL_WINDOW_OPENGL);

//     SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    
//     initializer(Renderer,player);
//     setmap(Renderer,player);
//     SetColors(player,player_count);

//     SDL_Texture *BKG_texture = loadimg(BKG_PATH,Renderer);
//     SDL_Rect bkg_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        
// 	time_t starting_time = time(NULL);
    
//     while(running)
// 	{
        
//         SDL_RenderCopy(Renderer,BKG_texture,NULL,&bkg_rect);
//         light_background(frame, Renderer);
//         printmap(Renderer,player);
//         show_help_message(Renderer);

//         frame ++;
//         if(frame == 2*FPS-1)frame = 0;

//         for (int i = 1; i <= atc_num; i++)
//         {
//             print_soldier(Renderer,attacks[i].start_state,attacks[i].stop_state,attacks[i].soldier_num,i);
//         }
        
//         for (int i = 1; i <= atc_num; i++)
//         {
//             attack_check();
//         }
        
        
//         time_t current_time = time(NULL);

//         print_text(Renderer,2,(int)(current_time - starting_time),"time passd:",10,10);
        
//         if (frame % 20 == 0)
//         {
//             solder_increasing(current_time - starting_time);
//         }
        
//         print_dynamic_line(Renderer);
//         selected_state(Renderer);

// 		handling(Renderer);
//         end_game(Renderer);
       
//         SDL_RenderPresent(Renderer);
// 		SDL_Delay(1000/FPS);
//         SDL_RenderClear(Renderer);
// 	}
//     update_leaderboard();
//     save_game();
//     SDL_DestroyWindow(window);
//     SDL_DestroyRenderer(Renderer);
//     IMG_Quit();
//     TTF_Quit();
//     Mix_Quit();
//     SDL_Quit();
//     return 0;
// }