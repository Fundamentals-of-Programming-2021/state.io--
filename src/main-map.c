// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h>
// #include <stdlib.h>
// #include <math.h>
// #include <stdint.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL2_gfxPrimitives.h>
// #include <SDL2/SDL_image.h>

// #define FPS 60

// const int WIDTH = 1600;
// const int HEIGHT = 900;
// const int STATE_COUNT_X = 10;
// const int STATE_COUNT_Y = 5;
// const Uint32 NonAvalableColor = 0xff990000;

// typedef struct
// {
//     int x;
//     int y;

// }_point;

// typedef struct 
// {
//     Uint32 color;
//     _point initstate;

// }_player;

// typedef struct
// {
//     _point place;
//     bool avalable;
//     Uint32 color;
//     int unitcount;
//     int player;

// }_state;


// void doExit(void)
// {
// 	SDL_Event event;

// 	while (SDL_PollEvent(&event))
// 	{
// 		switch (event.type)
// 		{
// 			case SDL_QUIT:
// 				exit(0);
// 				break;
// 		}
// 	}
// }
// void next_point(_point *P,int belongs_to[WIDTH][HEIGHT])
// {
//     _point step;
//     for (int i = 0; i < 9; i++)
//     {  
//         step.x = rand() % 3 - 1;
//         step.y = rand() % 3 - 1;
//         if (belongs_to[p->x+step.x][p->y+step.y] == -1 )
//         {
//             break;
//         }
        
        
//     }
    
//     if (belongs_to())
//     {
//         /* code */
//     }
    
// }

// void initmap(SDL_Renderer *renderer,Uint32 color,int player,int belongs_to[WIDTH][HEIGHT])
// {
//     int area_size,state_num = 0;
//     _point P;
//     int map_paddig = 100;
    
//     P.x = map_paddig ; P.y = map_paddig; 

//     while (P.x != WIDTH - map_padding || P.y != WIDTH - map_paddig)
//     {
//         area_size = rand() % 50 + 250;
//         for (int i = 0; i < area_size; i++)
//         {
//             if (belongs_to[P.x][P.y] == -1)
//             {
//                 belongs_to[P.x][P.y] = state_num;
//             }
//             next_point(&p,belongs_to);
//         }
//         state_num ++;
//     }
    
    
    
// }
// int main()
// {
    
//     SDL_Init(SDL_INIT_VIDEO);
//     int belongs_to[WIDTH][HEIGHT];

//     for (int i = 0; i < WIDTH; i++)
//     {
//         for (int j = 0; j < HEIGHT; j++)
//         {
//             belongs_to[i][j] = -1;
//         }
//     }

//     SDL_Window *window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
//     SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

//     SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

//     while(1)
//     {

//         SDL_RenderPresent(renderer);
// 		doExit();
// 		SDL_Delay(1000/FPS);

//     }

//     SDL_RenderClear(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
    
//     return 0;
// }
