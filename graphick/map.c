/*File "map.c" create by abstarct, (нд, 10-гру-2023 01:45:07 +0200)*/
#include "map.h"
#include "reader.h"
#include "graphick.h"
void graphick_bullet(GameEngine *engine){
   
}

void graphick_one_user(struct UserInfoPos* user,coord my_pos,int x_c,int y_c,int mils){
   Animation *anim=(user->rotate==West || user->rotate==East) ? TankAnimationH : TankAnimationV;
   int x_m=(user->rotate==West ? 1 : 0),y_m=(user->rotate==South ? 1 : 0);
   int mx=user->pos.x-my_pos.x+x_c,my=user->pos.y-my_pos.y+y_c;
   werase(user->win);
   wrefresh(user->win);
   refresh();
   mvprintw(0,0,"%d %d %d %d %d %d",(int)user->pos.x,(int)user->pos.y,mx<0 , mx+user->win->_maxx>getmaxx(stdscr) , my<0 , my+user->win->_maxy>getmaxy(stdscr));
   if(mx+5<0 || mx+user->win->_maxx-10>getmaxx(stdscr) || my+5<0 || my+user->win->_maxy-10>getmaxy(stdscr)) return;
   mvwin(user->win,my,mx);
   graphick_anim(user->win,5,5,anim,anim->speed*mils/10,x_m,y_m);
   graphick_gun(user->win,user->GunAngle,user->win->_maxx/2,user->win->_maxy/2,user->fire);
   if(user->fire) user->fire=0;
   wrefresh(user->win);
}
void graphick_users(GameEngine *engine,int mils,int x_c,int y_c){
   coord my_pos=engine->storage->tank.pos; 
   for(int i=0;i<engine->storage->users_count;i++){
      graphick_one_user(&engine->storage->users[i],my_pos,x_c,y_c,mils);
   }
     
}
void graphick_world(GameEngine *engine,int mils){
   /*erase();*/
   Tank *tank=&engine->storage->tank;
   coord center=CenterAnimation(tank->anim_h);
   int center_x=getmaxx(stdscr)/2,center_y=getmaxy(stdscr)/2;
   int x_m=(tank->rotate==West ? 1 : 0),y_m=(tank->rotate==South ? 1 : 0);
   Animation *anim=(tank->rotate==West || tank->rotate==East) ? tank->anim_h : tank->anim_v;
   int x_r=center_x-center.x,y_r=center_y-center.y;
   mvwin(tank->win,y_r-7,x_r-10);
   graphick_anim(tank->win,5,5,anim,(tank->dx || tank->dy)*anim->speed*mils/10,x_m,y_m);
   graphick_gun(tank->win,tank->angle,center.x+5,center.y+5,tank->fire);
   wrefresh(tank->win);
   /*refresh();*/
   if(tank->fire) tank->fire=0;
   coord center_pos={0,0};
   graphick_arrow(tank,center_pos,30);
}
