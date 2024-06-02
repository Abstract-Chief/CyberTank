/*File "graphick.c" create by abstarct, (чт, 07-гру-2023 16:41:26 +0200)*/
#include "../objects/storage.h"
#include "../physick/physick.h"
#include "reader.h"
#include <math.h>
void draw_line(WINDOW *win,coord a,coord v,char symbol){
    double length = sqrt(pow(v.x, 2) + pow(v.y, 2));
    double angle = atan2(v.y,v.x);
    // Отрисовка каждого символа на линии
    for (int i = 0; i <= (int)length; ++i) {
        int x = (int)(a.x + i * cos(angle));
        int y = (int)(a.y + i * sin(angle));
        mvwaddch(win,y, x, symbol);
    }
}
void graphick_gun(Tank *tank){
   coord vector_base={9,0};
   coord vector=get_angle_vector(vector_base, tank->angle);
   coord center=CenterAnimation(tank->anim_h);
   vector.x*=2;
   mvprintw(2,0,"%d   %d %d",tank->angle,(int)vector.x,(int)vector.y);
   center.x+=5;center.y+=5;
   draw_line(tank->win,center,vector,'#');
   wattron(tank->win,COLOR_PAIR(21));
   mvwprintw(tank->win,center.y+vector.y,center.x+vector.x," ");
   wattroff(tank->win,COLOR_PAIR(21));
   if(tank->fire){
      /*AddBullet(tank,normilize(vector));*/
      ActivateAnimation(center.x+vector.x,center.y+vector.y, BoomAnimation,tank->win);
      tank->fire=0;
   }
}
void graphick_tank(Tank* tank,int mils){
   Animation *anim=(tank->rotate%2==0 ?  tank->anim_h : tank->anim_v);
   int x_m=(tank->rotate==West ? 1 : 0),y_m=(tank->rotate==South ? 1 : 0);
   mvwin(tank->win,tank->pos.y,tank->pos.x);
   graphick_anim(tank->win,5,5,anim,(tank->dx || tank->dy)*anim->speed*mils/10,x_m,y_m);
   graphick_gun(tank);
   wrefresh(tank->win);
}

