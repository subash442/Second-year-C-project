#ifndef DIGITAL_H_INCLUDED
#define DIGITAL_H_INCLUDED

#include <SDL/SDL.h>
#include "Design.h"
int load_digital1();
int level1_digital();
int load_digital2();
int level2_digital();
int load_digital3();
int level3_digital();

class variable
{
    protected:
SDL_Rect box;
    bool bit;

public:
variable(){}
variable(int a):bit(a){}
variable( int x, int y)
{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = 65;
    box.h = 65;
    bit=0;
    //SDL_BlitSurface(resetBMP, NULL, screen, &box);
    flipscreen();
 //       SDL_Flip(screen);
}
    variable operator& (variable b)
    {
        return variable(bit&b.bit);
    }

     variable operator| (variable b)
    {
        return variable(bit|b.bit);
    }

    variable operator~ ()
    {
        return variable(!bit);
    }

   variable operator^ (variable b)
    {
        return variable(bit^b.bit);
    }

    int get_bit()
    {
        return bit;
    }

    void flipscreen()
    {

    if (bit)
               {

                SDL_BlitSurface(setBMP, NULL, screen, &box);
                 SDL_Flip(screen);
               }
               else
               {
                    SDL_BlitSurface(resetBMP, NULL, screen, &box);

                 SDL_Flip(screen);
               }
    }



    void setposition(int x,int y)
    {
    box.x = x;
    box.y = y;
    }

};




class output:public variable
{
public:
    output(){}
    output (int a,int b):variable(a ,b){}

    output(variable a )
    {

        bit=a.get_bit();
        if(bit)
            {
               level_completed();
            }
    }


};

      // output o (200,200);

class input:public variable
{
    public:

input (int a,int b):variable (a,b){}

void click_check()
{
    int x=0,y=0;
     //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
      if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                bit=!bit;
                               // SDL_BlitSurface(setBMP, NULL, screen, &box);

              flipscreen();
          //     o-> flipscreen();
            }
        }
    }
}


};

class wire:public variable
{
    public:
        wire(){}
wire(variable a )
    {
        bit=a.get_bit();
    }
};

int load_digital1()
{
    digital_loadfile();

      return (level1_digital());

}

int level1_digital()
{
    running=true;
        input a(310,210);
        input b(310,270);
        input c(310,540);
        input d(310,480);
        wire w1,w2;
        levelno = TTF_RenderText_Solid(font,"Level 1",textcolor);
     applySurface(30,0,levelno,screen);

        applySurface(330,150,levelImage,screen);
        applySurface(1040,5,home,screen);
        Buttons bo(1040,5,234,94);
        output o(1015,375);
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    clean_up();
                    break;
            }
            w1=a&b;
            w2=c|d;
            o=w1&w2;
            //o.zero();
            o.setposition(1015,375);
            o.flipscreen();
            a.click_check();
            b.click_check();
            c.click_check();
            d.click_check();
            bo.click_check();
            if (bo.get_clicks()) return 2;
            if (o.get_bit())
            {SDL_Delay(level_delay);
            return 1;
        }

        }
    }
}

int load_digital2()
{
    digital_loadfile1();

      return (level2_digital());

}

int level2_digital()
{
    running=true;
        input a(310,210);
        input b(310,270);
        input c(310,540);
        input d(310,480);
        wire w1,w2;
        levelno = TTF_RenderText_Solid(font,"Level 2",textcolor);
     applySurface(30,0,levelno,screen);

        applySurface(330,150,levelImage,screen);
        applySurface(1040,5,home,screen);
        Buttons bo(1040,5,234,94);
        output o(1015,375);
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    clean_up();
                    break;
            }
            w1=a&b;
            w2=c&d;
            o=w1|w2;
            //o.zero();
            o.setposition(1015,375);
            o.flipscreen();
            a.click_check();
            b.click_check();
            c.click_check();
            d.click_check();
            bo.click_check();
            if (bo.get_clicks()) return 2;
            if (o.get_bit())
            {SDL_Delay(level_delay);
            return 1;
        }
        }
    }
}

int load_digital3()
{
    digital_loadfile2();

      return (level3_digital());

}

int level3_digital()
{
    running=true;
        input a(310,210);
        input b(310,270);
        input c(310,540);
        input d(310,480);
        wire w1,w2;
        levelno = TTF_RenderText_Solid(font,"Level 3",textcolor);
     applySurface(30,0,levelno,screen);

        applySurface(330,150,levelImage,screen);
        applySurface(1040,5,home,screen);
        Buttons bo(1040,5,234,94);
        output o(1015,375);
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    clean_up();
                    break;
            }
            w1=a|b;
            w2=c|d;
            o=w1&w2;
            //o.zero();
            o.setposition(1015,375);
            o.flipscreen();
            a.click_check();
            b.click_check();
            c.click_check();
            d.click_check();
            bo.click_check();
            if (bo.get_clicks()) return 2;
            if (o.get_bit())
            {SDL_Delay(level_delay);
            return 2;
        }
        }
    }
}




#endif // DIGITAL_H_INCLUDED

