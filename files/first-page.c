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
// #define BKG_PATH "images/background/5.bmp"
// #define TXT_HEADER 0
// #define TXT_HANDWRITE 1
// #define TXT_BODY 2
// #define TXR_CENTER -1
// #define TXR_DEFAULT_SIZE -1

// bool mouse_is_down = 0;

// const int WIDTH = 1800;
// const int HEIGHT = 900;
// char user_name[500];

// typedef struct
// {
//     Sint16 x;
//     Sint16 y;

// }_coord;

// _coord mouse_pos;
// bool running = 1;

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
//                     running = 0;
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

// void menu_options(SDL_Renderer *Renderer)
// {
//     boxColor(Renderer,900-200,185+350,900+200,260+350,0x55010130);
//     boxColor(Renderer,900-200,270+350,900+200,345+350,0x55300101);
//     boxColor(Renderer,900-200,355+350,900+200,430+350,0x55013001);

//     SDL_Texture *start_txtr = loadimg("menu/Start.bmp",Renderer);
//     SDL_Texture *start_hovered_txtr = loadimg("menu/start_hovered.bmp",Renderer);

//     SDL_Rect start_Rect = {700,185+350,400,75};
//     SDL_Texture *option_txtr = loadimg("menu/options.bmp",Renderer);
//     SDL_Texture *option_hovered_txtr = loadimg("menu/options_hovered.bmp",Renderer);
//     SDL_Rect option_Rect = {700,270+350,400,75};
//     SDL_Texture *exit_hovered_txtr = loadimg("menu/Exit_hovered.bmp",Renderer);
//     SDL_Texture *exit_txtr = loadimg("menu/Exit.bmp",Renderer);
//     SDL_Rect exit_Rect = {700,355+350,400,75};

//     if (mouse_pos.x >= 700 && mouse_pos.x <= 1100 && mouse_pos.y >= 535 && mouse_pos.y <= 610)
//     {
//         SDL_RenderCopy(Renderer,start_hovered_txtr,NULL,&start_Rect);
//     }
//     else if (mouse_pos.x >= 700 && mouse_pos.x <= 1100 && mouse_pos.y >= 620 && mouse_pos.y <= 685)
//     {
//         SDL_RenderCopy(Renderer,option_hovered_txtr,NULL,&option_Rect);
//     }
//     else if (mouse_pos.x >= 700 && mouse_pos.x <= 1100 && mouse_pos.y >= 695 && mouse_pos.y <= 770)
//     {
//         SDL_RenderCopy(Renderer,exit_hovered_txtr,NULL,&exit_Rect);
//         if (mouse_is_down)
//         {
//             running = 0;
//         }
//     }

//     SDL_RenderCopy(Renderer,start_txtr,NULL,&start_Rect);
//     SDL_RenderCopy(Renderer,option_txtr,NULL,&option_Rect);
//     SDL_RenderCopy(Renderer,exit_txtr,NULL,&exit_Rect);
// }

// int main()
// {
//     SDL_Window *window = NULL;
//     SDL_Renderer *Renderer = NULL;
//     srand(time(NULL)*100);
    
//     SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

// 	window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
//     HEIGHT, SDL_WINDOW_OPENGL);

//     Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
//     TTF_Init();
//     Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC);
//     Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
// 	SDL_StartTextInput();
//     SDL_SetRenderDrawColor(Renderer,0,0,0,0);
//     Mix_Music *background_music = Mix_LoadMUS("music/background_music.mp3");
//     if (background_music == NULL)
//     {
//         printf("%s\n",SDL_GetError());
//     }
    

//     SDL_Texture *BKG_texture = loadimg(BKG_PATH , Renderer);
//     SDL_Rect BKG_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
//     SDL_Texture *signiture_texture = text_texture(Renderer,"by amir hossein ravan nakhajvani",100,TXT_HANDWRITE,1,1,1,230);
//     SDL_Rect signiture_rect = texture_position(signiture_texture,TXR_CENTER,780,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
//     Mix_PlayMusic(background_music,-1);

//     while(running)
// 	{
//         SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);
        
// 		handling();
//         menu_options(Renderer);
//         SDL_RenderCopy(Renderer,signiture_texture,NULL,&signiture_rect);
//         SDL_RenderPresent(Renderer);
// 		SDL_Delay(1000/FPS); 
//         SDL_RenderClear(Renderer);
// 	}

//     SDL_DestroyTexture(BKG_texture);
//     BKG_texture = NULL;
//     SDL_StopTextInput();
//     SDL_DestroyWindow(window);
//     SDL_DestroyRenderer(Renderer);
//     Mix_FreeMusic(background_music);
//     Mix_Quit();
//     TTF_Quit();
//     SDL_Quit();
//     return 0;
// }
