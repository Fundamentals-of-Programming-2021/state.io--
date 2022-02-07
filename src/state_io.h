#pragma once


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

#define FPS 50
#define TXT_HEADER 0
#define TXT_HANDWRITE 1
#define TXT_BODY 2
#define TXR_CENTER -1
#define TXR_DEFAULT_SIZE -1

#define STG_INGAME 3
#define STG_FIRSTPAGE 0
#define STG_USERINPUT 1
#define STG_SELECTMAP 2
#define STG_LEADERBOARD 4
#define STG_WHOLEGAME 5

typedef struct
{
    Sint16 x;
    Sint16 y;

}_coord;

typedef struct
{
    _coord start_state;
    _coord stop_state;
    int soldier_num;
    bool is_done;
    int passed_unit;

}_attack_info;

typedef struct
{
    int num;
    Uint32 color;
    int passed_unit;
    _coord capital;
    bool is_under_attack;
    int player;
    int unitcount;

}_country;

typedef struct
{
    double x;
    double y;

}_double_coord;

typedef struct
{
    Sint16 points[2][7];
    _double_coord center;
    int country_num;
    bool is_capital;
    bool avalable;

}_state;

typedef struct
{
    _double_coord center;
    int radius;
    bool reached;
    bool damage;
    _coord dest;
    int player;

}_soldier;

typedef struct
{
    int exp_frame;
    _double_coord center;
    bool is_done;   

}_explosion;

int player_count = 4;
char BKG_PATH[100] = {"images/background/bg 1.jpg"};
int stage = STG_INGAME;
const int WIDTH = 700;
const int HEIGHT = 1000;
int frame = 0;
bool running[6] = {1,1,1,1,1,1};
_coord STATECOUNT = {.x = 7 , .y = 8};
_coord mouse_pos,F_mouse_state,S_mouse_state;
bool mouse_is_down = 0;
int atc_num = 0;
int country_count = 0;
char user_name[100] = "amir";
bool load_previous = 0;
_state state[100][100];
_country country[100];
_attack_info attacks[150];
SDL_Texture *mouse_texture;
bool play_chunk = 1;

int explosion_num = 0;
_explosion explosion[1000];

_soldier soldier[100][10000];


#include "other.c"
#include "texture_functions.c"
#include "attack.c"
#include "save_load_scoreboard.c"
#include "map.c"
#include "mouse.c"
#include "handle_events.c"
#include "main-map.c"