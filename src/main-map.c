// #ifndef __MAIN__MAP__
// #define __MAIN__MAP__

// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h>
// #include <stdlib.h>
// #include <math.h>
// #include <stdint.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL2_gfxPrimitives.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>
// #ifndef __STATE__IO
// #include "state_io.h"
// #endif // !__STATE__IO

// void main_map(SDL_Renderer *Renderer)
// {    
//     Mix_Music *playground_music = Mix_LoadMUS("music/play ground.mp3");
//     initializer(Renderer);
//     setmap(Renderer);
//     SetColors();

//     SDL_Texture *BKG_texture = loadimg(BKG_PATH,Renderer);
//     SDL_Rect bkg_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
//     Mix_PlayMusic(playground_music,-1);
//     Mix_VolumeMusic(50); 
// 	time_t starting_time = time(NULL);

//     while(running[STG_INGAME])
// 	{
        
//         SDL_RenderCopy(Renderer,BKG_texture,NULL,&bkg_rect);
//         light_background(frame, Renderer);
//         printmap(Renderer);
//         show_help_message(Renderer);

//         frame ++;
//         if(frame == 8*FPS-1)frame = 0;

//         for (int i = 1; i <= atc_num; i++)
//         {
//             print_soldier(Renderer,attacks[i].start_state,attacks[i].stop_state,attacks[i].soldier_num,i);
//         }
//         attack_check();

//         for (int i = 0; i < explosion_num; i++)
//         {
//             show_explosion(Renderer,i);
//         }
//         explosion_check();
        
//         if (frame % (rand()%120+1) == 0)
//         {
//             AI();
//         } 
        
        
//         time_t current_time = time(NULL);

//         if (frame % 20 == 0)
//         {
//             solder_increasing(current_time - starting_time);
//         }
        
//         selected_state(Renderer);

// 		handling(Renderer);
        
//         end_game(Renderer);

//         mouse_cursor(Renderer);
        
//         SDL_RenderPresent(Renderer);
// 		SDL_Delay(1000/FPS);
//         SDL_RenderClear(Renderer);
// 	}
//     Mix_FreeMusic(playground_music);
//     update_leaderboard();
//     save_game();
// }

// #endif // !__MAIN__MAP__
