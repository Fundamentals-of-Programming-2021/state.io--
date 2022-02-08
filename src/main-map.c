#ifndef __MAIN__MAP__
#define __MAIN__MAP__

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
#include "state_io.h"


void main_map(SDL_Renderer *Renderer)
{   
    
    strcpy(BKG_PATH,"images/background/bg 1.jpg");
    Mix_Music *playground_music = Mix_LoadMUS("music/play ground.mp3");
    
    if (!load_previous)
    {
        mouse_is_down = 0;
        atc_num = 0;
        country_count = 0;
        play_chunk = 1;
        explosion_num = 0;
        selected_option = 0;
        map_num = -2;
        initializer(Renderer); 
    }
    setmap(Renderer);
    
    SetColors();


    SDL_Texture *BKG_texture = IMG_LoadTexture(Renderer,BKG_PATH);
    SDL_Rect bkg_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
    Mix_PlayMusic(playground_music,-1);
    Mix_VolumeMusic(50); 
	time_t starting_time = time(NULL);
    time_t current_time;
    int l[2] = {rand() % country_count,rand()%country_count} ,k[2] = {rand() % country_count,rand() % country_count} ,b[2] = {rand()%3,rand()%3};
    for (int i = 0; i < 4; i++)
    {
        potions[i].owner = -2;
    }
    
    while(running[STG_INGAME])
	{
        
        SDL_RenderCopy(Renderer,BKG_texture,NULL,&bkg_rect);
        light_background(frame, Renderer);
        printmap(Renderer);
        show_help_message(Renderer);
        selected_state(Renderer);

        frame ++;
        if ( 250 <= frame && frame <= 2000)
        {
            rainmaker(Renderer);

        }
        
        if(frame == 15990)frame = 0;

        for (int i = 1; i <= atc_num; i++)
        {
            if (attacks[i].is_done == 0)
            {
                print_soldier(Renderer,attacks[i].start_state,attacks[i].stop_state,attacks[i].soldier_num,attacks[i].num);
            }
        }

        current_time = time(NULL);

        for (int i = 0; i < explosion_num; i++)
        {
            show_explosion(Renderer,i);
        }
        explosion_check();
        
        if (frame % (rand()%120+1) == 0 && current_time - starting_time > 5)
        {
            AI();
        } 

        if (frame % 200 == 0)
        {
            for (int i = 0; i < 2; i++)
            {   
                l[i] = rand()%country_count;
                k[i] = rand()%country_count;
                if (k[i] == l[i])
                {
                    k[i] = rand()%country_count;
                }
                
                b[i] = rand()%4;
            }
        }

        for (int i = 0; i < 2; i++)
        {
            print_potion(Renderer,l[i],k[i],b[i],i);
        }
        
    
        for (int i = 0; i < 4; i++)
        {
            potion_check(i);        
        }
        
        
        
        
        if (frame % 20 == 0)
        {
            solder_increasing();
        }
        

		handling(Renderer);
        end_game(Renderer);
        mouse_cursor(Renderer);

        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS);
        SDL_RenderClear(Renderer);  
	}
    Mix_FreeMusic(playground_music);
    SDL_DestroyTexture(BKG_texture);
    update_leaderboard();
    save_game();

}



#endif // !__MAIN__MAP__
