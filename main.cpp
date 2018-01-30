#include "Design.h"
#include "digital.h"
#include "analog.h"

void mainpage_loading();

int main(int argc, char* argv[])
{

	   if (sdl_init()==false) return 1;
        mainpage_loading();
        clean_up();

    return 0;
}

void mainpage_loading()
{
Buttons bu1(516,353,352,109);
Buttons bu2(520,572,352,109);
main_page(bu1,bu2);
Buttons b1(618,234,164,72);
Buttons b2(618,351,164,72);
Buttons b3(618,475,164,72);


        if (bu1.get_clicks())
        {
           second_page(b1,b2,b3,'a');
        }
        else if (bu2.get_clicks())
        {
            second_page(b1,b2,b3,'d');
        }
   if (b1.get_clicks())
    {
        if (bu2.get_clicks())
        {

        if(load_digital1()==2)
            mainpage_loading();

        if(load_digital2()==2)
            mainpage_loading();

        load_digital3();

mainpage_loading();
        }

          if (bu1.get_clicks())
        {
            if(load_analog1()==2)
            mainpage_loading();

            load_analog2();
            mainpage_loading();
        }

    }
    else if (b2.get_clicks())
    {
        mainpage_loading();

    }
    else if (b3.get_clicks())
    {
        quit = true;
    }
}






