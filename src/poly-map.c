#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>

#define FPS 60

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
const int padding = 100;
const int STATE_COUNT_X = 14;
const int STATE_COUNT_Y = 7;
const Uint32 NonAvalableColor = 0xff990000;

typedef struct
{
    int x;
    int y;

}_point;

typedef struct 
{
    Uint32 color;
    _point initstate;

}_player;

typedef struct
{
    _point place;
    bool avalable;
    Uint32 color;
    int unitcount;
    int player;

}_state;


void armory_place(SDL_Renderer* renderer,_point coord, Uint32 color,int player)
{
        switch (player)
        {
            case (0):
                trigonColor(renderer,coord.x,coord.y-50,coord.x + 42.5,coord.y+25,coord.x -42.5,coord.y+25,color);
                break;
            case (1):
                rectangleColor(renderer,coord.x-30,coord.y-30,coord.x+30,coord.y+30,color);
                break;
            default:
                filledCircleColor(renderer,coord.x,coord.y,40,color);
                break;
        }
}

void drawBox(SDL_Renderer *Renderer,_state state[100][100],int player_num,_player player[]) {
    
    Sint16 diameter = 54;
    Sint16 distance = 50;
    Sint16 polygon_points_x[15][8][9];
    Sint16 polygon_points_y[15][8][9];
    _point center[100][100];
    //sin 22.5 = 0.03827 / cos 22.5 = 0.9239

    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            polygon_points_x[i][j][0] =i * 2 * (distance) + 0 + 100;
            polygon_points_y[i][j][0] =j * 2 * (distance) +(distance - diameter * 0.3827) + 100;
            polygon_points_x[i][j][1] =i * 2 * (distance) +(distance - diameter * 0.3827) + 100;
            polygon_points_y[i][j][1] =j * 2 * (distance) + 0 + 100;
            polygon_points_x[i][j][2] =i * 2 * (distance) +(distance + diameter * 0.3827) + 100;
            polygon_points_y[i][j][2] =j * 2 * (distance) + 0 + 100;
            polygon_points_x[i][j][3] =i * 2 * (distance) +(2*distance) + 100;
            polygon_points_y[i][j][3] =j * 2 * (distance) +(distance - diameter * 0.3827) + 100;
            polygon_points_x[i][j][4] =i * 2 * (distance) +(2*distance) + 100;
            polygon_points_y[i][j][4] =j * 2 * (distance) +(distance + diameter * 0.3827) + 100;
            polygon_points_x[i][j][5] =i * 2 * (distance) +(distance + diameter * 0.3827) + 100;
            polygon_points_y[i][j][5] =j * 2 * (distance) +(2*distance) + 100;
            polygon_points_x[i][j][6] =i * 2 * (distance) +(distance - diameter * 0.3827) + 100;
            polygon_points_y[i][j][6] =j * 2 * (distance) +(2*distance) + 100;
            polygon_points_x[i][j][7] =i * 2 * (distance) + 0 +100;
            polygon_points_y[i][j][7] =j * 2 * (distance) +(distance + diameter * 0.3827) + 100;
            center[i][j].x =  i * 2 * (distance) + distance;
            center[i][j].y =  j * 2 * (distance) + distance;
            
        }
        
    }

    int flag = 0;
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (state[i][j].avalable)
            {
                filledPolygonColor(Renderer,polygon_points_x[i][j],polygon_points_y[i][j],8,state[i][j].color);
                polygonColor(Renderer,polygon_points_x[i][j],polygon_points_y[i][j],8,0xffaa00aa);

                for (int k = 0; k < player_num; k++)
                {
                    if (player[k].initstate.x == i && player[k].initstate.y == j)
                    {
                        armory_place(Renderer,center[i][j],player[k].color,k);
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                {
                    armory_place(Renderer,center[i][j],0xffa0000a,-1);
                }

            }
            else 
            {
                filledPolygonColor(Renderer,polygon_points_x[i][j],polygon_points_y[i][j],8,NonAvalableColor);
                polygonColor(Renderer,polygon_points_x[i][j],polygon_points_y[i][j],8,0xff0c0c0c);
            }

        }
    }
}

void doExit(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
		}
	}
}

void SetPlayerColor(_player player[],int playernum)
{
        player[1].color = 0xffaaaabb;
        player[2].color = 0xffbbaaaa;
}



int main() {

    srand(time(NULL)*1000);

    int player_count = 2;
    _player player[player_count];

    _state state[100][100];
    int temp;

    for (int i = 0; i < player_count; i++)
    {
        player[i].initstate.x = rand() % 3 + i*3;
        player[i].initstate.y = rand() % 3 + i*3;

        while(state[player[i].initstate.x][player[i].initstate.y].avalable == 0 )
        {
            player[i].initstate.x = rand() % 3 + i*3;
            player[i].initstate.y = rand() % 3 + i*3;
        }

        state[player[i].initstate.x][player[i].initstate.y].color = player[i].color;
        state[player[i].initstate.x][player[i].initstate.y].player = i;
    }

    for (int i = 0; i < STATE_COUNT_X; i++)
    {
        for (int j = 0; j < STATE_COUNT_Y; j++)
        {
            temp = rand() ;
            if(temp % 5 == 1 || temp % 5 == 2 )
            {
                state[i][j].avalable = 0;
            }
            else
            {
                state[i][j].avalable = 1;
            }
            state[i][j].color = 0xff11cc22;
            state[i][j].player = -1;
        }
        
    }

    SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
    SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    
	while(1)
	{
        boxColor(Renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0xffffffff);
        rectangleColor(Renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0xff000000);
        boxColor(Renderer,padding,padding,SCREEN_WIDTH-padding,SCREEN_HEIGHT-padding,0xffffff00);
        rectangleColor(Renderer,padding,padding,SCREEN_WIDTH-padding,SCREEN_HEIGHT-padding,0xff0000cc);

        drawBox(Renderer,state,player_count,player);

        SDL_RenderPresent(Renderer);
		doExit();

		SDL_Delay(1000/FPS);
        
	}

    SDL_RenderClear(Renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}