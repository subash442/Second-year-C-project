#ifndef DESIGN_H_INCLUDED
#define DESIGN_H_INCLUDED
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <string>

SDL_Surface *load_image(std::string filename,char ch='n');
void applySurface (int x,int y,SDL_Surface *source,SDL_Surface *destination,SDL_Rect *clipp = NULL );
void set_clip(int x1,int y1,int w,int h,int x2,int y2,int x3=0,int y3=0);
bool load_file_mainpage();
bool sdl_init();
void clean_up();
class Buttons;
void load_page_secondpage(char ch);
void display_screen_mainpage(Buttons& bu1, Buttons& bu2);
void display_page_secondpage(Buttons &b1,Buttons &b2,Buttons &b3,char ch);
bool main_page(Buttons& bu1,Buttons& bu2);
void level_completed();
void digital_loadfile();


const int width = 1300;
const int height = 700;
const int bpp = 32;


SDL_Surface *resetBMP = NULL;
SDL_Surface *setBMP = NULL;
SDL_Surface *levelImage = NULL;
SDL_Surface *levelno = NULL;
SDL_Surface *buttonImage1 = NULL;
SDL_Surface *buttonImage2 = NULL;
SDL_Surface *icon = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *home = NULL;


TTF_Font *font = NULL;

Mix_Chunk *complete = NULL;
Mix_Music *music = NULL;
Mix_Chunk *click = NULL;

SDL_Color textcolor = {255,20,20};

Uint32 screenColor;
bool running = true;

SDL_Event event;
SDL_Rect clips[3];

bool quit = false;
int level_delay=2000;
class Buttons
{
private:
    SDL_Rect but;
    bool clicks;
public:
    SDL_Surface *temp;
    Buttons(int x,int y,int w,int h)
    {
        but.x=x;
        but.y=y;
        but.w=w;
        but.h=h;

        temp = buttonImage1;
        clicks = false;
    }
    bool get_clicks()
    {
        return clicks;
    }

    void click_check()
    {
        int x=0 , y=0;
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
             if( event.button.button == SDL_BUTTON_LEFT )
                {
                    x=event.button.x;
                    y=event.button.y;
                    if( ( x > but.x ) && ( x < but.x + but.w ) && ( y > but.y ) && ( y < but.y + but.h ) )
                    {
                        Mix_PlayChannel( -1, click, 0 );
                       temp = buttonImage2;
                       clicks=true;
                       quit = true;

                    }

                }
        }
    }

    ~Buttons()
    {
        SDL_FreeSurface(temp);
    }
};

//Buttons bu1(516,353,352,109);
//Buttons bu2(520,572,352,109);



SDL_Surface *load_image(std::string filename,char ch)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;

     loadedImage = IMG_Load(filename.c_str());
     if (loadedImage != NULL)
     {
         optimizedImage = SDL_DisplayFormat(loadedImage);
         SDL_FreeSurface(loadedImage);
         if (optimizedImage != NULL && ch =='y')
         {
             Uint32 colorkey = SDL_MapRGB(optimizedImage->format,0XFF,0XFF,0XFF);
             SDL_SetColorKey(optimizedImage,SDL_SRCCOLORKEY,colorkey);
         }
     }
     return optimizedImage;
}

void applySurface (int x,int y,SDL_Surface *source,SDL_Surface *destination,SDL_Rect *clipp )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source,clipp,destination,&offset);
}

void set_clip(int x1,int y1,int w,int h,int x2,int y2,int x3,int y3)
{
    clips[0].x=x1;
    clips[0].y=y1;
    clips[0].w=w;
    clips[0].h=h;

    clips[1].x=x2;
    clips[1].y=y2;
    clips[1].w=w;
    clips[1].h=h;
    if (!(x3==0 && y3==0))
    {
        clips[2].x=x3;
        clips[2].y=y3;
        clips[2].w=w;
        clips[2].h=h;
    }
}


bool sdl_init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)==-1) return false;
    screen = SDL_SetVideoMode(width,height,bpp,SDL_SWSURFACE);
    if (screen == NULL) return false;

    SDL_WM_SetCaption("Electronics world","icon1.bmp");
    if (TTF_Init()==-1) return false;
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )return false;

    return true;
}

void clean_up()
{

    SDL_FreeSurface( background );
    SDL_FreeSurface(buttonImage1);
    SDL_FreeSurface(buttonImage2);
    SDL_FreeSurface( message );
    SDL_FreeSurface( icon );
    SDL_FreeSurface(setBMP);
    SDL_FreeSurface(resetBMP);
    SDL_FreeSurface(message);
    SDL_FreeSurface(levelImage);
    SDL_FreeSurface(levelno);
     Mix_FreeChunk(complete);

    Mix_FreeMusic(music);
    Mix_FreeChunk(click);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_Quit();

}


bool load_file_mainpage()
{

    background = load_image("background1.bmp");
    font = TTF_OpenFont("digifaw.ttf",80);
    music = Mix_LoadMUS("beat.wav");
    click = Mix_LoadWAV("beat1.wav");
    buttonImage1 = load_image("button11.bmp",'y');
    buttonImage2 = load_image("button21.bmp",'y');
    icon = load_image("icon1.bmp");
    SDL_WM_SetIcon(icon,NULL);
    if ( background == NULL||font== NULL||music==NULL) return false;
    return true;
}

void display_screen_mainpage(Buttons& bu1, Buttons& bu2)
{

    applySurface( 0, 0, background, screen );
     applySurface(450,300,bu1.temp,screen,&clips[0]);
     applySurface(450,535,bu2.temp,screen,&clips[1]);
     message = TTF_RenderText_Solid(font,"Welcome to electronics",textcolor);
     applySurface(30,0,message,screen);
      message = TTF_RenderText_Solid(font,"World!",textcolor);
     applySurface(450,90,message,screen);
SDL_Flip(screen) ;


}

bool main_page(Buttons& bu1,Buttons& bu2)
{
     quit =false;
      set_clip(0,0,480,235,0,235);
     if (load_file_mainpage()==false) return false;
     if( Mix_PlayMusic( music, -1 ) == -1 ) return false;
      bu1.temp = buttonImage1;
bu2.temp = buttonImage1;
        display_screen_mainpage(bu1,bu2);
    if (SDL_Flip(screen) == -1) return false;
    while (quit==false)
    {
        while(SDL_PollEvent(&event))
        {
                if (event.type == SDL_QUIT) SDL_Quit();
                if (!(bu1.get_clicks()||bu2.get_clicks()))
                {
                    bu1.click_check();
                    bu2.click_check();
                }
        }
    }
    display_screen_mainpage(bu1,bu2);
    SDL_Delay(200);
    return true;
}


void load_page_secondpage(char ch)
{
    switch(ch)
    {
        case 'a':
            background = load_image("analog1.bmp");
            music = Mix_LoadMUS("beat.wav");
            break;
        case 'd':
            background = load_image("digital1.bmp");
            music = Mix_LoadMUS("beat.wav");
            break;
    }
//     click = Mix_LoadWAV("beat1.wav");
  //  font = TTF_OpenFont("digifaw.ttf",80);
    buttonImage1 = load_image("page-11.bmp",'y');
    buttonImage2 = load_image("page-21.bmp",'y');

}





void display_page_secondpage(Buttons &b1,Buttons &b2,Buttons &b3,char ch)
{
        applySurface( 0, 0, background, screen );
     applySurface(450,150,b1.temp,screen,&clips[0]);
     applySurface(450,310,b2.temp,screen,&clips[1]);
     applySurface(450,470,b3.temp,screen,&clips[2]);
     switch(ch)
     {
    case 'a':
         message = TTF_RenderText_Solid(font,"Analog World!",textcolor);
         break;
    case 'd':
         message = TTF_RenderText_Solid(font,"Digital World!",textcolor);
         break;
     }
     applySurface(350,0,message,screen);
            SDL_Flip(screen);

}


void second_page(Buttons& b1,Buttons& b2,Buttons&b3 ,char ch)
{
     quit = false;
     set_clip(0,0,510,160,0,160,0,310);
        load_page_secondpage(ch);

    //Mix_PlayMusic( music, -1 );
    b1.temp = buttonImage1;
            b2.temp = buttonImage1;
            b3.temp = buttonImage1;
    display_page_secondpage(b1,b2,b3,ch);
    SDL_Flip(screen);
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) SDL_Quit();
            if (!(b1.get_clicks()||b2.get_clicks()||b3.get_clicks()))
              {
                    b1.click_check();
                    b2.click_check();
                    b3.click_check();
              }
        }
    }
         display_page_secondpage(b1,b2,b3,ch);
            SDL_Delay(200);


}

void level_completed()
{
     applySurface(500,600,message,screen);
                Mix_PlayChannel( -1, complete, 0 );
}

void digital_loadfile()
{
complete = Mix_LoadWAV("complete.WAV");
message = load_image("complete1.bmp",'y');
setBMP = load_image("set1.bmp",'y');
resetBMP=load_image("reset1.bmp",'y');
levelImage = load_image("gates1.bmp",'y');
home=load_image("home.bmp");
screenColor = SDL_MapRGB(screen->format, 25, 90, 25);
SDL_FillRect(screen, NULL, screenColor);
}

void digital_loadfile1()
{
complete = Mix_LoadWAV("complete.WAV");
message = load_image("complete1.bmp",'y');
setBMP = load_image("set1.bmp",'y');
resetBMP=load_image("reset1.bmp",'y');
levelImage = load_image("gate2.bmp",'y');
home=load_image("home.bmp");
screenColor = SDL_MapRGB(screen->format, 25, 90, 25);
SDL_FillRect(screen, NULL, screenColor);
}

void digital_loadfile2()
{
complete = Mix_LoadWAV("complete.WAV");
message = load_image("complete1.bmp",'y');
setBMP = load_image("set1.bmp",'y');
resetBMP=load_image("reset1.bmp",'y');
levelImage = load_image("gate3.bmp",'y');
home=load_image("home.bmp");
screenColor = SDL_MapRGB(screen->format, 25, 90, 25);
SDL_FillRect(screen, NULL, screenColor);
}

void analog_loadfile()
{
complete = Mix_LoadWAV("complete.WAV");
message = load_image("complete1.bmp",'y');
setBMP = load_image("set1.bmp",'y');
resetBMP=load_image("reset1.bmp",'y');
levelImage = load_image("2.bmp",'y');
home=load_image("home.bmp");
screenColor = SDL_MapRGB(screen->format, 25, 90, 25);
SDL_FillRect(screen, NULL, screenColor);
}

void analog_loadfile1()
{
complete = Mix_LoadWAV("complete.WAV");
message = load_image("complete1.bmp",'y');
setBMP = load_image("set1.bmp",'y');
resetBMP=load_image("reset1.bmp",'y');
levelImage = load_image("resistor.bmp",'y');
home=load_image("home.bmp");
screenColor = SDL_MapRGB(screen->format, 25, 90, 25);
SDL_FillRect(screen, NULL, screenColor);
}

/*void analog_loadfile2()
{
complete = Mix_LoadWAV("complete.WAV");
message = load_image("complete1.bmp",'y');
setBMP = load_image("set1.bmp",'y');
resetBMP=load_image("reset1.bmp",'y');
levelImage = load_image("resistor.bmp",'y');
home=load_image(".bmp");
screenColor = SDL_MapRGB(screen->format, 25, 90, 25);
SDL_FillRect(screen, NULL, screenColor);
}*/

#endif // DESIGN_H_INCLUDED

