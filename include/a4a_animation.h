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

#ifndef ANIMATION_H
    #define ANIMATION_H

    #include <allegro.h>
    #include <assert.h>
    #include <loadpng.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>

enum a4a_sprite_type_t
{
    A4A_SPRITE_TYPE_BMP,
    A4A_SPRITE_TYPE_PNG
};

typedef enum a4a_sprite_type_t a4a_sprite_type_t;

struct a4a_animation_t
{
    int num_frames_;
    int start_ticks_;
    int ticks_per_frame_;
    BITMAP ** frames_;
};

typedef struct a4a_animation_t a4a_animation_t;

a4a_animation_t * a4a_animation_create(
        a4a_sprite_type_t,
        int,
        int,
        ...);

a4a_animation_t * a4a_animation_createa(
        a4a_sprite_type_t,
        int,
        int,
        char * []);

a4a_animation_t * a4a_animation_createf(
        a4a_sprite_type_t,
        int,
        int,
        const char *);

a4a_animation_t * a4a_animation_createv(
        a4a_sprite_type_t,
        int,
        int,
        va_list);

void a4a_animation_destroy(a4a_animation_t **);

BITMAP * a4a_animation_begin(a4a_animation_t * a, int ticks);

BITMAP * a4a_animation_frame(a4a_animation_t * a, int ticks);

#endif

