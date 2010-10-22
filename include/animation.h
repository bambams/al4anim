#ifndef ANIMATION_H
    #define ANIMATION_H

    #include <allegro.h>
    #include <assert.h>
    #include <loadpng.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>

enum animation_type_t
{
    ANIMATION_TYPE_BMP,
    ANIMATION_TYPE_PNG
};

typedef enum animation_type_t animation_type_t;

struct animation_t
{
    animation_type_t type_;
    int num_frames_;
    int start_ticks_;
    int ticks_per_frame_;
    BITMAP ** frames_;
};

typedef struct animation_t animation_t;

animation_t * animation_create(animation_type_t, int, int, ...);
animation_t * animation_createa(animation_type_t, int, int, char * []);
animation_t * animation_createf(animation_type_t, int, int, const char *);
animation_t * animation_createv(animation_type_t, int, int, va_list);
void animation_destroy(animation_t **);
BITMAP * animation_begin(animation_t * a, int ticks);
BITMAP * animation_frame(animation_t * a, int ticks);

#endif

