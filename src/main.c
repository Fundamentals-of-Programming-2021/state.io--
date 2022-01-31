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

#define FPS 60
#define TXT_HEADER 0
#define TXT_HANDWRITE 1
#define TXT_BODY 2
#define TXR_CENTER -1
#define TXR_DEFAULT_SIZE -1
typedef struct
{
    Sint16 x;
    Sint16 y;

}_coord;


char BKG_PATH[100] = {"images/background/game 1_1.bmp"};
const int WIDTH = 1800;
const int HEIGHT = 900;
int frame = 0;
_coord STATECOUNT = {.x = 17 , .y = 7};
_coord mouse_pos,F_mouse_state,S_mouse_state;
bool mouse_is_down = 0;
int atc_num = 0;
int country_count = 0;


typedef struct 
{
    Uint32 color;
    _coord initstate;

}_player;

typedef struct
{
    _coord start_state;
    _coord stop_state;
    int soldier_num;

}_attack_info;

typedef struct
{
    int num;
    Uint32 color;
    int passed_unit;
    _coord capital;
    bool is_under_attack;
}_country;

_country country[100];
typedef struct
{
    Sint16 points[2][7];
    _coord center;
    int country_num;
    bool is_capital;
    bool avalable;
    int unitcount;
    short int player;

}_state;

_state state[100][100];
typedef struct
{
    _coord center;
    int radius;
    bool reached;
    bool damage;

}SDL_circ;

SDL_circ soldier[100][1000];

int sign(int num)
{
    return (num > 0 ? 1 : -1);
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
    SDL_Surface *imgsurface = SDL_LoadBMP(file_location);
    if (imgsurface == NULL)
    {
        printf("can not open image: %s \n",file_location);
        return NULL;
    }
    
    SDL_Texture *Texture = SDL_CreateTextureFromSurface(Renderer,imgsurface);
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

//0 =: for number , 1 =: for text , 2=: for combine
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

int power(int power,int base)
{
    int res = 1;
    for (int i = 0; i < power; i++)
    {
        res *= base;
    }
    return res;
    
}

void armory_place(SDL_Renderer* renderer,_coord coord, Uint32 color,int player,int size,int soldier_num)
{
    Sint8 C_radius = size;
    Sint8 sq_len = size;
    Sint8 trig_len = size*1.25;
    switch (player)
    {
        case (0):
            filledTrigonColor(renderer,coord.x,coord.y-trig_len,coord.x + trig_len * 0.85, coord.y+trig_len/2,coord.x -trig_len*0.85,coord.y+trig_len/2,color);
            break;
        case (1):
            boxColor(renderer,coord.x-sq_len,coord.y-sq_len,coord.x+sq_len,coord.y+sq_len,color);
            break;
        default:
            filledCircleColor(renderer,coord.x,coord.y,C_radius,color);
            break;
    }
    print_text(renderer,0,soldier_num," ",coord.x-3,coord.y+30);
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

//makes all of a hex shape points
void sethex(Sint16 point[][7],_coord center,int diameter,_coord *state_cent)
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
                temp.x = i; temp.y=j;
                return temp;
            }
        }   
    }
    return temp;
}

void printmap(SDL_Renderer *Renderer,_player player[])
{
    print_text(Renderer,1,0,"you are squere",WIDTH/2-50,10);
    Sint16 big_polyg[2][7];

    for (int i = 0; i < STATECOUNT.x; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x03ffff05);
            polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,0x09ffff00);

            if (state[i][j].country_num != -1 && state[i][j].avalable)
            {
                filledPolygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,country[state[i][j].country_num].color);
                polygonColor(Renderer,state[i][j].points[0],state[i][j].points[1],6,country[state[i][j].country_num].color);
                if (state[i][j].is_capital)
                {
                    armory_place(Renderer,state[i][j].center,0xffffffff,1,18,state[i][j].unitcount);
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

void setmap(SDL_Renderer *Renderer,_player player[])
{    
    //sin 22.5 = 0.03827 / cos 22.5 = 0.9239
    //sin 60 = 0.85 / cos60 = 0.5 
    int diameter = 124;
    _coord step;

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
            step.y -= 35;
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
}

void SetColors(_player player[],int playernum)
{
    player[0].color = 0x55005500;
    player[1].color = 0x55000055;
    player[2].color = 0x5500bb00;
    player[3].color = 0x550000bb;

    for (int i = 0; i < STATECOUNT.x; i++)
    {
        for (int j = 0; j < STATECOUNT.y; j++)
        {
            country[state[i][j].country_num].color = 0x998888ff+ state[i][j].country_num * 0x0011aacc;
        }
    }
}

_attack_info attacks[150];
void handling(SDL_Renderer *renderer)
{
	SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) exit(0);
        if (event.type == SDL_KEYDOWN)
        {
            const Uint8* keys = SDL_GetKeyboardState(NULL);
        }
        if( event.type == SDL_MOUSEMOTION)
        {
            mouse_pos.x = event.button.x;
            mouse_pos.y = event.button.y;
            S_mouse_state.x = mouse_check(renderer).x;
            S_mouse_state.y = mouse_check(renderer).y;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_is_down = 1;
                F_mouse_state = S_mouse_state;
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_is_down = 0;
                atc_num ++;
                attacks[atc_num].start_state = F_mouse_state;
                attacks[atc_num].stop_state = S_mouse_state;
                attacks[atc_num].soldier_num = state[F_mouse_state.x][F_mouse_state.y].unitcount;
                state[F_mouse_state.x][F_mouse_state.y].unitcount = 0;
                country[state[S_mouse_state.x][S_mouse_state.y].country_num].is_under_attack =1;
            }
        }
	}
}

int colission_detect(_coord obj,_coord dest,int diameter)
{
    if ((pow(obj.x-dest.x,2) + pow(obj.y-dest.y,2))<= pow(diameter,2))
    {
        return 1;
    }
    return 0;
}

//sets map and intializes the map
void initializer(SDL_Renderer *Renderer,_player player[])
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
            state[i][j].player = -1;
            state[i][j].country_num = -1;
            state[i][j].is_capital = 0;
            state[i][j].unitcount = 0;
        }
    }

    for (int i = 0; i < country_count; i++)
    {
        country[i].is_under_attack = 0;
        country[i].color = 0xffffffff;
        country[i].passed_unit = 0;
    }
}

void solder_increasing(time_t time)
{
    int speed = 1;
    
    if (time % speed == 0)
    {
        for (int i = 0; i < STATECOUNT.x; i++)
        {
            for (int j = 0; j < STATECOUNT.y; j++)
            {
                if (state[i][j].unitcount < 75 && !country[state[i][j].country_num].is_under_attack)
                {
                    state[i][j].unitcount+= 3;
                }                
            }
        }
    }
}

void selected_state(SDL_Renderer *Renderer)
{
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

void print_dynamic_line(SDL_Renderer *Renderer)
{
    if (mouse_is_down && state[F_mouse_state.x][F_mouse_state.y].avalable && state[S_mouse_state.x][S_mouse_state.y].avalable)
    {
        lineRGBA(Renderer,state[F_mouse_state.x][F_mouse_state.y].center.x,state[F_mouse_state.x][F_mouse_state.y].center.y,mouse_pos.x,mouse_pos.y,0,160,200,255);
    }
}

void set_soldier(int cntry_num)
{
    for (int i = 0; i < 100; i++)
    {
        soldier[cntry_num][i].damage = 1;
        soldier[cntry_num][i].center = state[country[cntry_num].capital.x][country[cntry_num].capital.y].center;
        soldier[cntry_num][i].reached = 0;
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

void print_soldier(SDL_Renderer *Renderer,_coord F_state , _coord S_state  ,int number)
{
    double difference_x = state[S_state.x][S_state.y].center.x - state[F_state.x][F_state.y].center.x;
    double difference_y = state[S_state.x][S_state.y].center.y - state[F_state.x][F_state.y].center.y;
    double SIN,COS;

    if (difference_x == 0)
    {
        if (difference_y > 0)
        {
            SIN = 1;
        }
        else
        {
            SIN = -1;
        }        
        COS = 0;
    }
    else if (difference_y == 0)
    {
        if (difference_x > 0)
        {
            COS = 1;
        }
        else
        {
            COS = -1;
        }        
        SIN = 0;
    }
    else
    {
        SIN = difference_y/sqrt(pow(difference_x,2)+pow(difference_y,2));
        COS = difference_x/sqrt(pow(difference_x,2)+pow(difference_y,2));
    }
    
    //just for less typing 
    _state temp = state[F_state.x][F_state.y];

    int flag = 1;
    for (int i = 0; i < country[state[F_state.x][F_state.y].country_num].passed_unit ; i++)
    {
        if (!colission_detect(soldier[state[F_state.x][F_state.y].country_num][i].center,state[S_state.x][S_state.y].center,50))
        {
            soldier[state[F_state.x][F_state.y].country_num][i].center.y += 10 * SIN;
            soldier[state[F_state.x][F_state.y].country_num][i].center.x += 10 * COS;
        }
        else
        {
            soldier[state[F_state.x][F_state.y].country_num][i].reached = 1;
        }
        if (!soldier[state[F_state.x][F_state.y].country_num][i].reached)
        {
            filledCircleColor(Renderer,soldier[state[F_state.x][F_state.y].country_num][i].center.x,soldier[state[F_state.x][F_state.y].country_num][i].center.y,10,0xffffffff);
        }
        else if(soldier[state[F_state.x][F_state.y].country_num][i].reached && soldier[state[F_state.x][F_state.y].country_num][i].damage)
        {
            state[S_state.x][S_state.y].unitcount--;
            soldier[state[F_state.x][F_state.y].country_num][i].damage = 0;
        }        
    }

    if (country[state[F_state.x][F_state.y].country_num].passed_unit != number && frame % 3 == 0)
    {
        country[state[F_state.x][F_state.y].country_num].passed_unit++;
    }
    if (reach_check(state[F_state.x][F_state.y].country_num,number))
    {
        country[state[F_state.x][F_state.y].country_num].passed_unit = 0;
        set_soldier(state[F_state.x][F_state.y].country_num);
        country[state[S_state.x][S_state.y].country_num].is_under_attack = 0;
        atc_num--;
    }
    
    
}


int main() {

    srand(time(NULL)*1000);
    int player_count = 4;
    _player player[player_count+1];

    SDL_Init(SDL_INIT_VIDEO);


	SDL_Window *window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
    HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    
    initializer(Renderer,player);
    setmap(Renderer,player);
    SetColors(player,player_count);

    for (int i = 0; i < country_count; i++)
    {
        set_soldier(i);
    }

    SDL_Texture *BKG_texture = loadimg(BKG_PATH,Renderer);
    SDL_Rect bkg_rect = texture_position(BKG_texture,TXR_CENTER,TXR_CENTER,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);
        
	time_t starting_time = time(NULL);
    
    while(1)
	{
        
        SDL_RenderCopy(Renderer,BKG_texture,NULL,&bkg_rect);
        printmap(Renderer,player);

        frame ++;
        if(frame == 2*FPS-1)frame = 0;

        if (atc_num)
        {
            for (int i = 1; i <= atc_num; i++)
            {
                print_soldier(Renderer,attacks[i].start_state,attacks[i].stop_state,attacks[i].soldier_num);
            }
        }
        
        time_t current_time = time(NULL);

        print_text(Renderer,2,(int)(current_time - starting_time),"time passd:",10,10);
        
        if (frame % 20 == 0)
        {
            solder_increasing(current_time - starting_time);
        }
        
        print_dynamic_line(Renderer);
        selected_state(Renderer);

		handling(Renderer);
       
        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS);
        SDL_RenderClear(Renderer);
	}
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
    return 0;
}