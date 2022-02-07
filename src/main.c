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

typedef struct
{
    int score;
    char user_name[25];
}_score;

_score score[1000]; 
int player_count = 4;
char BKG_PATH[100] = {"images/background/bg 1.jpg"};
int stage = STG_FIRSTPAGE;
const int WIDTH = 700;
const int HEIGHT = 1000;
int frame = 0;
bool running[7] = {1,1,1,1,1,1,1};
_coord STATECOUNT = {.x = 7 , .y = 8};
_coord mouse_pos,F_mouse_state,S_mouse_state;
bool mouse_is_down = 0;
int atc_num = 0;
int country_count = 0;
char user_name[100];
bool load_previous = 0;
_state state[100][100];
_country country[100];
_attack_info attacks[150];
SDL_Texture *mouse_texture;
bool play_chunk = 1;
int explosion_num = 0;
_explosion explosion[1000];
_soldier soldier[100][10000];
int selected_option = 0;
bool return_is_down = 0;
int map_num = -2;

void kill_program()
{
    for (int i = 0; i <= STG_WHOLEGAME; i++)
    {
        running[i] = 0;
    }
    
}

int sign(int num)
{
    return (num > 0 ? 1 : -1);
}

int power(int power,int base)
{
    int res = 1;
    for (int i = 0; i < power; i++)
    {
        res *= base;
    }
    return res;
}

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

SDL_Texture *loadimg(char* file_location,SDL_Renderer *Renderer)
{
    SDL_Texture *Texture;
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

_coord mouse_check(SDL_Renderer *renderer)
{
    int diameter = 60;
    _coord temp = {.x = -1,.y = -1};
    for (int i = 0; i < STATECOUNT.x; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            if (power(2,state[i][j].center.x-mouse_pos.x) + power(2,state[i][j].center.y-mouse_pos.y) <= power(2,diameter))
            {   
                temp.x = country[state[i][j].country_num].capital.x; temp.y=country[state[i][j].country_num].capital.y;
                return temp;
            }
        }   
    }
    return temp;
}

int is_mouse_attacking()
{
    if (S_mouse_state.x != -1 && F_mouse_state.x != -1 && S_mouse_state.y != -1 && F_mouse_state.y != -1 && mouse_is_down && state[F_mouse_state.x][F_mouse_state.y].avalable && state[F_mouse_state.x][F_mouse_state.y].country_num != -1  && country[state[F_mouse_state.x][F_mouse_state.y].country_num].player != -1 && state[S_mouse_state.x][S_mouse_state.y].country_num != -1 && state[S_mouse_state.x][S_mouse_state.y].avalable)
    {
        return 1;
    }
    return 0;
}

void mouse_cursor(SDL_Renderer *Renderer)
{
    
    if (mouse_is_down)
    {
        mouse_texture = loadimg("images/cursor/cursor 3.png",Renderer);
    }
    else
    {
        mouse_texture = loadimg("images/cursor/cursor 1.png",Renderer);
    } 
    if (stage == STG_INGAME && is_mouse_attacking())
    {
        mouse_texture = loadimg("images/cursor/cursor 2.png",Renderer);
    }
    
    
    SDL_Rect mouse_rect = texture_position(mouse_texture,mouse_pos.x,mouse_pos.y,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,mouse_texture,NULL,&mouse_rect);
}

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
    
    fprintf(save,"%d %d ",atc_num,country_count);
    
    for (int i = 0; i < STATECOUNT.x; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            for (int m = 0; m < 6; m++)
            {
                fprintf(save,"%d %d ",state[i][j].points[0][m],state[i][j].points[1][m]);
            }
            fprintf(save,"%f %f %d %d %d ",state[i][j].center.x,state[i][j].center.y,state[i][j].country_num ,state[i][j].is_capital,state[i][j].avalable);
        }
    }
    for (int i = 0; i < country_count; i++)
    {
        fprintf(save,"%d %d %x %d %d %d %d %d ",country[i].capital.x,country[i].capital.y,country[i].color,country[i].is_under_attack,country[i].num,country[i].passed_unit,country[i].player,country[i].unitcount);
    }

    for (int i = 1; i <= atc_num; i++)
    {
        fprintf(save,"%d %d %d %d %d %d %d ",attacks[i].is_done,attacks[i].passed_unit,attacks[i].soldier_num,attacks[i].start_state.x,attacks[i].start_state.y,attacks[i].stop_state.x,attacks[i].stop_state.y);
    }

    for (int i = 0; i < country_count; i++)
    {
        for (int j = 0; j < country[i].passed_unit; j++)
        {
            fprintf(save,"%f %f %d %hd %hd %hd %hd ",soldier[i][j].center.x,soldier[i][j].center.y,soldier[i][j].damage,soldier[i][j].dest.x,soldier[i][j].dest.y,soldier[i][j].player,soldier[i][j].reached);
        }
    }
    
    
    fclose(save);
}

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
        fscanf(load,"%hd %hd %x %d %d %d %d %d ",&country[i].capital.x,&country[i].capital.y,&country[i].color,&temp,&country[i].num,&country[i].passed_unit,&country[i].player,&country[i].unitcount);
        country[i].is_under_attack = temp;
    }

    for (int i = 1; i <= atc_num; i++)
    {
        int temp1;
        fscanf(load,"%d %d %d %hd %hd %hd %hd ",&temp1,&attacks[i].passed_unit,&attacks[i].soldier_num,&attacks[i].start_state.x,&attacks[i].start_state.y,&attacks[i].stop_state.x,&attacks[i].stop_state.y);
        attacks[i].is_done = temp1;
    }
    for (int i = 0; i < country_count; i++)
    {
        for (int j = 0; j < country[i].passed_unit; j++)
        {
            int temp1,temp2;
            fscanf(load,"%lf %lf %d %hd %hd %d %d ",&soldier[i][j].center.x,&soldier[i][j].center.y,&temp1,&soldier[i][j].dest.x,&soldier[i][j].dest.y,&soldier[i][j].player,&temp2);
            soldier[i][j].damage = temp1;
            soldier[i][j].reached = temp2;
        }
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
    FILE *leaderboard = fopen("saves/leader-board","a");
    if (leaderboard == NULL)
    {
        printf("gooz\n");
        return;
    }
    fprintf(leaderboard,"%s : %d\n",user_name,score_counter(0));
}

// ----------------------------------------------------------------------------------------------------

int colission_detect(_double_coord obj,_double_coord dest,int diameter)
{
    if ((pow(obj.x-dest.x,2) + pow(obj.y-dest.y,2))<= pow(diameter,2))
    {
        return 1;
    }
    return 0;
}

void solder_increasing(time_t time)
{
    int speed = 1;
    
    if (time)
    {
       for(int i = 0; i < country_count ; i++)
       {
            if (country[i].unitcount < 75 && !country[i].is_under_attack && country[i].player != -1 )
            {
                if(country[i].player == 0)country[i].unitcount += 2;
                else country[i].unitcount+= 1;
            }                
       }
    }
}

void shift_attack(int num)
{
    _attack_info temp;
    for (int i = num; i <= atc_num; i++)
    {
        temp = attacks[i];
        attacks[i] = attacks[i+1];
        attacks[i+1] = temp;
    }
    
}

int reach_check(int cntry_num,int count)
{
    for (int i = 0; i < count; i++)
    {
        if (soldier[cntry_num][i].reached == 0)
        {
            return 0;
        }
    }
    return 1;
}

int soldier_faced(int cntry_num,int sold_num,_coord *res)
{
    for (int i = 0; i <= country_count; i++)
    {
        if (soldier[i][0].player != soldier[cntry_num][sold_num].player && country[i].passed_unit > 0)
        {
            for (int m = 0; m < country[i].passed_unit; m++)
            {
                if (colission_detect(soldier[i][m].center,soldier[cntry_num][sold_num].center,25) && soldier[i][m].damage && soldier[cntry_num][sold_num].damage)
                {
                    explosion[explosion_num].center.x = (soldier[i][m].center.x+soldier[cntry_num][sold_num].center.x)/2;
                    explosion[explosion_num].center.y = (soldier[i][m].center.y+soldier[cntry_num][sold_num].center.y)/2;
                    explosion[explosion_num].exp_frame = 0;
                    explosion[explosion_num].is_done = 0;
                    explosion_num ++;

                    Mix_Chunk *bubble_chunk = Mix_LoadWAV("music/bubble.wav");
                    Mix_PlayChannel(-1,bubble_chunk,0); 
                    res->x = i;
                    res->y = m;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void attack_check()
{
    int temp = 0;
    for (int i = 1; i < atc_num; i++)
    {
        if (attacks[i].is_done == 1)
        {
            shift_attack(i);
            attacks[i].is_done = 0;
            temp++;
        }
    }
    atc_num -= temp;
}

_double_coord set_speed(_double_coord difference)
{
    _double_coord speed;
        if (difference.x == 0)
    {
        if (difference.y > 0)
        {
            speed.y = 1;
        }
        else
        {
            speed.y = -1;
        }        
        speed.x = 0;
    }
    else if (difference.y == 0)
    {
        if (difference.x > 0)
        {
            speed.x = 1;
        }
        else
        {
            speed.x = -1;
        }        
        speed.y = 0;
    }
    else
    {
        speed.y = difference.y/sqrt(pow(difference.x,2)+pow(difference.y,2));
        speed.x = difference.x/sqrt(pow(difference.x,2)+pow(difference.y,2));
    }
    return speed;
}

void attack_initializer(_coord F_state , _coord S_state)
{
    atc_num ++;

    attacks[atc_num].is_done = 0;
    attacks[atc_num].start_state = F_state;
    attacks[atc_num].stop_state = S_state;
    attacks[atc_num].soldier_num = country[state[F_state.x][F_state.y].country_num].unitcount;
    attacks[atc_num].passed_unit = 0;

    for (int i = 0; i < attacks[atc_num].soldier_num; i++)
    {
        soldier[state[F_state.x][F_state.y].country_num][i].center.x = state[F_state.x][F_state.y].center.x;
        soldier[state[F_state.x][F_state.y].country_num][i].center.y = state[F_state.x][F_state.y].center.y;
        soldier[state[F_state.x][F_state.y].country_num][i].damage = 1;
        soldier[state[F_state.x][F_state.y].country_num][i].reached = 0;
        soldier[state[F_state.x][F_state.y].country_num][i].dest = S_state;
        soldier[state[F_state.x][F_state.y].country_num][i].player = country[state[F_state.x][F_state.y].country_num].player;

    }

    country[state[F_state.x][F_state.y].country_num].passed_unit = 0;
    country[state[S_state.x][S_state.x].country_num].is_under_attack = 0;
    country[state[F_state.x][F_state.y].country_num].unitcount = 0;
    country[state[S_state.x][S_state.y].country_num].is_under_attack =1;
}

void print_soldier(SDL_Renderer *Renderer,_coord F_state , _coord S_state  ,int number,int Attack_num)
{
    _double_coord difference = {.x = state[S_state.x][S_state.y].center.x - state[F_state.x][F_state.y].center.x , .y = state[S_state.x][S_state.y].center.y - state[F_state.x][F_state.y].center.y};
    _double_coord speed;
    
    char soldier_path[100];

    speed = set_speed(difference);
    
    if (speed.x < 0)
    {
        strcpy(soldier_path,"images/soldier_2_1.png");
    }
    else
    {
        strcpy(soldier_path,"images/soldier_1_2.png");
    }
    
    //just for less typing 
    _coord res;
    SDL_Texture *soldier_texture = loadimg(soldier_path,Renderer);
    for (int i = 0; i < attacks[Attack_num].passed_unit ; i++)
    {
        soldier_path[15] = (char)soldier[state[F_state.x][F_state.y].country_num][i].player + '1';

        if (soldier_faced(state[F_state.x][F_state.y].country_num,i,&res))
        {
            
            soldier[state[F_state.x][F_state.y].country_num][i].damage = 0;
            soldier[res.x][res.y].center = state[soldier[res.x][res.y].dest.x][soldier[res.x][res.y].dest.y].center;
            soldier[res.x][res.y].damage = 0;
            soldier[state[F_state.x][F_state.y].country_num][i].reached = 1;
            soldier[res.x][res.y].reached = 1;
            soldier[state[F_state.x][F_state.y].country_num][i].center = soldier[state[S_state.x][S_state.y].country_num][i].center;
        }
        if (!colission_detect(soldier[state[F_state.x][F_state.y].country_num][i].center,state[S_state.x][S_state.y].center,30))
        {
            soldier[state[F_state.x][F_state.y].country_num][i].center.y +=  12*speed.y;
            soldier[state[F_state.x][F_state.y].country_num][i].center.x +=  12*speed.x;
        }
        else
        {
            soldier[state[F_state.x][F_state.y].country_num][i].reached = 1;
        }
        if (!soldier[state[F_state.x][F_state.y].country_num][i].reached && soldier[state[F_state.x][F_state.y].country_num][i].damage)
        {
            soldier_texture = loadimg(soldier_path,Renderer);
            SDL_Rect soldier_rect = texture_position(soldier_texture,soldier[state[F_state.x][F_state.y].country_num][i].center.x-30,soldier[state[F_state.x][F_state.y].country_num][i].center.y-30,60,60);
            SDL_RenderCopy(Renderer,soldier_texture,NULL,&soldier_rect);
        }
        else if(soldier[state[F_state.x][F_state.y].country_num][i].reached && soldier[state[F_state.x][F_state.y].country_num][i].damage)
        {
            if (soldier[state[F_state.x][F_state.y].country_num][i].player != country[state[soldier[state[F_state.x][F_state.y].country_num][i].dest.x][soldier[state[F_state.x][F_state.y].country_num][i].dest.y].country_num].player)
            {
                country[state[S_state.x][S_state.y].country_num].unitcount--;
                if (country[state[S_state.x][S_state.y].country_num].unitcount <= 0)
                {
                    country[state[S_state.x][S_state.y].country_num].player = soldier[state[F_state.x][F_state.y].country_num][i].player;
                    country[state[S_state.x][S_state.y].country_num].unitcount = 0;
                }
            }
            else
            {
                country[state[S_state.x][S_state.y].country_num].unitcount++;
            }
            
            soldier[state[F_state.x][F_state.y].country_num][i].damage = 0;
        }        
    }

    if (attacks[Attack_num].passed_unit != number && frame % 5 == 0)
    {
        attacks[Attack_num].passed_unit++;
        country[state[F_state.x][F_state.y].country_num].passed_unit++;
    }

    if (reach_check(state[F_state.x][F_state.y].country_num,number))
    {
        attacks[Attack_num].is_done = 1;
        country[state[S_state.x][S_state.y].country_num].is_under_attack = 0;
        country[state[F_state.x][F_state.y].country_num].passed_unit = 0;
    }
    SDL_DestroyTexture(soldier_texture);
}

void show_help_message(SDL_Renderer *Renderer)
{
    SDL_Texture *TXT_texture = text_texture(Renderer,"your icon is : ",20,TXT_HEADER,255,255,255,255);
    SDL_Rect text_rect = texture_position(TXT_texture,WIDTH/2-60,10,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,TXT_texture,NULL,&text_rect);
    SDL_DestroyTexture(TXT_texture);
    SDL_Texture *icon_texture = loadimg("images/player_icon/0.png",Renderer);
    SDL_Rect icon_rect = texture_position(icon_texture,WIDTH/2 + 60,0,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,icon_texture,NULL,&icon_rect);
    SDL_DestroyTexture(icon_texture);
}

int is_game_running()
{
    int k= 0;        
    while (country[k].player == -1)k++;

    for (int i = 0; i < country_count; i++)
    {
        if(country[i].player != country[k].player && country[i].player != -1)
            return 1;
    }
    

    for (int i = 0; i < country_count; i++)
    {
        for (int j = 0; j < country[i].passed_unit; j++)
        {
            if (soldier[i][j].player != 0)
            {
                return 1;
            }
        }
    }

    return 0;
    
}

void end_game(SDL_Renderer *Renderer)
{   
    if (!is_game_running())
    {
        Mix_Chunk *end_soundEffect;
        SDL_Texture *texture;
        SDL_Rect rect;

        
        int k= 0;        
        while (country[k].player == -1)k++;
        
        if (country[k].player != 0 && country[k].player != -1)
        {
            end_soundEffect = Mix_LoadWAV("music/loose.wav");
            texture = text_texture(Renderer,"you loose !",100,TXT_HEADER,255,255,255,255);

        }
        else
        {
            end_soundEffect = Mix_LoadWAV("music/win.wav");
            texture = text_texture(Renderer,"you won !",100,TXT_HEADER,255,255,255,255);

        }

        if (play_chunk)
        {
            Mix_PlayChannel(0,end_soundEffect,0);
            play_chunk = 0;
        }
        if (!Mix_Playing(0))
        {
            Mix_FreeChunk(end_soundEffect);
        }
        

        boxColor(Renderer,0,0,WIDTH,HEIGHT,0xef010101);
        rectangleColor(Renderer,380,850,680,950,0xffffffff);
        rect = texture_position(texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        SDL_RenderCopy(Renderer,texture,NULL,&rect);

        texture = loadimg("menu/score board.png",Renderer);

        if (mouse_pos.x >= 380 && mouse_pos.x <= 680 && mouse_pos.y >= 850 && mouse_pos.y <= 950)
        {
            texture = loadimg("menu/score board_hovered.png",Renderer);
            
            if (mouse_is_down)
            {
                
                mouse_is_down = 0;
                running[STG_LEADERBOARD] = 1;
                stage = STG_LEADERBOARD;
                running[STG_INGAME] = 0;
            }
        }
        rect = texture_position(texture,380,850,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        SDL_RenderCopy(Renderer,texture,NULL,&rect);
        SDL_DestroyTexture(texture);
    }    
}

void shift_explosion(int num)
{
    for (int i = 0; i < explosion_num; i++)
    {
        explosion[i] = explosion[i+num];
    }
}

void show_explosion(SDL_Renderer *Renderer,int exp_num)
{   
    if (explosion[exp_num].exp_frame == 4)
    {
        explosion[exp_num].is_done = 1;
        return;
    }
    explosion[exp_num].exp_frame ++;
    
    SDL_Rect explosion_src_rect;
    SDL_Rect explosion_dst_rect;
    SDL_Texture *explosion_texture;
    explosion_texture = loadimg("images/explosion/3.png",Renderer);
    explosion_src_rect.x = (explosion[exp_num].exp_frame%4)*200 ; explosion_src_rect.y = (explosion[exp_num].exp_frame/4+1)*100 ,explosion_src_rect.w = 100;explosion_src_rect .h = 100;
    explosion_dst_rect.x = explosion[exp_num].center.x-40 ; explosion_dst_rect.y = explosion[exp_num].center.y-40 ; explosion_dst_rect.w = 80 ; explosion_dst_rect.h = 80;
    SDL_RenderCopy(Renderer,explosion_texture,&explosion_src_rect,&explosion_dst_rect);
    SDL_DestroyTexture(explosion_texture);

}

void explosion_check()
{
    int temp = 0;
    for (int i = 0; i < explosion_num; i++)
    {
        if (explosion[i].is_done == 1)
        {
            temp++;
        }
    }
    shift_explosion(temp);
    explosion_num -= temp;
}

//the most simplest AI in the world
void AI()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = rand()%country_count; j < country_count; j++)
        {
            if (country[j].player == i && country[j].passed_unit == 0)
            {
                for (int l = rand()%country_count; l < country_count; l++)
                {
                    if (is_game_running() && country[l].player != i && country[j].unitcount >= country[l].unitcount && country[j].unitcount > 10)
                    {
                        attack_initializer(country[j].capital,country[l].capital);
                    }
                }
            }
        }
    }
}

// -----------------------------------------------------

void armory_place(SDL_Renderer* renderer,_double_coord coord, Uint32 color,int player,int size,int soldier_num)
{
    SDL_Texture *player_icon_texture;
    SDL_Rect player_icon_rect;
    if (player == 0)
    {
        player_icon_texture = loadimg("images/player_icon/0.png",renderer);
        player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-19,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    }
    else if (player == 1)
    {
        player_icon_texture = loadimg("images/player_icon/1.png",renderer);
        player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-14,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);        
    }
    else if (player == 2)
    {
        player_icon_texture = loadimg("images/player_icon/2.png",renderer);
        player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-31,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);        
    }
    else if (player == 3)
    {
        player_icon_texture = loadimg("images/player_icon/3.png",renderer);
        player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-16,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);        
    }
    else
    {
        player_icon_texture = loadimg("images/player_icon/4.png",renderer);
        player_icon_rect = texture_position(player_icon_texture,coord.x-20,coord.y-30,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    }
    SDL_RenderCopy(renderer,player_icon_texture,NULL,&player_icon_rect);
    SDL_DestroyTexture(player_icon_texture);
    print_text(renderer,0,soldier_num," ",coord.x-3,coord.y+30);
}

void init_country()
{
    for (int i = 0; i < country_count; i++)
    {
        country[i].player = -1;
        country[i].color = 0xffffffff;
        country[i].unitcount = 30;
    }
}

//makes all of a hex shape points
void sethex(Sint16 point[][7],_double_coord center,int diameter,_double_coord *state_cent)
{
    point[0][0] = center.x - diameter/2;
    point[0][1] = center.x - diameter/4;
    point[0][2] = center.x + diameter/4;
    point[0][3] = center.x + diameter/2;
    point[0][4] = center.x + diameter/4;
    point[0][5] = center.x - diameter/4;
    point[1][0] = center.y;
    point[1][1] = center.y - ((diameter/2)*0.85);
    point[1][2] = center.y - ((diameter/2)*0.85);
    point[1][3] = center.y;
    point[1][4] = center.y + ((diameter/2)*0.85);
    point[1][5] = center.y + ((diameter/2)*0.85);

    state_cent->x = center.x;
    state_cent->y = center.y; 
}

void initializer(SDL_Renderer *Renderer)
{
    int temp;
    for (int i = 0; i < STATECOUNT.x ; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            temp = rand() ;
            if(temp % 5 == 1 || temp % 5 == 2 || temp % 5 == 3)
            {
                state[i][j].avalable = 0;
            }
            else
            {
                state[i][j].avalable = 1;
            }
            state[i][j].country_num = -1;
            state[i][j].is_capital = 0;
        }
    }
    for (int i = 0; i < 1000; i++)
    {
        explosion[i].is_done = 1;
        explosion[i].exp_frame = 0;
    }
    
}

void printmap(SDL_Renderer *Renderer)
{
    for (int i = 0; i < STATECOUNT.x; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x01ffff05);
            polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x02ffff00);

            if (state[i][j].country_num != -1 && state[i][j].avalable)
            {
                filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,country[state[i][j].country_num].color);
                polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,country[state[i][j].country_num].color);
                if (state[i][j].is_capital)
                {
                    armory_place(Renderer,state[i][j].center,0xffffffff,country[state[i][j].country_num].player,18,country[state[i][j].country_num].unitcount);
                }
            }
        }
    }
}

int uninier(int i,int j,int group,int chance)
{
    if (chance && state[i][j].country_num == -1)
    {
        state[i][j].country_num = group;
        state[i][j].avalable = 1;
        return 1;
    }
    return 0;
}

void setmap(SDL_Renderer *Renderer)
{    
    //sin 22.5 = 0.03827 / cos 22.5 = 0.9239
    //sin 60 = 0.85 / cos60 = 0.5 
    int diameter = 124;
    _coord for_akhavans_sake = {rand()%10-3,rand()%10-5};
    _double_coord step;
    if (load_previous)
    {
        char buffer[100] = "saves/";
        strcat(buffer,user_name);
        load_game(buffer);
    }
    else
    {
        for (int i = 0 ; i < STATECOUNT.x ; i++)
        {
            for (int j = 0; j < STATECOUNT.y ; j++)
            {
                if (i % 2 == 1)
                {
                    step.x = WIDTH/2 + ((i-STATECOUNT.x/2) * diameter * 0.75);
                    step.y = HEIGHT/2 + ((j-STATECOUNT.y/2) * diameter *0.85);
                }
                else
                {
                    step.x = WIDTH/2 + ((i-STATECOUNT.x/2) * diameter * 0.75);
                    step.y = HEIGHT/2 + ((j-STATECOUNT.y/2) * diameter *0.85) + diameter/2*0.85;
                }
                step.y += 25 + for_akhavans_sake.y;
                step.x += for_akhavans_sake.x;
                sethex(state[i][j].points,step,diameter,&state[i][j].center);    
            }   
        }

        int country_size;

        for (int i = 1; i < STATECOUNT.x-1; i ++)
        {
            for (int j = 1; j < STATECOUNT.y-1; j ++)
            {
                country_size = 0;
                if (state[i][j].country_num == -1 && state[i][j].avalable)
                {
                    state[i][j].is_capital = 1;
                    country[country_count].capital.x = i;
                    country[country_count].capital.y = j;
                    country_size += uninier(i,j,country_count,1);
                    country_size += uninier(i+1,j,country_count,rand()%2);
                    country_size += uninier(i,j+1,country_count,rand()%2);
                    country_size += uninier(i-1,j,country_count,rand()%2);
                    country_size += uninier(i,j-1,country_count,rand()%2);
                    if (country_size == 1)
                    {
                        country_size += uninier(i+1,j,country_count,1);
                        country_size += uninier(i,j+1,country_count,1);
                        country_size += uninier(i-1,j,country_count,1);
                        country_size += uninier(i,j-1,country_count,1);
                    }
                    country_count++;                    
                } 
            }
        }

        init_country();

        int n = 0;
        int m = 0;
        for (int i = 0; i < 4; i++)
        {
            if (i < country_count)
            {       
                do
                {
                    n = rand()%STATECOUNT.x;
                    m = rand()%STATECOUNT.y;
                } while (state[n][m].avalable == 0 || country[state[m][n].country_num].player != -1);
                country[state[m][n].country_num].player = i;        
            }
        }

    }
}

void SetColors()
{
    for (int i = 0; i < STATECOUNT.x; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            country[state[i][j].country_num].color = 0x88050505+ state[i][j].country_num * 0x00885515;
        }
    }
}

void light_background(int frame,SDL_Renderer *Renderer)
{
    static Uint32 color = 0x50252525;
    static int temp = 1;

    if (frame % 3 == 0)
    {
        color += temp * 0x00010101;
    }
    
    if (color == 0x50000000)
    {
        temp = 1;
    }
    else if (color == 0x50505050)
    {
        temp = -1;
    }
    boxColor(Renderer,0,0,WIDTH,HEIGHT,color);
}

void rainmaker(SDL_Renderer *renderer)
{
    if (rand()%2 == 1)
    {
        int length = 8;
        for (int i = 0; i < 50; i++)
        {
            _coord randomplace ={.x = rand()%WIDTH, .y = rand()%HEIGHT};
            lineColor(renderer,randomplace.x,randomplace.y,randomplace.x+length,randomplace.y+length,0xffff55ff);
            lineColor(renderer,randomplace.x-1,randomplace.y-1,randomplace.x+length,randomplace.y+length,0xffffff55);
            lineColor(renderer,randomplace.x-3,randomplace.y-3,randomplace.x+length,randomplace.y+length,0xffff5555);
        }
    }
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

// -----------------------------------------------------------------------------------------------
void handling(SDL_Renderer *renderer)
{
	SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
        {
            kill_program();
        }
        if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN)
        {
            if(event.type == SDL_TEXTINPUT)
            {
                if (stage == STG_USERINPUT)
                {
                    if (strlen(user_name) > 20)
                    {

                    }
                    else
                    {
                        user_name[strlen(user_name)] = *(event.text.text);
                        user_name[strlen(user_name)] = '\0';
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(user_name) > 0)
                {
                    if (stage == STG_USERINPUT)
                    {
                        user_name[strlen(user_name)-1] = '\0';
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN)
                {
                    return_is_down = 1;
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    if (stage == STG_FIRSTPAGE)
                    {
                        selected_option -= 1;
                        if (selected_option < 1)
                        {
                            selected_option = 1;
                        }                    
                    }
                    else if (stage == STG_SELECTMAP)
                    {
                        map_num -= 2;
                        if (map_num < -1)
                        {
                            map_num = -1;
                        }
                    }
                    
                }
                else if (event.key.keysym.sym == SDLK_DOWN)
                {
                    if (stage == STG_FIRSTPAGE)
                    {
                        selected_option += 1;
                        if (selected_option > 2)
                        {
                            selected_option = 2;
                        }
                    }
                    else if (stage == STG_SELECTMAP)
                    {
                        map_num += 2;
                        if (map_num > 3)
                        {
                            map_num = -1;
                        }
                    }
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    if (stage == STG_USERINPUT)
                    {
                        selected_option += 1;
                        if (selected_option > 1)
                        {
                            selected_option = 1;
                        }
                    }
                    else if (stage == STG_SELECTMAP)
                    {
                        map_num ++;
                        if (map_num > 3)
                        {
                            map_num = -1;
                        }
                    }
                }
                else if (event.key.keysym.sym == SDLK_LEFT)
                {
                    if (stage == STG_USERINPUT)
                    {
                        selected_option -= 1;
                        if (selected_option < 0)
                        {
                            selected_option = 0;
                        }                    
                    }
                    else if (stage == STG_SELECTMAP)
                    {
                        map_num --;
                        if (map_num < -1)
                        {
                            map_num = 3;
                        }
                    }
                }
            }
        }
        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_RETURN)
            {
                return_is_down = 0;
            }
        }
        if( event.type == SDL_MOUSEMOTION)
        {
            mouse_pos.x = event.button.x;
            mouse_pos.y = event.button.y;
            if (stage == STG_INGAME)
            {
                S_mouse_state.x = mouse_check(renderer).x;
                S_mouse_state.y = mouse_check(renderer).y;
            }
            
            
        }
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_is_down = 1;
                if (stage == STG_INGAME)
                {
                    F_mouse_state = S_mouse_state;
                }
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_is_down = 0;
                if (stage == STG_INGAME)
                {
                    if (S_mouse_state.x != -1 && F_mouse_state.x != -1 && S_mouse_state.y != -1 && F_mouse_state.y != -1 && ( S_mouse_state.x != F_mouse_state.x || S_mouse_state.y != F_mouse_state.y) && state[F_mouse_state.x][F_mouse_state.y].avalable && state[S_mouse_state.x][S_mouse_state.y].avalable && country[state[F_mouse_state.x][F_mouse_state.y].country_num].passed_unit == 0 && country[state[F_mouse_state.x][F_mouse_state.y].country_num].player == 0)
                    {
                        Mix_Chunk *yes_chunk = Mix_LoadWAV("music/yes.wav");
                        Mix_PlayChannel(0,yes_chunk,0);
                        attack_initializer(F_mouse_state,S_mouse_state);
                    }
                }
            }
        }
	}
}

void main_map(SDL_Renderer *Renderer)
{    
    strcpy(BKG_PATH,"images/background/bg 1.jpg");
    Mix_Music *playground_music = Mix_LoadMUS("music/play ground.mp3");
    initializer(Renderer);
    setmap(Renderer);
    SetColors();

    SDL_Texture *BKG_texture = loadimg(BKG_PATH,Renderer);
    SDL_Rect bkg_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
    Mix_PlayMusic(playground_music,-1);
    Mix_VolumeMusic(50); 
	time_t starting_time = time(NULL);
    time_t current_time;
    while(running[STG_INGAME])
	{
        
        SDL_RenderCopy(Renderer,BKG_texture,NULL,&bkg_rect);
        light_background(frame, Renderer);
        printmap(Renderer);
        show_help_message(Renderer);
        selected_state(Renderer);

        frame ++;
        if(frame == 8*FPS-1)frame = 0;

        for (int i = 1; i <= atc_num; i++)
        {
            print_soldier(Renderer,attacks[i].start_state,attacks[i].stop_state,attacks[i].soldier_num,i);
        }
        attack_check();
        current_time = time(NULL);

        for (int i = 0; i < explosion_num; i++)
        {
            show_explosion(Renderer,i);
        }
        explosion_check();
        
        if (frame % (rand()%120+1) == 0 && current_time - starting_time > 3)
        {
            AI();
        } 
        
        if (frame % 20 == 0)
        {
            solder_increasing(current_time - starting_time);
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

// -----------------------------------------------------------------------------------------------

SDL_Texture *dynamic_background(SDL_Renderer *Renderer,SDL_Texture *BKG_texture,int range,int num_place)
{
    if (frame % 60 == 0)
    {
        int bkg_num = rand()%range;
        BKG_PATH[num_place] = (char)(bkg_num + '0');
        BKG_texture = loadimg(BKG_PATH , Renderer);
    }
    return BKG_texture;
}

void first_menu_options(SDL_Renderer *Renderer)
{
    SDL_Texture *start_txtr = loadimg("menu/Start.bmp",Renderer);
    SDL_Texture *start_hovered_txtr = loadimg("menu/start_hovered.bmp",Renderer);
    SDL_Rect start_Rect = texture_position(start_txtr,TXR_CENTER,HEIGHT/2,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);

    SDL_Texture *exit_hovered_txtr = loadimg("menu/Exit_hovered.bmp",Renderer);
    SDL_Texture *exit_txtr = loadimg("menu/Exit.bmp",Renderer);
    SDL_Rect exit_Rect = texture_position(exit_txtr,TXR_CENTER,HEIGHT/2 +100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);

    if ((mouse_pos.x >= WIDTH/2-175 && mouse_pos.x <= WIDTH/2+175 && mouse_pos.y >= HEIGHT/2+20 && mouse_pos.y <= HEIGHT/2+60 ) || selected_option == 1)
    {
        SDL_RenderCopy(Renderer,start_hovered_txtr,NULL,&start_Rect);
        if (mouse_is_down || return_is_down)
        {
            running[STG_FIRSTPAGE] = 0;
            stage = STG_USERINPUT;
        }
    }
    
    else if (mouse_pos.x >= WIDTH/2-175 && mouse_pos.x <= WIDTH/2+175 && mouse_pos.y >= HEIGHT/2+120 && mouse_pos.y <= HEIGHT/2+160 || selected_option == 2)
    {
        SDL_RenderCopy(Renderer,exit_hovered_txtr,NULL,&exit_Rect);
        if (mouse_is_down || return_is_down)
        {
            kill_program();
        }
    }

    SDL_RenderCopy(Renderer,start_txtr,NULL,&start_Rect);
    SDL_RenderCopy(Renderer,exit_txtr,NULL,&exit_Rect);
    SDL_DestroyTexture(start_txtr);
    SDL_DestroyTexture(start_hovered_txtr);
    SDL_DestroyTexture(exit_txtr);
    SDL_DestroyTexture(exit_hovered_txtr);
}

_coord center = { .x = 295 , .y = 950};
void sound_control(SDL_Renderer *Renderer)
{
    SDL_Texture *sound_texture = loadimg("images/icon/sound_icon.png",Renderer);
    SDL_Rect sound_rect = texture_position(sound_texture,30,HEIGHT - 70,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,sound_texture,NULL,&sound_rect);
    SDL_DestroyTexture(sound_texture);
    
    boxColor(Renderer,85,44+905,295,46+905,0xccffffff);
    boxColor(Renderer,center.x-10,center.y-10,center.x+10,center.y+10,0xff4040aa);
    static int flag = 0;
    if (mouse_pos.x >= 85 && mouse_pos.x <= 295 && mouse_pos.y >= 940 && mouse_pos.y <= 960)
    {
        if (mouse_is_down)
        {
            flag = 1;
        }
        
    }

    if(flag)
    {
        rectangleColor(Renderer,center.x-10,center.y-10,center.x+10,center.y+10,0xff9090ff);
        if (mouse_pos.x >= 295)
        {
            center.x = 295;
        }
        else if (mouse_pos.x <= 85)
        {
            center.x = 85;
        }
        else
        {
            center.x = mouse_pos.x;
        }            
    }

    if(mouse_is_down == 0)flag = 0;

    double percent = (center.x-85)*128/210;
    Mix_VolumeMusic(percent);
}

void main_first_page(SDL_Renderer *Renderer)
{
    strcpy(BKG_PATH,"images/background/7.jpg");
    Mix_Music *background_music = Mix_LoadMUS("music/back ground.mp3");
    if (background_music == NULL)
    {
        printf("%s\n",SDL_GetError());
    }
    

    SDL_Texture *BKG_texture = loadimg(BKG_PATH , Renderer);
    SDL_Rect BKG_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
    Mix_PlayMusic(background_music,-1);

    while(running[STG_FIRSTPAGE])
	{
        frame++;
        if (frame == 8*FPS-1)frame =0;
        
        BKG_texture = dynamic_background(Renderer,BKG_texture,8,18);
        SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);
        
		handling(Renderer);
        first_menu_options(Renderer);
        sound_control(Renderer);
        mouse_cursor(Renderer);
        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS); 
        SDL_RenderClear(Renderer);
	}
    selected_option = -1;
    SDL_DestroyTexture(BKG_texture);
    BKG_texture = NULL;
}

// ----------------------------------------------------------------------------------------
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

void textinput_show_options(SDL_Renderer *Renderer)
{
    rectangleColor(Renderer,20,650,320,750,0xffffffff);
    rectangleColor(Renderer,380,650,680,750,0xffffffff);
    // rectangleColor(Renderer,200,780,500,880,0xffffffff);
    SDL_Texture *options_texture;
    SDL_Rect options_rect;

    options_texture = loadimg("menu/new game.png",Renderer);
    if ((mouse_pos.x >= 20 && mouse_pos.y >= 650 && mouse_pos.x <= 320 && mouse_pos.y <= 750 )|| selected_option == 0)
    {
        options_texture = loadimg("menu/new game_hovered.png",Renderer);
        if ((mouse_is_down || return_is_down ) )
        {
            if (strlen(user_name) != 0)
            {
                load_previous = 0;
                running[STG_USERINPUT] = 0;
                stage = STG_SELECTMAP;
            }
        }
    }
    options_rect = texture_position(options_texture,20,650,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);    
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);


    options_texture = loadimg("menu/load game.png",Renderer);    
    if ((mouse_pos.x >= 380 && mouse_pos.y >= 650 && mouse_pos.x <= 680 && mouse_pos.y <= 750) ||  selected_option == 1)
    {
        options_texture = loadimg("menu/load game_hovered.png",Renderer);
        if ((mouse_is_down || return_is_down) && is_any_load())
        {
            if (strlen(user_name) != 0)
            {
                load_previous = 1;
                running[STG_USERINPUT] = 0;
                running[STG_INGAME] = 1;
                Mix_PauseMusic();
                stage = STG_INGAME;
            }
        }        
    }
    options_rect = texture_position(options_texture,380,650,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);
    
    SDL_DestroyTexture(options_texture);

}

void main_username(SDL_Renderer *Renderer)
{
	SDL_StartTextInput();
    
    SDL_Texture *BKG_texture = loadimg(BKG_PATH , Renderer);
    SDL_Rect BKG_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);

    
    SDL_Rect userTXT_rect;
    SDL_Texture *userTXT_texture;
    
    SDL_Texture *message_texture = text_texture(Renderer,"please ENTER username :",60,TXT_HEADER,255,255,255,150);
    SDL_Rect messsage_rect = texture_position(message_texture,TXR_CENTER,350,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    
    while(running[STG_USERINPUT])
	{
        frame++;
        if (frame == 8*FPS-1) frame = 0;


        BKG_texture = dynamic_background(Renderer,BKG_texture,8,18);
        
        SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);
        sound_control(Renderer);

        boxColor(Renderer,100,474,600,476,0x332288aa);
        boxColor(Renderer,100,574,600,576,0x332288aa);
        userTXT_texture = text_texture(Renderer,user_name,50,TXT_BODY,255,255,255,255);
        userTXT_rect = texture_position(userTXT_texture,TXR_CENTER,500,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        
        textinput_show_options(Renderer);
		handling(Renderer);

        SDL_RenderCopy(Renderer,message_texture,NULL,&messsage_rect);
        SDL_RenderCopy(Renderer,userTXT_texture,NULL,&userTXT_rect);
        
        mouse_cursor(Renderer);
        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS); 
        SDL_DestroyTexture(userTXT_texture);
        SDL_RenderClear(Renderer);

	}
    SDL_DestroyTexture(message_texture);
    SDL_DestroyTexture(BKG_texture);
    BKG_texture = NULL;
    SDL_StopTextInput();
}

// ---------------------------------------------------------------------------------------- 

void selectmap_show_options(SDL_Renderer *Renderer)
{
    rectangleColor(Renderer,200,300-100,500,400-100,0xffffffff);
    rectangleColor(Renderer,20,450-100,320,550-100,0xffffffff);
    rectangleColor(Renderer,380,450-100,680,550-100,0xffffffff);
    rectangleColor(Renderer,20,600-100,320,700-100,0xffffffff);
    rectangleColor(Renderer,380,600-100,680,700-100,0xffffffff);
    rectangleColor(Renderer,0,750,WIDTH,850,0xffffffff);
    SDL_Texture *options_texture;
    SDL_Rect options_rect;
    
    options_texture = text_texture(Renderer,"map 1",80,TXT_HANDWRITE,255,255,255,255);
    options_rect = texture_position(options_texture,20+50,450-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

    options_texture = text_texture(Renderer,"map 2",80,TXT_HANDWRITE,255,255,255,255);
    options_rect = texture_position(options_texture,380+50,450-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

    options_texture = text_texture(Renderer,"map 3",80,TXT_HANDWRITE,255,255,255,255);
    options_rect = texture_position(options_texture,20+50,600-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

    options_texture = text_texture(Renderer,"map 4",80,TXT_HANDWRITE,255,255,255,255);
    options_rect = texture_position(options_texture,380+50,600-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);

    options_texture = loadimg("menu/new map.png",Renderer);
    if ((mouse_pos.x >= 200 && mouse_pos.y >= 300-100 && mouse_pos.x <= 500 && mouse_pos.y <= 400-100) || map_num == -1)
    {
        options_texture = loadimg("menu/new map_hovered.png",Renderer);
        if (mouse_is_down || return_is_down)
        {
            load_previous = 0;
            running[STG_SELECTMAP] = 0;
            running[STG_INGAME] = 1;
            Mix_PauseMusic();
            stage = STG_INGAME;
        }
        
    }
    options_rect = texture_position(options_texture,200,300-100,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);    
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);
    
    options_texture = loadimg("menu/select map.png",Renderer);
    if (return_is_down && map_num != -1)
    {
        options_texture = loadimg("menu/select map_hovered.png",Renderer);
    }

    if ((mouse_pos.x >= 380 && mouse_pos.y >= 450-100 && mouse_pos.x <= 680 && mouse_pos.y <= 550-100) || map_num == 1)
    {
        rectangleColor(Renderer,380,450-100,680,550-100,0xffff11ff);
        if (mouse_is_down || return_is_down)
        {
            load_previous = 1;
            load_game("saves/saved_map 1");
            Mix_PauseMusic();
            running[STG_SELECTMAP] = 0;
            running[STG_INGAME] = 1;

            stage = STG_INGAME;
        }
        
    }
    else if ((mouse_pos.x >= 20 && mouse_pos.y >= 450-100 && mouse_pos.x <= 350 && mouse_pos.y <= 550-100) || map_num == 0)
    {
        rectangleColor(Renderer,20,450-100,320,550-100,0xffff11ff);
        if (mouse_is_down || return_is_down)
        {
            load_previous = 1;
            load_game("saves/saved_map 4");
            running[STG_SELECTMAP] = 0;
            stage = STG_INGAME;
            Mix_PauseMusic();

        }
    }
    else if ((mouse_pos.x >= 380 && mouse_pos.y >= 600-100 && mouse_pos.x <= 680 && mouse_pos.y <= 700-100) || map_num == 3)
    {
        rectangleColor(Renderer,380,600-100,680,700-100,0xffff11ff);
        if (mouse_is_down || return_is_down)
        {
            load_previous = 1;
            load_game("saves/saved_map 3");
            running[STG_SELECTMAP] = 0;
            stage = STG_INGAME;
            Mix_PauseMusic();

        }
    }
    else if ((mouse_pos.x >= 20 && mouse_pos.y >= 600-100 && mouse_pos.x <= 350 && mouse_pos.y <= 700-100) || map_num == 2)
    {
        rectangleColor(Renderer,20,600-100,320,700-100,0xffff11ff);
        if (mouse_is_down || return_is_down)
        {
            load_previous = 1;
            load_game("saves/saved_map 2");
            running[STG_SELECTMAP] = 0;
            stage = STG_INGAME;
            Mix_PauseMusic();

        }
    }
    options_rect = texture_position(options_texture,200,750,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    SDL_RenderCopy(Renderer,options_texture,NULL,&options_rect);
    
    SDL_DestroyTexture(options_texture);

}

int main_selectmap(SDL_Renderer *Renderer)
{
    SDL_Texture *BKG_texture = loadimg(BKG_PATH , Renderer);
    SDL_Rect BKG_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
    while(running[STG_SELECTMAP])
	{
        frame++;
        if (frame == 8*FPS-1) frame = 0;

        BKG_texture = dynamic_background(Renderer,BKG_texture,8,18);
        
        SDL_RenderCopy(Renderer,BKG_texture,NULL,&BKG_rect);
        sound_control(Renderer);

        
        selectmap_show_options(Renderer);
		handling(Renderer);
        
        mouse_cursor(Renderer);

        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS); 
        SDL_RenderClear(Renderer);

	}
    SDL_DestroyTexture(BKG_texture);
    BKG_texture = NULL;
}

// ----------------------------------------------------------------------------

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

void read_leaderboard()
{
    FILE *leaderboard = fopen("saves/leader-board","r");
    int head = 0;
    while (!feof(leaderboard))
    {
        fscanf(leaderboard,"%s : %d\n",score[head].user_name,&score[head].score);
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
        if (head >= 1000)
        {
            head = 0;
        }
        
    }
    fclose(leaderboard);
}

void show_leaderboard(SDL_Renderer *Renderer)
{
    SDL_Texture *score_texture;
    SDL_Rect score_rect;
    char buffer[40];
    char temp[30];

    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }
    
    score_texture = text_texture(Renderer,"top 8 players in last 1000 games: ",45,TXT_HEADER,255,255,100,255);
    score_rect = texture_position(score_texture,TXR_CENTER,180,TXR_DEFAULT_SIZE,TXR_CENTER);
    SDL_RenderCopy(Renderer,score_texture,NULL,&score_rect);

    for (int i = 0; i < (file_lines("saves/leader-board") <= 8 ? file_lines("saves/leader-board") : 8); i++)
    {
        sprintf(temp," : %d",score[i].score);
        strcat(buffer,score[i].user_name);
        strcat(buffer,temp);
        score_texture = text_texture(Renderer,buffer,60,TXT_HANDWRITE,255,255,100,255);
        score_rect = texture_position(score_texture,TXR_CENTER,250+70*i,TXR_DEFAULT_SIZE,TXR_CENTER);
        SDL_RenderCopy(Renderer,score_texture,NULL,&score_rect);
        for (int j = 0; j < 40; j++)
        {
            buffer[j] = '\0';
        }
    }
    SDL_DestroyTexture(score_texture);
}

void show_leaderboard_options(SDL_Renderer *Renderer)
{
    rectangleColor(Renderer,WIDTH-340,830,WIDTH -40,930,0xffffffff);
    SDL_Texture *back_texture = loadimg("menu/back.png",Renderer);
    SDL_Rect back_rect = texture_position(back_texture,WIDTH-340,830,300,100);

    if (mouse_pos.x >= WIDTH-340 && mouse_pos.y >= 830 && mouse_pos.x <= WIDTH -40 && mouse_pos.y <= 930)
    {
        back_texture = loadimg("menu/back_hovered.png",Renderer);
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
    SDL_Texture *BKG_texture = loadimg(BKG_PATH , Renderer);
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

int main() 
{
    srand(time(NULL)*1000);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	SDL_Window *window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
    HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_ShowCursor(0);
    while(running[STG_WHOLEGAME])
    {
        if (stage == STG_FIRSTPAGE)
        {
            main_first_page(Renderer);
        }
        else if (stage == STG_USERINPUT)
        {
            main_username(Renderer);
        }
        else if(stage == STG_SELECTMAP)
        {
            main_selectmap(Renderer);
        }
        else if (stage == STG_INGAME)
        {
            main_map(Renderer);
        }
        else if (stage == STG_LEADERBOARD)
        {
            leaderboeard_main(Renderer);
        }
        SDL_RenderClear(Renderer);
    }
    // SDL_DestroyTexture(Texture);
    SDL_DestroyTexture(mouse_texture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Renderer);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}