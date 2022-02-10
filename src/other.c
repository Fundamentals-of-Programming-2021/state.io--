#ifndef __OTHER__
#define __OTHER__

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "state_io.h"



void kill_program()
{
    for (int i = 0; i <= STG_WHOLEGAME; i++)
    {
        running[i] = 0;
    }
    
}


int colission_detect(_double_coord obj,_double_coord dest,int diameter)
{
    if ((pow(obj.x-dest.x,2) + pow(obj.y-dest.y,2))<= pow(diameter,2))
    {
        return 1;
    }
    return 0;
}



int sign(int num)
{
    return (num >= 0 ? 1 : -1);
}

int power(int power,int base)
{
    int res = 1;
    for (int i = 0; i < power; i++)
    {
        res *= base;
    }
    return res;
}

#endif