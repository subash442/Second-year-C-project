#ifndef ANALOG_H_INCLUDED
#define ANALOG_H_INCLUDED
#include <SDL/SDL.h>
#include "Design.h"
int level1_analog();
int level2_analog();
int level3_analog();
using namespace std;

class circuit
{
    protected:
SDL_Rect box;
    int bit;

public:
circuit(){}
circuit(int a):bit(a){}
circuit( int x, int y)
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
    circuit operator+ (circuit b)
    {
        return circuit(bit&b.bit);
    }

     circuit operator|| (circuit b)
    {
        return circuit(bit|b.bit);
    }


    int get_bit()
    {
        return bit;
    }

    void flipscreen()
    {

    if (bit==1)
               {

                SDL_BlitSurface(setBMP, NULL, screen, &box);
                 SDL_Flip(screen);


               }
               else if (bit==0)
               {
                    SDL_BlitSurface(resetBMP, NULL, screen, &box);

                 SDL_Flip(screen);

               }

             /*  else if (bit==2)
               {
                   SDL_BlitSurface (shortBMP,NULL,screen,&box);

               }*/
    }



    void setposition(int x,int y)
    {
        box.x = x;
    box.y = y;
    }

};




      // output o (200,200);

class npn:public circuit
{
    public:

npn (int a,int b):circuit(a ,b){}

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


class branch:public circuit
{
    public:
        branch(){}
        branch (int a):circuit(a){}
branch(circuit a )
    {
        bit=a.get_bit();
    }
};

branch circuit1,circuit2;

class LED:public circuit
{
public:
    LED(){}
    LED (int a,int b):circuit(a ,b){}

    LED(circuit a )
    {

        bit=a.get_bit();


    }

    check()
    {
        if ((circuit1.get_bit()==0 && circuit2.get_bit()==0) || (circuit1.get_bit()==0 && circuit2.get_bit()==1) )
        {
            bit=0;
        }
        else if (circuit1.get_bit()==1 && circuit2.get_bit()==0 )
        {
            bit=1;
            level_completed();


        }
        else if (circuit1.get_bit()==1 && circuit2.get_bit()==1)
            bit=0;

    }


};

int load_analog1()
{
    analog_loadfile();

      return (level1_analog());

}

int level1_analog()
{
    running =true;
            applySurface(1040,5,home,screen);

        applySurface(0,0,levelImage,screen);

        npn a(720,375);
        //npn b(930,192);
        LED o(570,192);

                levelno = TTF_RenderText_Solid(font,"Level 1",textcolor);
applySurface(30,0,levelno,screen);

        Buttons bo(1040,5,234,94);
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

       circuit1=a;
       //circuit2=b;
o.check();
o.flipscreen();
            a.click_check();
//            b.click_check();

bo.click_check();
            if (bo.get_clicks()) return 2;
if (o.get_bit())
             {
            {SDL_Delay(level_delay);
            return 1;
            }
        }
    }
}
}

int load_analog2()
{
    analog_loadfile1();

      return (level2_analog());

}

int level2_analog()
{
    running =true;
            applySurface(1040,5,home,screen);

        applySurface(0,0,levelImage,screen);

        npn a(415,600);
        npn b(1018,287);
        LED o(1030,478);

                levelno = TTF_RenderText_Solid(font,"Level 2",textcolor);
applySurface(30,0,levelno,screen);

        Buttons bo(1040,5,234,94);
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

       circuit1=a;
       circuit2=b;
o.check();
o.flipscreen();
            a.click_check();
            b.click_check();

bo.click_check();
            if (bo.get_clicks()) return 2;
             if (o.get_bit())

            {SDL_Delay(level_delay);
            return 2;
            }

    }
}
}



/*int load_analog3()
{
    analog_loadfile2();

      return (level3_analog());

}

int level1_analog()
{
    running =true;
            applySurface(1040,5,home,screen);

        applySurface(0,0,levelImage,screen);

        npn a(415,600);
        npn b(1018,287);
        LED o(1030,478);

                levelno = TTF_RenderText_Solid(font,"Level 1",textcolor);
applySurface(30,0,levelno,screen);

        Buttons bo(1040,5,234,94);
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
            }

       circuit1=a;
       circuit2=b;
o.check();
o.flipscreen();
            a.click_check();
            b.click_check();

bo.click_check();
            if (bo.get_clicks()) return 2;

        }
    }
}*/





#endif





