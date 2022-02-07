// // #include <stdio.h>
// #include <stdbool.h>
// #include <string.h>
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

// bool running = 1;
// bool mouse_is_down = 0;
// bool return_is_down = 0;
// char BKG_PATH[100] = {"images/background/3.jpg"};
// const int WIDTH = 700;
// const int HEIGHT = 1000;
// char user_name[25];
// int frame = 0;

// typedef struct
// {
//     Sint16 x;
//     Sint16 y;

// }_coord;

// _coord mouse_pos;

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
//     TTF_CloseFont(font);
//     SDL_FreeSurface(txtsurface);
//     return txtTexture;    
// }

// void handling(void)
// {
// 	SDL_Event event;
//     while (SDL_PollEvent(&event)) {
//         if (event.type == SDL_QUIT) running = 0;

//         if( event.type == SDL_MOUSEMOTION)
//         {
//             mouse_pos.x = event.button.x;
//             mouse_pos.y = event.button.y;
//         }

//         if(event.type == SDL_MOUSEBUTTONDOWN)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 mouse_is_down = 1;
//                 printf("pressed on (%d,%d)\n", event.button.x, event.button.y);
//             }
//         }
//         if(event.type == SDL_MOUSEBUTTONUP)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 mouse_is_down = 0;
//                 printf("finished on (%d,%d)\n", event.button.x, event.button.y);
//             }
//         }
//         if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN)
//         {
//             if(event.type == SDL_TEXTINPUT)
//             {
//                 if(strlen(user_name) < 20)
//                 {
//                     user_name[strlen(user_name)] = *(event.text.text);
//                     user_name[strlen(user_name)] = '\0';
//                 }
//             }
//             else if (event.type == SDL_KEYDOWN)
//             {
//                 if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(user_name) > 0)
//                 {
//                     user_name[strlen(user_name)-1] = '\0';
//                 }
//                 else if (event.key.keysym.sym == SDLK_RETURN && strlen(user_name) > 0)
//                 {
//                     return_is_down = 1;
//                 }
//                 else if (event.key.keysym.sym == SDLK_RIGHT)
//                 {
//                     map_num ++;
//                     if (map_num > 3)
//                     {
//                         map_num = -1;
//                     }
//                 }
//                 else if (event.key.keysym.sym == SDLK_LEFT)
//                 {
//                     map_num --;
//                     if (map_num < -1)
//                     {
//                         map_num = 3;
//                     }
//                 }
//                 else if (event.key.keysym.sym == SDLK_UP)
//                 {
//                     map_num -= 2;
//                     if (map_num < -1)
//                     {
//                         map_num = -1;
//                     }
//                 }
//                 else if (event.key.keysym.sym == SDLK_DOWN)
//                 {
//                     map_num += 2;
//                     if (map_num > 3)
//                     {
//                         map_num = -1;
//                     }
//                 }
//             }
//         }
//         if (event.type == SDL_KEYUP)
//         {
//             if (event.key.keysym.sym == SDLK_RETURN)
//             {
//                 return_is_down = 0;
//             }
            
//         }
        
// 	}
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

// SDL_Texture *dynamic_background(SDL_Renderer *Renderer,SDL_Texture *BKG_texture)
// {
//     if (frame % 60 == 0)
//     {
//         int bkg_num = rand()%3+1;
//         BKG_PATH[18] = (char)(bkg_num + '0');
//         BKG_texture = loadimg(BKG_PATH , Renderer);
//     }
//     return BKG_texture;
// }

// _coord center = { .x = 310 , .y = 45};
// void sound_control(SDL_Renderer *Renderer)
// {
//     SDL_Texture *sound_texture = loadimg("images/icon/sound_icon.png",Renderer);
//     SDL_Rect sound_rect = texture_position(sound_texture,25,HEIGHT - 55,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,sound_texture,NULL,&sound_rect);
//     SDL_DestroyTexture(sound_texture);
    
//     boxColor(Renderer,100,44+920,310,46+920,0xccffffff);
//     boxColor(Renderer,center.x-10,center.y-10+920,center.x+10,center.y+10+920,0xff4040aa);
//     static int flag = 0;
//     if (mouse_pos.x >= 100 && mouse_pos.x <= 310 && mouse_pos.y >= 32+920 && mouse_pos.y <= 58+920)
//     {
//         if (mouse_is_down)
//         {
//             flag = 1;
//         }
        
//     }

//     if(flag)
//     {
//         rectangleColor(Renderer,center.x-10,center.y-10+920,center.x+10,center.y+10+920,0xff9090ff);
//         if (mouse_pos.x >= 310)
//         {
//             center.x = 310;
//         }
//         else if (mouse_pos.x <= 100)
//         {
//             center.x = 100;
//         }
//         else
//         {
//             center.x = mouse_pos.x;
//         }            
//     }
//     else if(mouse_is_down == 0 && flag)flag = 0;

//     double percent = (center.x-100)*128/210;
//     Mix_VolumeMusic(percent);
    
// }

// void show_options(SDL_Renderer *Renderer)
// {
//     rectangleColor(Renderer,200,300,500,400,0xffffffff);
//     rectangleColor(Renderer,20,450,320,550,0xffffffff);
//     rectangleColor(Renderer,380,450,680,550,0xffffffff);
//     rectangleColor(Renderer,20,600,320,700,0xffffffff);
//     rectangleColor(Renderer,380,600,680,700,0xffffffff);
//     rectangleColor(Renderer,0,750,WIDTH,850,0xffffffff);
//     SDL_Texture *options_texture;
//     SDL_Rect options_rect;
    
//     options_texture = text_texture(Renderer,"map 1",80,TXT_HANDWRITE,255,255,255,255);
//     options_rect = texture_position(options_texture,20+50,450,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

//     options_texture = text_texture(Renderer,"map 2",80,TXT_HANDWRITE,255,255,255,255);
//     options_rect = texture_position(options_texture,380+50,450,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

//     options_texture = text_texture(Renderer,"map 3",80,TXT_HANDWRITE,255,255,255,255);
//     options_rect = texture_position(options_texture,20+50,600,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

//     options_texture = text_texture(Renderer,"map 4",80,TXT_HANDWRITE,255,255,255,255);
//     options_rect = texture_position(options_texture,380+50,600,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);    
//     if ((mouse_pos.x >= 200 && mouse_pos.y >= 300 && mouse_pos.x <= 500 && mouse_pos.y <= 400) || map_num == -1)
//     {
//         options_texture = loadimg("menu/new map_hovered.png",Renderer);
//     }
//     else
//     {
//         options_texture = loadimg("menu/new map.png",Renderer);
//     }
//     options_rect = texture_position(options_texture,200,300,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);    
//     SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);
    
//     if (return_is_down && map_num != -1)
//     {
//         options_texture = loadimg("menu/select map_hovered.png",Renderer);
//     }
//     else
//     {
//         options_texture = loadimg("menu/select map.png",Renderer);
//     }

//     if ((mouse_pos.x >= 380 && mouse_pos.y >= 450 && mouse_pos.x <= 680 && mouse_pos.y <= 550) || map_num == 1)
//     {
//         rectangleColor(Renderer,380,450,680,550,0xffff11ff);
//     }
//     else if ((mouse_pos.x >= 20 && mouse_pos.y >= 450 && mouse_pos.x <= 350 && mouse_pos.y <= 550) || map_num == 0)
//     {
//         rectangleColor(Renderer,20,450,320,550,0xffff11ff);
//     }
//     else if ((mouse_pos.x >= 380 && mouse_pos.y >= 600 && mouse_pos.x <= 680 && mouse_pos.y <= 700) || map_num == 3)
//     {
//         rectangleColor(Renderer,380,600,680,700,0xffff11ff);
//     }
//     else if ((mouse_pos.x >= 20 && mouse_pos.y >= 600 && mouse_pos.x <= 350 && mouse_pos.y <= 700) || map_num == 2)
//     {
//         rectangleColor(Renderer,20,600,320,700,0xffff11ff);
//     }
//     options_rect = texture_position(options_texture,200,750,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
//     SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);
    
//     SDL_DestroyTexture(options_texture);

// }

// int main()
// {
//     SDL_Window *window = NULL;
//     SDL_Renderer *Renderer = NULL;
//     srand(time(NULL)*1000);
    
//     SDL_Init(SDL_INIT_VIDEO);

// 	window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
//     HEIGHT, SDL_WINDOW_OPENGL);

//     Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
//     TTF_Init();
//     IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

// 	SDL_StartTextInput();
//     SDL_SetRenderDrawColor(Renderer,0,0,0,0);
    
//     SDL_Texture *BKG_texture = loadimg(BKG_PATH , Renderer);
//     SDL_Rect BKG_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);

        
//     while(running)
// 	{
//         frame++;
//         if (frame == 2*FPS-1) frame = 0;


//         BKG_texture = dynamic_background(Renderer,BKG_texture);
        
//         SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);
//         sound_control(Renderer);

        
//         show_options(Renderer);
// 		handling();
        
//         SDL_RenderPresent(Renderer);
// 		SDL_Delay(1000/FPS); 
//         SDL_RenderClear(Renderer);

// 	}
//     IMG_Quit();
//     SDL_DestroyTexture(BKG_texture);
//     BKG_texture = NULL;
//     SDL_StopTextInput();
//     SDL_DestroyWindow(window);
//     SDL_DestroyRenderer(Renderer);
//     TTF_Quit();
//     SDL_Quit();

//     return 0;
// }
