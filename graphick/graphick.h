/*File "graphick.c" create by abstarct, (чт, 07-гру-2023 16:41:26 +0200)*/
#ifndef ABSTARCT_GRAPHICK_H_SENTURY
#define ABSTARCT_GRAPHICK_H_SENTURY
#include "../objects/storage.h"
//void graphick_tank(Tank* tank,int mils);
void graphick_gun(WINDOW *win,double angle,int x,int y,bool fire);

void graphick_arrow(Tank *tank,coord pos,int len);

#endif
