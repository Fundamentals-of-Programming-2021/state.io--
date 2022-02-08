#ifndef __SAVE__LOAD__
#define __SAVE__LOAD__

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


void save_game()
{
    FILE *save;
    char temp[100] = "saves/";
    
    strcat(temp,user_name);
    save = fopen(temp,"w");
    if (save == NULL)
    {
        printf("goooooz\n");
        return;
    }
    
    fprintf(save,"0 %d ",country_count);
    
    for (int i = 0; i < STATECOUNT.x; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            for (int m = 0; m < 6; m++)
            {
                fprintf(save,"%d %d ",state[i][j].points[0][m],state[i][j].points[1][m]);
            }
            fprintf(save,"%f %f %d %d %d ",state[i][j].center.x,state[i][j].center.y,state[i][j].country_num,state[i][j].is_capital,state[i][j].avalable);
        }
    }
    for (int i = 0; i < country_count; i++)
    {
        fprintf(save,"%d %d %x %d %d %d ",country[i].capital.x,country[i].capital.y,country[i].color,country[i].is_under_attack,country[i].player,country[i].unitcount);
    }

    fclose(save);
}

void load_game(char *location)
{
    FILE *load = fopen(location,"r");
    printf("%s\n",location);
    if (load == NULL)
    {
        printf("gooz\n");
        return;
    }
    fscanf(load,"%d %d ",&atc_num,&country_count);
    
    for (int i = 0; i < STATECOUNT.x; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            for (int m = 0; m < 6; m++)
            {
                fscanf(load,"%hd %hd ",&state[i][j].points[0][m],&state[i][j].points[1][m]);
            }
            int temp1,temp2;
            
            fscanf(load,"%lf %lf %d %d %d ",&state[i][j].center.x,&state[i][j].center.y,&state[i][j].country_num ,&temp1,&temp2);     
            state[i][j].is_capital = temp1;
            state[i][j].avalable = temp2;
        }
    }

    for (int i = 0; i < country_count; i++)
    {
        int temp;
        fscanf(load,"%hd %hd %x %d %d %d ",&country[i].capital.x,&country[i].capital.y,&country[i].color,&temp,&country[i].player,&country[i].unitcount);
        country[i].is_under_attack = temp;
    }
    fclose(load);
    
}

int score_counter(int player)
{
    int res = 0;
    for (int i = 0; i < country_count; i++)
    {
        if (country[i].player == player)
        {
            res += country[i].unitcount;
        }
    }
    return res;
    
}

void update_leaderboard()
{
    FILE *leaderboard = fopen("saves/leader-board","r+");
    if (leaderboard == NULL)
    {
        printf("gooz\n");
        return;
    }
    char *buffer = malloc(100);
    int temp;
    bool check = 0;
    while (!feof(leaderboard))
    {
        fscanf(leaderboard,"%s : %d",buffer,&temp);
        if (!strcmp(buffer,user_name))
        {
            check = 1;
            temp = score_counter(0) - score_counter(1) - score_counter(2) - score_counter(3);
            fprintf(leaderboard," %d\n",temp);
            break;
        }
    }

    if (check == 0)
    {
        fprintf(leaderboard,"%s : %d\n",user_name,score_counter(0));
    }
    free(buffer);
    
    
}

int is_any_load()
{
    char buffer[100] = "saves/";
    strcat(buffer,user_name);
    FILE *file = fopen(buffer,"r");
    if (file == NULL)
    {
        return 0;
    }
    return 1;
}

int file_lines(char *file_address)
{
    FILE *file = fopen(file_address,"r");
    char Ch;
    int line_num = 0;

    do
    {
        Ch = fgetc(file);

        if (Ch == '\n')
        {
            line_num++;
        }
    } while (!feof(file));
    

    fclose(file);
    return line_num;
}
char score_board[10][1000];

void read_leaderboard()
{
    FILE *leaderboard = fopen("saves/leader-board","r");
    int head = 0;
    int temp_num = 0;
    while (!feof(leaderboard))
    {
        score[head].score = 0;
        fscanf(leaderboard,"%s :",score[head].user_name);
        for (char i = getc(leaderboard); i != '\n' && i != EOF; i = getc(leaderboard))
        {
            fscanf(leaderboard,"%d",&temp_num);
            score[head].score += temp_num;
        }

        for (int i = 0; i < head; i++)
        {
            if (score[head].score >= score[i].score)
            {
                _score temp;
                temp = score[head];
                score[head] = score[i];
                score[i] = temp;
            }
        }
        head++;
        if (head >= 100)
        {
            head = 0;
        }
        
    }
    fclose(leaderboard);
    char buffer[40];
    char temp[30];

    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }

    for (int i = 0; i < 8; i++)
    {
        sprintf(temp," : %d",score[i].score);
        strcat(buffer,score[i].user_name);
        strcat(buffer,temp);
        strcpy(score_board[i],buffer);
        for (int j = 0; j < 40; j++)
        {
            buffer[j] = '\0';
        }
    }
    
}

void show_leaderboard(SDL_Renderer *Renderer)
{
    SDL_Texture *score_texture;
    SDL_Rect score_rect;

    score_texture = text_texture(Renderer,"top 8 players in last 100 games: ",45,TXT_HEADER,255,255,100,255);
    score_rect = texture_position(score_texture,TXR_CENTER,180,TXR_DEFAULT_SIZE,TXR_CENTER);
    SDL_RenderCopy(Renderer,score_texture,NULL,&score_rect);

    for (int i = 0; i < (file_lines("saves/leader-board") <= 8 ? file_lines("saves/leader-board") : 8); i++)
    {
        score_texture = text_texture(Renderer,score_board[i],60,TXT_HANDWRITE,255,255,100,255);
        score_rect = texture_position(score_texture,TXR_CENTER,250+70*i,TXR_DEFAULT_SIZE,TXR_CENTER);
        SDL_RenderCopy(Renderer,score_texture,NULL,&score_rect);
    }
    SDL_DestroyTexture(score_texture);
}

void show_leaderboard_options(SDL_Renderer *Renderer)
{
    rectangleColor(Renderer,WIDTH-340,830,WIDTH -40,930,0xffffffff);
    SDL_Texture *back_texture = IMG_LoadTexture(Renderer,"menu/back.png");
    SDL_Rect back_rect = texture_position(back_texture,WIDTH-340,830,300,100);

    if (mouse_pos.x >= WIDTH-340 && mouse_pos.y >= 830 && mouse_pos.x <= WIDTH -40 && mouse_pos.y <= 930)
    {
        back_texture = IMG_LoadTexture(Renderer,"menu/back_hovered.png");
        if (mouse_is_down)
        {
            for (int i = 0; i < STG_WHOLEGAME; i++)
            {
                running[i] = 1;
            }
            int temp = strlen(user_name);
            for (int i = 0; i < temp; i++)
            {
                user_name[i] = '\0';
            }
            running[STG_LEADERBOARD] = 0;
            stage = STG_FIRSTPAGE;
        }
        
    }
    
    SDL_RenderCopy(Renderer,back_texture,NULL,&back_rect);
    SDL_DestroyTexture(back_texture);
}

void leaderboeard_main(SDL_Renderer *Renderer)
{
    strcpy(BKG_PATH,"images/background/score board/1.jpg");
    SDL_Texture *BKG_texture = IMG_LoadTexture(Renderer,BKG_PATH);
    SDL_ShowCursor(0);
    read_leaderboard();
    Mix_Music *celebrate_mus = Mix_LoadMUS("music/leader board.mp3");
    Mix_PlayMusic(celebrate_mus,-1);
    while(running[STG_LEADERBOARD])
	{
        frame++;
        if (frame == 8*FPS-1) frame = 0;
        BKG_texture = dynamic_background(Renderer,BKG_texture,4,30);
        
        SDL_RenderCopy(Renderer,BKG_texture,NULL,NULL);
        sound_control(Renderer);
        
        show_leaderboard(Renderer);
        show_leaderboard_options(Renderer);
		handling(Renderer);
        
        mouse_cursor(Renderer);
        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS); 
        SDL_RenderClear(Renderer);
	}
    SDL_DestroyTexture(BKG_texture);
    BKG_texture = NULL;
    Mix_FreeMusic(celebrate_mus);
}

#endif