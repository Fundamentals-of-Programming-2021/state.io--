// #include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#define FPS 60
#define TXT_HEADER 0
#define TXT_HANDWRITE 1
#define TXT_BODY 2
#define TXR_CENTER -1
#define TXR_DEFAULT_SIZE -1

bool running = 1;
bool mouse_is_down = 0;
bool return_is_down = 0;
char BKG_PATH[100] = {"images/background/score board/1.jpg"};
const int WIDTH = 700;
const int HEIGHT = 1000;
char user_name[25];
int frame = 0;
int map_num = -1;
typedef struct
{
    Sint16 x;
    Sint16 y;

}_coord;

typedef struct
{
    int score;
    char user_name[25];
}_score;

_score score[1000]; 

_coord mouse_pos = {0,0};

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
    TTF_CloseFont(font);
    SDL_FreeSurface(txtsurface);
    return txtTexture;    
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

void handling(void)
{
	SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = 0;

        if( event.type == SDL_MOUSEMOTION)
        {
            mouse_pos.x = event.button.x;
            mouse_pos.y = event.button.y;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_is_down = 1;
                printf("pressed on (%d,%d)\n", event.button.x, event.button.y);
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_is_down = 0;
                printf("finished on (%d,%d)\n", event.button.x, event.button.y);
            }
        }
        if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN)
        {
            if(event.type == SDL_TEXTINPUT)
            {
                if(strlen(user_name) < 20)
                {
                    user_name[strlen(user_name)] = *(event.text.text);
                    user_name[strlen(user_name)] = '\0';
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(user_name) > 0)
                {
                    user_name[strlen(user_name)-1] = '\0';
                }
                else if (event.key.keysym.sym == SDLK_RETURN && strlen(user_name) > 0)
                {
                    return_is_down = 1;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    map_num ++;
                    if (map_num > 3)
                    {
                        map_num = -1;
                    }
                }
                else if (event.key.keysym.sym == SDLK_LEFT)
                {
                    map_num --;
                    if (map_num < -1)
                    {
                        map_num = 3;
                    }
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    map_num -= 2;
                    if (map_num < -1)
                    {
                        map_num = -1;
                    }
                }
                else if (event.key.keysym.sym == SDLK_DOWN)
                {
                    map_num += 2;
                    if (map_num > 3)
                    {
                        map_num = -1;
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
        
	}
}

SDL_Texture *loadimg(char* file_location,SDL_Renderer *Renderer)
{
    SDL_Surface *imgsurface = IMG_Load(file_location);
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

SDL_Texture *dynamic_background(SDL_Renderer *Renderer,SDL_Texture *BKG_texture)
{
    if (frame % 60 == 0)
    {
        int bkg_num = rand()%4;
        BKG_PATH[30] = (char)(bkg_num + '0');
        BKG_texture = loadimg(BKG_PATH , Renderer);
    }
    return BKG_texture;
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

void read_leaderboard()
{
    FILE *leaderboard = fopen("saves/leader-board","r");
    int head = 0;
    int l = file_lines("saves/leader-board");
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
    }
    fclose(leaderboard);
}

void show_leaderboard(SDL_Renderer *Renderer)
{
    SDL_Texture *score_texture;
    SDL_Rect score_rect;
    char buffer[50];
    char temp[50];

    for (int i = 0; i < 50; i++)
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
        for (int j = 0; j < 50; j++)
        {
            buffer[j] = '\0';
        }
    }
    SDL_DestroyTexture(score_texture);
}

void show_options(SDL_Renderer *Renderer)
{
    rectangleColor(Renderer,WIDTH-340,830,WIDTH -40,930,0xffffffff);
    SDL_Texture *back_texture = loadimg("menu/back.png",Renderer);
    SDL_Rect back_rect = texture_position(back_texture,WIDTH-340,830,300,100);

    if (mouse_pos.x >= WIDTH-340 && mouse_pos.y >= 830 && mouse_pos.x <= WIDTH -40 && mouse_pos.y <= 930)
    {
        back_texture = loadimg("menu/back_hovered.png",Renderer);
    }
    
    SDL_RenderCopy(Renderer,back_texture,NULL,&back_rect);
    SDL_DestroyTexture(back_texture);
}

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *Renderer = NULL;
    srand(time(NULL)*1000);
    
    SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,
    HEIGHT, SDL_WINDOW_OPENGL);

    Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    TTF_Init();
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_StartTextInput();
    SDL_SetRenderDrawColor(Renderer,0,0,0,0);
    
    SDL_Texture *BKG_texture = loadimg(BKG_PATH , Renderer);
    SDL_Texture *mouse_texture = loadimg("images/cursor/cursor 2.png",Renderer);
    SDL_Rect mouse_rect;

    SDL_ShowCursor(0);
    read_leaderboard();
        
    while(running)
	{
        frame++;
        if (frame == 2*FPS-1) frame = 0;
        mouse_rect = texture_position(mouse_texture,mouse_pos.x,mouse_pos.y,TXR_DEFAULT_SIZE,TXR_DEFAULT_SIZE);



        BKG_texture = dynamic_background(Renderer,BKG_texture);
        
        SDL_RenderCopy(Renderer,BKG_texture,NULL,NULL);
        sound_control(Renderer);

        
        show_leaderboard(Renderer);
        show_options(Renderer);
		handling();
        SDL_RenderCopy(Renderer,mouse_texture,NULL,&mouse_rect);
        
        SDL_RenderPresent(Renderer);
		SDL_Delay(1000/FPS); 
        SDL_RenderClear(Renderer);

	}

    IMG_Quit();
    SDL_DestroyTexture(BKG_texture);
    BKG_texture = NULL;
    SDL_StopTextInput();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Renderer);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
