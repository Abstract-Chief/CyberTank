/*File "reader.c" create by abstarct, (чт, 07-гру-2023 00:22:07 +0200)*/
#ifndef ABSTARCT_READER_H_SENTURY
#define ABSTARCT_READER_H_SENTURY
#include "../physick/physick.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
typedef struct{
   char symbol;
   short x,y;
   short color;
} Point;

typedef struct{
   int count;
   int cols,rows;
   Point **data;
} Layer;
typedef struct{
   int count;
   float n_layer,speed;
   Layer *layers[32];
} Animation;
Animation* AnimationParse(const char* filename);
Layer* LayerParse(const char* filename);
void graphick_layer(WINDOW *win,int x,int y,Layer *layer,bool mirror_x,bool mirror_y);
bool graphick_anim(WINDOW *win,int x,int y,Animation *anim,float d,bool mirror_x,bool mirror_y);
bool graphick_animc(WINDOW *win,int x,int y,Animation *anim,float d,bool mirror_x,bool mirror_y);
coord CenterAnimation(Animation *tank);

#endif
