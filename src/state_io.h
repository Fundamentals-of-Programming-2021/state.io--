#ifndef __STATE__IO__
#define __STATE__IO__

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

//for seting txt and posiotion pf texture
#define TXT_HEADER 0
#define TXT_HANDWRITE 1
#define TXT_BODY 2
#define TXR_CENTER -1
#define TXR_DEFAULT_SIZE -1

// defferent pages in game
#define STG_INGAME 3
#define STG_FIRSTPAGE 0
#define STG_USERINPUT 1
#define STG_SELECTMAP 2
#define STG_LEADERBOARD 4
#define STG_WHOLEGAME 5
// size of window
#define WIDTH 700
#define HEIGHT 1000

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
    int num;

}_attack_info;

typedef struct
{
    Uint32 color;
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

typedef struct
{
    int score;
    char user_name[25];
}_score;

typedef struct
{
    _double_coord center[5];
    int owner;
    time_t start_time;

}_potion;

_potion potions[10];
_score score[1000]; 
int player_count;
char BKG_PATH[100];
int stage;
int frame;
bool running[7];
_coord STATECOUNT;
_coord mouse_pos,F_mouse_state,S_mouse_state;
bool mouse_is_down;
int atc_num;
int country_count;
char user_name[100];
bool load_previous;
_state state[100][100];
_country country[100];
_attack_info attacks[150];
SDL_Texture *mouse_texture;
bool play_chunk;
int explosion_num;
_explosion explosion[1000];
_soldier soldier[100][10000];
int selected_option;
bool return_is_down;
int map_num;
bool win;
bool saved_map;

//other : ----------------------------------------------------------------
//makes all runnings 0;
void kill_program();
int sign(int num);
int power(int power,int base);
//detect a cicular collision
int colission_detect(_double_coord obj,_double_coord dest,int diameter);

//potions : ---------------------------------------------------------------
//set potions position and chooses between them
int set_potion(int num);
//just sets the owner to -2 (no_one)
void potion_initializer();
//return potion number of a player that he ownes
int active_potion(int player_num);
//checks if a player has more than one potion or not
int only_one_potion(int player_num);
//sets and checks the effective time of potion
void potion_check(int num);
//places the potion in map
void print_potion(SDL_Renderer *Renderer,int ,int );

//texture_functions : ----------------------------------------------------
SDL_Texture *text_texture(SDL_Renderer *Renderer,char* str,int ptrsize,int flag,int r,int g,int b ,int a);
SDL_Rect texture_position(SDL_Texture *txt_texture,int x,int y,int w,int h);

//mouse : ----------------------------------------------------------------
//checks position of mouse and tells on witch state the mouse is placed
_coord mouse_check(SDL_Renderer *renderer);
//for changing mouse to blue
int is_mouse_attacking();
//for showing this fire mouse
void mouse_cursor(SDL_Renderer *Renderer);


//save_load_scoreboard : -------------------------------------------------
void save_game();
void load_game(char *location);
//count sum of players units return -100 if he looses
int score_counter(int player);

void update_leaderboard();
//checks if a file exist or not
int is_any_load();
//return count of lines of a file 
int file_lines(char *file_address);

void read_leaderboard();
void show_leaderboard(SDL_Renderer *Renderer);
void show_leaderboard_options(SDL_Renderer *Renderer);
void leaderboeard_main(SDL_Window *window);

//attacks : ---------------------------------------------------------------
//increases soldier num
void solder_increasing();
//checks if an attack is done
int reach_check(int atk_num,int count);
//checks collision detect
int soldier_faced(int atk_num,int sold_num,_coord *res);
//sets speed of a soldier
_double_coord set_speed(_double_coord difference);
//initializes an attack with attack information
void attack_initializer(_coord F_state , _coord S_state);
//checks if a country is free from attacks
void free_country(int cntry_num);
//places soldier and the main function of soldier stuff
void print_soldier(SDL_Renderer *Renderer,_coord F_state , _coord S_state  ,int number,int Attack_num);
// ?
int is_game_running();
// end game in time :)
void end_game(SDL_Renderer *Renderer);
//a random kind of AI that attacks a random country that he can conquer
void AI();
//checks if the player has been lost or not
int lossing();
int is_enemy_attacking();

//explosion : (in attacks) : ----------------------------------------------
void shift_explosion(int num);
void show_explosion(SDL_Renderer *Renderer,int exp_num);
void explosion_check();

//map : -------------------------------------------------------------------
//the message your icon is :
void show_help_message(SDL_Renderer *Renderer);
//places armory in capital of a country
void armory_place(SDL_Renderer* renderer,_double_coord coord, Uint32 color,int player,int size,int soldier_num);
void init_country();
void sethex(Sint16 point[][7],_double_coord center,int diameter,_double_coord *state_cent);
//initializes states
void initializer(SDL_Renderer *Renderer);
// ...
void printmap(SDL_Renderer *Renderer);

//decides about shape of a country
int uninier(int i,int j,int group,int chance);
void setmap(SDL_Renderer *Renderer);
void SetColors();
//a little dynmical light
void light_background(int frame,SDL_Renderer *Renderer);
// :)
void rainmaker(SDL_Renderer *renderer);
void selected_state(SDL_Renderer *Renderer);
SDL_Texture *dynamic_background(SDL_Renderer *Renderer,SDL_Texture *BKG_texture,int range,int num_place);

//handling : ------------------------------------------------------------------------
void handling(SDL_Renderer *renderer);
void sound_control(SDL_Renderer *Renderer);


//main_functions : -----------------------------------------------------------------
void main_map(SDL_Window *window);
void main_first_page(SDL_Window *window);
void main_username(SDL_Window *window);
int main_selectmap(SDL_Window *window);

//first_menu : ------------------------------------------------------------------
void first_menu_options(SDL_Renderer *Renderer);

//text_input : ----------------------------------------------------------------------
void textinput_show_options(SDL_Renderer *Renderer);

//select_map : -------------------------------------------------------------
void selectmap_show_options(SDL_Renderer *Renderer);

#endif // !__STATE__IO__