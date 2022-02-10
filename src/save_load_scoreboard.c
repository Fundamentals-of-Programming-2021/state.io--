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


//saves game with your user_name
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
//loads_game based on user_name
void load_game(char *location)
{
    FILE *load = fopen(location,"r");
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
//sum pf all units that a player owns
// -100 if he looses
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
    if (res == 0)
    {
        return -100;
    }
    
    return res;
}

//updates_leaderboard in saves/leaderboard
void update_leaderboard()
{
    FILE *leaderboard = fopen("saves/leader-board","a");
    if (leaderboard == NULL)
    {
        printf("gooz\n");
        return;
    }
    fprintf(leaderboard,"%s : %d\n",user_name,score_counter(0));  
}
//check if a file existes or not
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
//counts line count of a file
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

//saves all scores in format user_name : score
char score_board[100][1000];
void read_leaderboard()
{
    FILE *leaderboard = fopen("saves/leader-board","r");
    int head = 0;
    int temp_num = 0;
    while (!feof(leaderboard))
    {
        score[head].score = 0;
        fscanf(leaderboard,"%s : %d\n",score[head].user_name,&score[head].score);
        head++;
        if (head >= 100)
        {
            head = 0;
        }
    }
    fclose(leaderboard);

    for (int i = 0; i < head + 1; i++)
    {
        for (int j = i+1; j < head + 1; j++)
        {
            if (!strcmp(score[i].user_name,score[j].user_name) || !strcmp(score[i].user_name,"/n") || score[i].user_name == NULL)
            {
                score[i].score += score[j].score;
                strcpy(score[j].user_name," ");
            }
        }
    }

    for (int i = 0; i < head+1; i++)
    {
        for (int j = i+1; j < head+1; j++)
        {
            if (score[i].score <= score[j].score)
            {
                _score temp;
                temp = score[j];
                score[j] = score[i];
                score[i] = temp;
            }
        }
    }

    char buffer[40];
    char temp[30];

    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }
    int count = (file_lines("saves/leader-board") < 8 ? file_lines("saves/leader-board") : 8);
    for (int i = 0; i <= count; i++)
    {
        if (strcmp(score[i].user_name," "))
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
        else
        {
            strcpy(score_board[i]," ");
            if (count < head)
            {
                count++;
            }
            
        }
    }
    for (int i = 0; i <= count; i++)
    {
        if (!strcmp(score_board[i]," ") || !strcmp(score_board[i]," : 0") || score_board[i] == NULL)
        {
            for (int j = i; j <= count; j++)
            {
                strcpy(score_board[j],score_board[j+1]);
            }
        }
    }
    
    
    
}

//show leader board in renderer in format user_name : score
void show_leaderboard(SDL_Renderer *Renderer)
{
    SDL_Texture *score_texture;
    SDL_Rect score_rect;

    score_texture = text_texture(Renderer,"top 8 players in last 100 games: ",45,TXT_HEADER,255,255,100,255);
    score_rect = texture_position(score_texture,TXR_CENTER,180,TXR_DEFAULT_SIZE,TXR_CENTER);
    SDL_RenderCopy(Renderer,score_texture,NULL,&score_rect);

    for (int i = 0; i < (file_lines("saves/leader-board") <= 8 ? file_lines("saves/leader-board") : 8); i++)
    {
        if (!strcmp(score_board[i]," ") || !strcmp(score_board[i]," : 0") || score_board[i] == NULL)
        {
            for (int j = i; j <= 10; j++)
            {
                strcpy(score_board[j],score_board[j+1]);
            }
        }
        score_texture = text_texture(Renderer,score_board[i],60,TXT_HANDWRITE,255,255,100,255);
        score_rect = texture_position(score_texture,TXR_CENTER,250+70*i,TXR_DEFAULT_SIZE,TXR_CENTER);
        SDL_RenderCopy(Renderer,score_texture,NULL,&score_rect);
    }
    SDL_DestroyTexture(score_texture);
}

//back option in page
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


void leaderboeard_main(SDL_Window *window)
{
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    strcpy(BKG_PATH,"images/background/score board/1.jpg");
    SDL_Texture *BKG_texture = IMG_LoadTexture(Renderer,BKG_PATH);
    SDL_ShowCursor(0);
    read_leaderboard();
    //celebrate music :)
    //pretty fun
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
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyTexture(BKG_texture);
    BKG_texture = NULL;
    Mix_FreeMusic(celebrate_mus);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

#endif