#ifndef __TEXTURE__FUNCTION__
#define __TEXTURE__SUNCTION__

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
    return txtTexture;    
}

SDL_Texture *Texture;
SDL_Texture *loadimg(char* file_location,SDL_Renderer *Renderer)
{
    SDL_Surface *imgsurface = IMG_Load(file_location);
    if (imgsurface == NULL)
    {
        printf("can not open image: %s \n",file_location);
        return NULL;
    }
    
    Texture = SDL_CreateTextureFromSurface(Renderer,imgsurface);
    SDL_FreeSurface(imgsurface);
    return Texture;
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

#endif //!__TEXTURE__FUNCTION__
