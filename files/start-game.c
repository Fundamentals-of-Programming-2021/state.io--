// #include <stdio.h>
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

// #define FPS 60
// #define BKG_PATH "images/background/2.bmp"
// #define TXT_HEADER 0
// #define TXT_HANDWRITE 1
// #define TXT_BODY 2

// const int WIDTH = 1800;
// const int HEIGHT = 900;
// char user_name[500];

// typedef struct
// {
//     Sint16 x;
//     Sint16 y;

// }_coord;

// SDL_Texture *text_texture(SDL_Renderer *Renderer,char* str,int ptrsize,int flag,int r,int g,int b ,int a)
// {
//     TTF_Font *font;
//     if (flag == TXT_HEADER)
//     {
//         font = TTF_OpenFont("fonts/header/3.ttf",ptrsize);
//         if (font == NULL)printf("ERROR : %s\n",SDL_GetError());
//         TTF_SetFontStyle(font,TTF_STYLE_BOLD);
//     }
//     else if(flag == TXT_BODY)
//     {

//         font = TTF_OpenFont("fonts/body/1.ttf",ptrsize);
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

// int strlength(char str[])
// {
//     int head = 0;
//     int num = 0;
//     while(str[head])
//     {
//         if (str[head] == ' ' || str[head] == '.')
//         {
//             num += 5;
//         }
//         else
//         {
//             num += 15;
//         }
//         head ++;
//     }
//     return num;
// }
// void handling(void)
// {
// 	SDL_Event event;
//     while (SDL_PollEvent(&event)) {
//         if (event.type == SDL_QUIT) exit(0);

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
//         if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN)
//         {
//             if(event.type == SDL_TEXTINPUT)
//             {
//                 if (strlen(user_name) > 20)
//                 {

//                 }
//                 else
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
//                     exit(0);
//                 }
//             }
//         }
// 	}
// }

// SDL_Texture *loadimg(char* file_location,SDL_Renderer *Renderer)
// {
//     SDL_Surface *imgsurface = SDL_LoadBMP(file_location);
//     if (imgsurface == NULL)
//     {
//         printf("can not open image: %s \n",file_location);
//         return NULL;
//     }
    
//     SDL_Texture *Texture = SDL_CreateTextureFromSurface(Renderer,imgsurface);
//     SDL_FreeSurface(imgsurface);
//     return Texture;
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

// 	SDL_StartTextInput();
//     SDL_SetRenderDrawColor(Renderer,0,0,0,0);
    
//     SDL_Texture *BKG_texture = loadimg(BKG_PATH , Renderer);
//     SDL_Rect BKG_rect;
//     SDL_QueryTexture(BKG_texture,NULL,NULL,&BKG_rect.w,&BKG_rect.h);
//     BKG_rect.x = 900 - BKG_rect.w/2 ; BKG_rect.y = 450 - BKG_rect.h/2;
    
//     SDL_Texture *head_texture = text_texture(Renderer,"STATE.IO",50,TXT_HEADER,255,255,255,255);
//     SDL_Rect head_rect;
//     SDL_QueryTexture(head_texture,NULL,NULL,&head_rect.w,&head_rect.h);
//     head_rect.x = 900 - head_rect.w/2; head_rect.y = 20; 
    
//     SDL_Texture *signiture_texture = text_texture(Renderer,"by amir hossein ravan nakhajvani",200,TXT_HANDWRITE,255,255,255,150);
//     SDL_Rect signiture_rect;
//     SDL_QueryTexture(head_texture,NULL,NULL,&signiture_rect.w,&signiture_rect.h);
//     signiture_rect.w += 100 ; signiture_rect.h += 10;
//     signiture_rect.x = 900 - signiture_rect.w/2; signiture_rect.y = 800; 
    
//     SDL_Rect userTXT_rect;
//     SDL_Texture *userTXT_texture;
    
//     while(1)
// 	{
//         SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);

//         boxColor(Renderer,200,150,1600,200,0xaa010101);
//         userTXT_texture = text_texture(Renderer,user_name,100,TXT_BODY,255,255,255,255);
//         userTXT_rect.w = strlength(user_name);
//         userTXT_rect.h = 40;
//         userTXT_rect.x = 900 - userTXT_rect.w/2; userTXT_rect.y = 155;
        
// 		handling();

//         SDL_RenderCopy(Renderer,userTXT_texture,NULL,&userTXT_rect);
//         SDL_RenderCopy(Renderer,head_texture,NULL,&head_rect);
//         SDL_RenderCopy(Renderer,signiture_texture,NULL,&signiture_rect);
//         SDL_RenderPresent(Renderer);
// 		SDL_Delay(1000/FPS); 
//         SDL_DestroyTexture(userTXT_texture);
//         SDL_RenderClear(Renderer);

// 	}

//     SDL_DestroyTexture(head_texture);
//     SDL_DestroyTexture(BKG_texture);
//     BKG_texture = NULL;
//     SDL_StopTextInput();
//     SDL_DestroyWindow(window);
//     SDL_DestroyRenderer(Renderer);
//     TTF_Quit();
//     SDL_Quit();
//     return 0;
// }
