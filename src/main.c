#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

#include "animation.h"

#define FATAL_ERROR(msg) \
    do \
    { \
        fprintf(stderr, msg); \
        exit(1); \
    }while(0)

#define FATAL_ERRORA(msg) \
    do \
    { \
        fprintf(stderr, msg, allegro_error); \
        exit(1); \
    }while(0)

typedef int bool;

const bool false = 0;
const bool true = 1;

volatile int ticks = 0;
volatile int total_ticks = 0;
void ticker()
{
    ticks++;
    total_ticks++;
}
END_OF_FUNCTION(ticker)
 
const int updates_per_second = 60;
 
int main()
{
    if(allegro_init() != 0)
        FATAL_ERRORA("allegro_init(): %s\n");

    if(install_keyboard() != 0)
        FATAL_ERROR("install_keyboard()\n");

    if(install_timer() != 0)
        FATAL_ERRORA("install_timer(): %s\n");

    set_color_depth(32);

    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0) != 0)
        FATAL_ERRORA("set_gfx_mode(): %s\n");
 
    //initialize the timer
    LOCK_VARIABLE(ticks);
    LOCK_VARIABLE(total_ticks);
    LOCK_FUNCTION(ticker);
    install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));

    bool quit = false;

    animation_t * haddokken = animation_createf(
            ANIMATION_TYPE_PNG,
            10,
            5,
            "media/ryu-haddoken%02d.png");

    if(!haddokken)
    {
        allegro_message(
                "Failed to create haddokken animation. Aborting...");
        exit(1);
    }

    animation_begin(haddokken, total_ticks);

    while(!quit && !key[KEY_ESC])
    {
        while(ticks == 0)
        {
            rest(100 / updates_per_second);//rest until a full tick has passed
        }
 
        while(ticks > 0)
        {
            int old_ticks = ticks;
 
            ticks--;
            if(old_ticks <= ticks)//logic is taking too long: abort and draw a frame
                break; 
        }
 
        BITMAP * haddokken_frame = animation_frame(
                haddokken,
                total_ticks);

        blit(
                haddokken_frame,
                screen,
                0,
                0,
                100,
                100,
                haddokken_frame->w,
                haddokken_frame->h);
    }

    animation_destroy(&haddokken);

    return 0;
}
END_OF_MAIN()

