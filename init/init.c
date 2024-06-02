/*File "init.c" create by abstarct, (чт, 07-гру-2023 16:39:15 +0200)*/
#include "../objects/storage.h"
#include "init.h"
#include <string.h>
Animation* BoomAnimation;
Animation* TankAnimationV;
Animation* TankAnimationH;
Animation* BoomAnimationLoop;
#define BoomSpeed 0.015
void init_graphick_obj(){
   BoomAnimation=AnimationParse("data/boom.eanim",0);
   BoomAnimationLoop=AnimationParse("data/boom.eanim",1);
   BoomAnimation->speed=BoomSpeed;
   BoomAnimationLoop->speed=BoomSpeed;
   TankAnimationV=AnimationParse("data/tank_v.eanim",1);
   TankAnimationH=AnimationParse("data/tank_h.eanim",1);
}

void init_tank(Tank *tank,int x,int y,int hp,int reload,const char *filename_v,const char *filename_h,float speed_anim){
   tank->pos.x=x-5;
   tank->pos.y=y-5;
   tank->hp=hp;
   tank->fire=0;
   tank->angle=0;
   tank->reload=reload;
   tank->anim_v=TankAnimationV;
   tank->anim_h=TankAnimationH;
   tank->anim_h->speed=speed_anim;
   tank->anim_v->speed=speed_anim;
   tank->win=newwin(tank->anim_v->layers[0]->rows+10,tank->anim_v->layers[0]->cols+10,x,y);
   tank->arrrow_win=newwin(4,4,0,0);
   tank->rotate=South;
   wrefresh(tank->win);
}
#define GENERAL_SCREEN_SIZEX 200
#define GENERAL_SCREEN_SIZEY 50
void init_storage(StorageGame *storage){
   init_tank(&storage->tank,10,10,0,0,"data/tank_v.eanim","data/tank_h.eanim",0.09);
   storage->general_win=newwin(GENERAL_SCREEN_SIZEY,GENERAL_SCREEN_SIZEX
         ,(getmaxy(stdscr)-GENERAL_SCREEN_SIZEY)/2,(getmaxx(stdscr)-GENERAL_SCREEN_SIZEX)/2);
   wrefresh(storage->general_win);
   refresh();
   memset(storage->users,0,sizeof(storage->users));
}
void init(){
   initscr();
   start_color();
   use_default_colors();
   init_pair(RedWhite,COLOR_WHITE,COLOR_RED);
   init_pair(NUllRed,COLOR_RED,-1);
   init_pair(YellowBlue,COLOR_BLUE,COLOR_YELLOW);
   init_pair(Yellow,38,38);
   init_pair(Red,COLOR_RED,COLOR_RED);
   init_pair(Blue,COLOR_BLUE,COLOR_BLUE);
   curs_set(0);
   noecho();
   /*nocbreak();*/
   nodelay(stdscr,true);
   keypad(stdscr,0);
}
int close(){
   endwin();
   return 0;
}
