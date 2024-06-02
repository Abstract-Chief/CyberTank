/*File "map.c" create by abstarct, (нд, 10-гру-2023 01:45:07 +0200)*/
#include "map.h"
#include "reader.h"
#include "../init/init.h"
#include "graphick.h"
void graphick_one_bullet(Bullet* bullet,coord my_pos,int x_c,int y_c){
   int mx=(bullet->pos.x-my_pos.x)+x_c,my=(bullet->pos.y-my_pos.y)+y_c;
   if(mx<0 || my<0 || mx>getmaxx(stdscr) || my>getmaxy(stdscr)) return;
   /*attron(COLOR_PAIR(Yellow));*/
   mvprintw(my,mx,"###");
   /*attroff(COLOR_PAIR(Yellow));*/
}
void graphick_bullets(GameEngine *engine,int x_c,int y_c){
   coord my_pos=engine->storage->tank.pos; 
   for(int i=0;i<engine->storage->bullets_count;i++){
      mvprintw(i,0,"b: %f %f",engine->storage->bullets[i].pos.x,engine->storage->bullets[i].pos.y);
      graphick_one_bullet(&engine->storage->bullets[i],my_pos,x_c,y_c);
   }
}

void graphick_one_user(struct UserInfoPos* bullet,coord my_pos,int x_c,int y_c,int mils){
   Animation *anim=(bullet->rotate==West || bullet->rotate==East) ? TankAnimationH : TankAnimationV;
   coord center_anim=CenterAnimation(anim);
   int x_m=(bullet->rotate==West ? 1 : 0),y_m=(bullet->rotate==South ? 1 : 0);
   int mx=(bullet->pos.x-my_pos.x)+x_c,my=(bullet->pos.y-my_pos.y)+y_c;
   if(mx+center_anim.x<0 || my+center_anim.y<0 || mx-center_anim.x>getmaxx(stdscr) || my-center_anim.y>getmaxy(stdscr)) return;
   graphick_animc(stdscr,mx,my,anim,anim->speed*mils/10,x_m,y_m);
   graphick_gun(stdscr,bullet->GunAngle,mx,my,bullet->fire);
   if(bullet->fire) bullet->fire=0;
}
void graphick_users(GameEngine *engine,int mils,int x_c,int y_c){
   coord my_pos=engine->storage->tank.pos; 
   for(int i=0;i<engine->storage->users_count;i++)
      graphick_one_user(&engine->storage->users[i],my_pos,x_c,y_c,mils);
}
void graphick_world(GameEngine *engine,int mils){
   Tank *tank=&engine->storage->tank;
   int center_x=getmaxx(stdscr)/2,center_y=getmaxy(stdscr)/2;
   int x_m=(tank->rotate==West ? 1 : 0),y_m=(tank->rotate==South ? 1 : 0);
   Animation *anim=(tank->rotate==West || tank->rotate==East) ? tank->anim_h : tank->anim_v;
   coord center_pos={0,0};
   graphick_arrow(tank,center_pos,30);
   graphick_users(engine, mils,center_x,center_y);
   graphick_animc(stdscr,center_x,center_y,anim,(tank->dx || tank->dy)*anim->speed*mils/10,x_m,y_m);
   graphick_gun(stdscr,tank->angle,center_x,center_y,tank->fire);
   graphick_bullets(engine,center_x,center_y);
   if(tank->fire) tank->fire=0;
}
