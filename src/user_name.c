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

// #define FPS 60
// #define TXT_HEADER 0
// #define TXT_HANDWRITE 1
// #define TXT_BODY 2
// #define TXR_CENTER -1
// #define TXR_DEFAULT_SIZE -1

// char BKG_PATH[100] = {"images/background/3.bmp"};
// const int WIDTH = 1800;
// const int HEIGHT = 900;
// char user_name[25];
// int frame = 0;
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
//     SDL_Rect BKG_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);

    
//     SDL_Rect userTXT_rect;
//     SDL_Texture *userTXT_texture;
    
//     SDL_Texture *message_texture = text_texture(Renderer,"please ENTER username :",60,TXT_HEADER,255,255,255,150);
//     SDL_Rect messsage_rect = texture_position(message_texture,TXR_CENTER,450,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
//     while(1)
// 	{
//         frame++;
//         if (frame == 99) frame = 0;

//         BKG_texture = dynamic_background(Renderer,BKG_texture);
        
//         SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);

//         boxColor(Renderer,600,474+100,1200,476+100,0x332288aa);
//         boxColor(Renderer,600,574+100,1200,576+100,0x332288aa);
//         userTXT_texture = text_texture(Renderer,user_name,50,TXT_BODY,255,255,255,255);
//         userTXT_rect = texture_position(userTXT_texture,TXR_CENTER,600,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        
// 		handling();

//         SDL_RenderCopy(Renderer,message_texture,NULL,&messsage_rect);
//         SDL_RenderCopy(Renderer,userTXT_texture,NULL,&userTXT_rect);
        
//         SDL_RenderPresent(Renderer);
// 		SDL_Delay(1000/FPS); 
//         SDL_DestroyTexture(userTXT_texture);
//         SDL_RenderClear(Renderer);

// 	}
//     SDL_DestroyTexture(message_texture);
//     SDL_DestroyTexture(BKG_texture);
//     BKG_texture = NULL;
//     SDL_StopTextInput();
//     SDL_DestroyWindow(window);
//     SDL_DestroyRenderer(Renderer);
//     TTF_Quit();
//     SDL_Quit();

//     return 0;
// }