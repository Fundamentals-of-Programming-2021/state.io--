// #ifndef __HANDLE__EVENTS__
// #define __HANDLE__EVENTS__

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
// #include <SDL2/SDL_image.h>
// #ifndef __STATE__IO
// #include "state_io.h"
// #endif // !__STATE__IO"

// void handling(SDL_Renderer *renderer)
// {
// 	SDL_Event event;
//     while (SDL_PollEvent(&event)) {
//         if (event.type == SDL_QUIT)
//         {
//             for (int i = 0; i <= STG_WHOLEGAME; i++)
//             {
//                 running[i] = 0;
//             }
            
//         }
//         if (event.type == SDL_KEYDOWN)
//         {

//         }
//         if( event.type == SDL_MOUSEMOTION)
//         {
//             mouse_pos.x = event.button.x;
//             mouse_pos.y = event.button.y;
//             if (stage == STG_INGAME)
//             {
//                 S_mouse_state.x = mouse_check(renderer).x;
//                 S_mouse_state.y = mouse_check(renderer).y;
//             }
            
            
//         }
//         if(event.type == SDL_MOUSEBUTTONDOWN)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 mouse_is_down = 1;
//                 if (stage == STG_INGAME)
//                 {
//                     F_mouse_state = S_mouse_state;
//                 }
//             }
//         }
//         if(event.type == SDL_MOUSEBUTTONUP)
//         {
//             if(event.button.button == SDL_BUTTON_LEFT)
//             {
//                 mouse_is_down = 0;
//                 if (stage == STG_INGAME)
//                 {
//                     if ((S_mouse_state.x != F_mouse_state.x || S_mouse_state.y != F_mouse_state.y) && state[F_mouse_state.x][F_mouse_state.y].avalable && state[S_mouse_state.x][S_mouse_state.y].avalable && country[state[F_mouse_state.x][F_mouse_state.y].country_num].passed_unit == 0 && country[state[F_mouse_state.x][F_mouse_state.y].country_num].player == 0)
//                     {
//                         Mix_Chunk *yes_chunk = Mix_LoadWAV("music/yes.wav");
//                         Mix_PlayChannel(0,yes_chunk,0);
//                         attack_initializer(F_mouse_state,S_mouse_state);
//                     }
//                 }
//             }
//         }
// 	}
// }

// #endif // !__HANDLE__EVENTS__
