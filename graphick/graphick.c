/*File "graphick.c" create by abstarct, (чт, 07-гру-2023 16:41:26 +0200)*/
#include "../objects/storage.h"
#include "../physick/physick.h"
#include "reader.h"
#include <math.h>
#include "../init/init.h"
void draw_line(WINDOW *win,coord a,coord v,char symbol){
    double length = sqrt(pow(v.x, 2) + pow(v.y, 2));
    double angle = atan2(v.y,v.x);
    for (int i = 0; i <= (int)length; ++i) {
        int x = (int)(a.x + i * cos(angle));
        int y = (int)(a.y + i * sin(angle));
        mvwaddch(win,y, x, symbol);
    }
}
void graphick_gun(WINDOW *win,double angle,int x,int y,bool fire){
   coord vector_base={9,0};
   coord vector=get_angle_vector(vector_base, angle);
   vector.x*=2;
   coord center={x,y};
   draw_line(win,center,vector,'#');
   wattron(win,COLOR_PAIR(21));
   mvwprintw(win,center.y+vector.y,center.x+vector.x," ");
   wattroff(win,COLOR_PAIR(21));
   if(fire)
      ActivateAnimation(x+vector.x,y+vector.y, BoomAnimation,win);
}
void graphick_arrow(Tank *tank,coord pos,int len){
   coord size={getmaxx(stdscr),getmaxy(stdscr)};
   coord vector={pos.x-tank->pos.x,pos.y-tank->pos.y};
   coord mvector=normilize(vector);
   mvector.x*=len*2;
   mvector.y*=len;
   werase(tank->arrrow_win);
   wrefresh(tank->arrrow_win);
   refresh();
   if(get_module(vector)<=20) return;
   mvwin(tank->arrrow_win,mvector.y+size.y/2,mvector.x+size.x/2);
   wattron(tank->arrrow_win,COLOR_PAIR(Red));
   mvwprintw(tank->arrrow_win,0,1,"#");
   mvwprintw(tank->arrrow_win,1,0,"###");
   mvwprintw(tank->arrrow_win,2,1,"#");
   wattroff(tank->arrrow_win,COLOR_PAIR(Red));
   wrefresh(tank->arrrow_win);
}
/*void graphick_tank(Tank* tank,int mils){*/
   /*Animation *anim=(tank->rotate%2==0 ?  tank->anim_h : tank->anim_v);*/
   /*int x_m=(tank->rotate==West ? 1 : 0),y_m=(tank->rotate==South ? 1 : 0);*/
   /*mvwin(tank->win,tank->pos.y,tank->pos.x);*/
   /*graphick_anim(tank->win,5,5,anim,(tank->dx || tank->dy)*anim->speed*mils/10,x_m,y_m);*/
   /*graphick_gun(tank);*/
   /*wrefresh(tank->win);*/
/*}*/

