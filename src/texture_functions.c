#ifndef __TEXTURE__
#define __TEXTURE__

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

SDL_Texture *text_texture(SDL_Renderer *Renderer,char* str,int ptrsize,int flag,int r,int g,int b ,int a)
{
    TTF_Font *font;
    if (flag == TXT_HEADER)
    {
        font = TTF_OpenFont("fonts/header/2.ttf",ptrsize);
        if (font == NULL)printf("ERROR : %s\n",SDL_GetError());
        // TTF_SetFontStyle(font,TTF_STYLE_BOLD);
    }
    else if(flag == TXT_BODY)
    {

        font = TTF_OpenFont("fonts/body/2.ttf",ptrsize);
        if (font == NULL)printf("ERROR : %s\n",SDL_GetError());
    
    }
    else if(flag == TXT_HANDWRITE)
    {
        font = TTF_OpenFont("fonts/hand_write/2.ttf",ptrsize);
        if (font == NULL)printf("ERROR : %s\n",SDL_GetError());
    }

    SDL_Color color = {r,g,b,a};
    SDL_Surface *txtsurface = TTF_RenderText_Solid(font,str,color);
    SDL_Texture *txtTexture = SDL_CreateTextureFromSurface(Renderer,txtsurface);
    SDL_FreeSurface(txtsurface);
    TTF_CloseFont(font);
    return txtTexture;    
}

SDL_Rect texture_position(SDL_Texture *txt_texture,int x,int y,int w,int h)
{
    SDL_Rect txt_rect = {.x = x , .y = y , .h = h , .w = w};
    SDL_Rect txt_info;
    SDL_QueryTexture(txt_texture,NULL,NULL,&txt_info.w,&txt_info.h);

    if (x == TXR_CENTER)
    {
        txt_rect.x = WIDTH/2 - txt_info.w/2;
    }
    if (y == TXR_CENTER)
    {
        txt_rect.y = HEIGHT/2 - txt_info.h/2;
    }
    if (w == TXR_DEFAULT_SIZE)
    {
        txt_rect.w = txt_info.w;
    }
    if (h == TXR_DEFAULT_SIZE)
    {
        txt_rect.h = txt_info.h;
    }
    return txt_rect;
}

SDL_Texture *dynamic_background(SDL_Renderer *Renderer,SDL_Texture *BKG_texture,int range,int num_place)
{
    if (frame % 60 == 0)
    {
        int bkg_num = rand()%range;
        BKG_PATH[num_place] = (char)(bkg_num + '0');
        BKG_texture = IMG_LoadTexture(Renderer,BKG_PATH);
    }
    return BKG_texture;
}

void print_text(SDL_Renderer *renderer,int flag,int number,char* str,int x , int y)
{
    char *buffer = malloc(sizeof(char)*100);
    if (flag == 0)
    {
        sprintf(buffer,"%d",number);
    }
    else if(flag == 1)
    {
        sprintf(buffer,"%s",str);
    }
    else if(flag == 2)
    {
        sprintf(buffer,"%s %d",str,number);
    }
    stringRGBA(renderer,x,y,buffer,255,255,255,255);
}



void selected_state(SDL_Renderer *Renderer)
{
    if (F_mouse_state.x != -1 && F_mouse_state.y != -1 && mouse_is_down && country[state[F_mouse_state.x][F_mouse_state.y].country_num].player == 0)
    {
        if (state[F_mouse_state.x][F_mouse_state.y].avalable && state[F_mouse_state.x][F_mouse_state.y].country_num != -1)
        {
            for (int i = 0; i < STATECOUNT.x; i++)
            {
                for (int j = 0; j < STATECOUNT.y; j++)
                {
                    if (state[i][j].country_num == state[F_mouse_state.x][F_mouse_state.y].country_num)
                    {
                        filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x30010101);
                        polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0xff010101);
                    }
                }
                
            } 
        }
    }

    for (int i = 0; i < country_count; i++)
    {
        if (active_potion(country[i].player) == 0)
        {
            for (int m = 0; m < STATECOUNT.x; m++)
            {
                for (int n = 0; n < STATECOUNT.y; n++)
                {
                    if (state[m][n].country_num == i)
                    {
                        filledPolygonColor(Renderer,state[m][n].points[0],state[m][n].points[1],6,0x5500ffff);
                        polygonColor(Renderer,state[m][n].points[0],state[m][n].points[1],6,0xff00ffff);
                    }
                    
                }
                
            }
            
        }
        if (active_potion(country[i].player) == 1)
        {
            for (int m = 0; m < STATECOUNT.x; m++)
            {
                for (int n = 0; n < STATECOUNT.y; n++)
                {
                    if (state[m][n].country_num == i)
                    {
                        filledPolygonColor(Renderer,state[m][n].points[0],state[m][n].points[1],6,0x5500ff00);
                        polygonColor(Renderer,state[m][n].points[0],state[m][n].points[1],6,0xff00ff00);
                    }
                    
                }
                
            }
            
        }if (active_potion(country[i].player) == 2)
        {
            for (int m = 0; m < STATECOUNT.x; m++)
            {
                for (int n = 0; n < STATECOUNT.y; n++)
                {
                    if (state[m][n].country_num == i)
                    {
                        filledPolygonColor(Renderer,state[m][n].points[0],state[m][n].points[1],6,0x550000ff);
                        polygonColor(Renderer,state[m][n].points[0],state[m][n].points[1],6,0xff0000ff);
                    }
                    
                }
                
            }
            
        }
        if (active_potion(country[i].player) == 3)
        {
            for (int m = 0; m < STATECOUNT.x; m++)
            {
                for (int n = 0; n < STATECOUNT.y; n++)
                {
                    if (state[m][n].country_num == i)
                    {
                        filledPolygonColor(Renderer,state[m][n].points[0],state[m][n].points[1],6,0x55ffff00);
                        polygonColor(Renderer,state[m][n].points[0],state[m][n].points[1],6,0xffffff00);
                    }
                    
                }
                
            }
            
        }
    }
    

    if (S_mouse_state.x != -1 && S_mouse_state.y != -1)
    {
        if (state[S_mouse_state.x][S_mouse_state.y].avalable && state[S_mouse_state.x][S_mouse_state.y].country_num != -1)
        {
            for (int i = 0; i < STATECOUNT.x; i++)
            {
                for (int j = 0; j < STATECOUNT.y; j++)
                {
                    if (state[i][j].country_num == state[S_mouse_state.x][S_mouse_state.y].country_num)
                    {
                        filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x10ffffff);
                        polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0xffffffff);
                    }
                }
                
            } 
        }
    }
}

#endif //!__TEXTURE__
