#ifndef ANIMATION_H
    #define ANIMATION_H

    #include <allegro.h>
    #include <assert.h>
    #include <loadpng.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>

enum a4a_animation_type_t
{
    ANIMATION_TYPE_BMP,
    ANIMATION_TYPE_PNG
};

typedef enum a4a_animation_type_t a4a_animation_type_t;

struct a4a_animation_t
{
    a4a_animation_type_t type_;
    int num_frames_;
    int start_ticks_;
    int ticks_per_frame_;
    BITMAP ** frames_;
};

typedef struct a4a_animation_t a4a_animation_t;

a4a_animation_t * a4a_animation_create(
        a4a_animation_type_t,
        int,
        int,
        ...);

a4a_animation_t * a4a_animation_createa(
        a4a_animation_type_t,
        int,
        int,
        char * []);

a4a_animation_t * a4a_animation_createf(
        a4a_animation_type_t,
        int,
        int,
        const char *);

a4a_animation_t * a4a_animation_createv(
        a4a_animation_type_t,
        int,
        int,
        va_list);

void a4a_animation_destroy(a4a_animation_t **);

BITMAP * a4a_animation_begin(a4a_animation_t * a, int ticks);

BITMAP * a4a_animation_frame(a4a_animation_t * a, int ticks);

#endif

