/*
 * al4anim is a simple animation library for Allegro 4.
 * Copyright (C) 2010 Brandon McCaig
 *
 * This file is part of al4anim.
 *
 * al4anim is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * al4anim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with al4anim.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

#include "a4a_animation.h"

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

    a4a_animation_t * haddokken = a4a_animation_createf(
            A4A_SPRITE_TYPE_PNG,
            10,
            5,
            "media/ryu-haddoken%02d.png");

    if(!haddokken)
    {
        allegro_message(
                "Failed to create haddokken a4a_animation. Aborting...");
        exit(1);
    }

    a4a_animation_begin(haddokken, total_ticks);

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
 
        BITMAP * haddokken_frame = a4a_animation_frame(
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

    a4a_animation_destroy(&haddokken);

    return 0;
}
END_OF_MAIN()

