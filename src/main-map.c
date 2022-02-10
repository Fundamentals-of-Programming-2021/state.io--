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


void main_map(SDL_Window *window)
{   
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    
    strcpy(BKG_PATH,"images/background/bg 3.jpg");
    Mix_Music *playground_music = Mix_LoadMUS("music/playground.mp3");
    
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
    int active_pot_num[2] = {set_potion(0),set_potion(1)}; 
    potion_initializer();
    bool do_we_have_potion[2] = {rand()%2,rand()%2};
    frame = 0;
    play_chunk = 1;
    while(running[STG_INGAME])
	{
        
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
        SDL_RenderCopy(Renderer,BKG_texture,NULL,NULL);
        light_background(frame, Renderer);
        printmap(Renderer);
        show_help_message(Renderer);
        selected_state(Renderer);

        frame ++;
        if ( 800 <= frame%2000 && frame%2000 <= 1300)
        {
            rainmaker(Renderer);

        }
        else
        {
            Mix_HaltChannel(6);
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

        if (frame % (rand()%50+300) == 0)
        {
            active_pot_num[0] = set_potion(0);
            active_pot_num[1] = set_potion(1);
            do_we_have_potion[0] = rand()%2;
            do_we_have_potion[1] = rand()%2;
        }

        for (int i = 0; i < 2; i++)
        {
            if (do_we_have_potion[i])
            {
                print_potion(Renderer,active_pot_num[i],i);
            }            
        }
        
    
        for (int i = 0; i < 5; i++)
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
    SDL_RenderClear(Renderer);
    Mix_FreeMusic(playground_music);
    SDL_DestroyTexture(BKG_texture);
    SDL_DestroyRenderer(Renderer);
    update_leaderboard();
    save_game();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();

}



#endif // !__MAIN__MAP__
