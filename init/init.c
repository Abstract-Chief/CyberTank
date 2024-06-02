/*File "init.c" create by abstarct, (чт, 07-гру-2023 16:39:15 +0200)*/
#include "../objects/storage.h"
#include "init.h"
Animation* BoomAnimation;
Animation* TankAnimationV;
Animation* TankAnimationH;
#define BoomSpeed 0.015
void init_graphick_obj(){
   BoomAnimation=AnimationParse("data/boom.eanim");
   BoomAnimation->speed=BoomSpeed;
   TankAnimationV=AnimationParse("data/tank_v.eanim");
   TankAnimationH=AnimationParse("data/tank_h.eanim");
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
   tank->rotate=South;
   wrefresh(tank->win);
}
void init_storage(StorageGame *storage){
   init_tank(&storage->tank,10,10,0,0,"data/tank_v.eanim","data/tank_h.eanim",0.09);
}
void init(){
   initscr();
   start_color();
   use_default_colors();
   init_pair(RedWhite,COLOR_WHITE,COLOR_RED);
   init_pair(NUllRed,COLOR_RED,-1);
   init_pair(YellowBlue,COLOR_BLUE,COLOR_YELLOW);
   init_pair(Yellow,COLOR_YELLOW,COLOR_YELLOW);
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