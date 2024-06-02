/*File "map.c" create by abstarct, (нд, 10-гру-2023 01:45:07 +0200)*/
#include "map.h"
#include "reader.h"
#include "../init/init.h"
#include "graphick.h"
#include "../player/handlers.h"

void graphick_one_bullet(Bullet* bullet,coord my_pos,int x_c,int y_c){
   int mx=(bullet->pos.x-my_pos.x)+x_c,my=(bullet->pos.y-my_pos.y)+y_c;
   if(mx<0 || my<0 || mx>getmaxx(GlobalEngine->storage->general_win) || my>getmaxy(GlobalEngine->storage->general_win)) return;
   wattron(GlobalEngine->storage->general_win,COLOR_PAIR(Yellow));
   mvwprintw(GlobalEngine->storage->general_win,my,mx,"###");
   attroff(COLOR_PAIR(Yellow));
}
void graphick_bullets(GameEngine *engine,int x_c,int y_c){
   coord my_pos=engine->storage->tank.pos; 
   for(int i=0;i<engine->storage->bullets_count;i++){
      /*mvprintw(i,0,"b: %f %f",engine->storage->bullets[i].pos.x,engine->storage->bullets[i].pos.y);*/
      graphick_one_bullet(&engine->storage->bullets[i],my_pos,x_c,y_c);
   }
}

void graphick_one_user(struct UserInfoPos* bullet,coord my_pos,int x_c,int y_c,int mils){
   Animation *anim=(bullet->rotate==West || bullet->rotate==East) ? TankAnimationH : TankAnimationV;
   coord center_anim=CenterAnimation(anim);
   int x_m=(bullet->rotate==West ? 1 : 0),y_m=(bullet->rotate==South ? 1 : 0);
   int mx=(bullet->pos.x-my_pos.x)+x_c,my=(bullet->pos.y-my_pos.y)+y_c;
   if(mx+center_anim.x<0 || my+center_anim.y<0 || mx-center_anim.x>getmaxx(GlobalEngine->storage->general_win) || my-center_anim.y>getmaxy(GlobalEngine->storage->general_win)) return;
   graphick_animc(GlobalEngine->storage->general_win,mx,my,anim,bullet->move*anim->speed*mils/10,x_m,y_m);
   graphick_gun(GlobalEngine->storage->general_win,bullet->GunAngle,mx,my,0);
   /*if(bullet->fire) bullet->fire=0;*/
}
void graphick_users(GameEngine *engine,int mils,int x_c,int y_c){
   coord my_pos=engine->storage->tank.pos; 
   mvwprintw(engine->storage->general_win,2,0,"%d  ",engine->storage->users_count);
   if(engine->storage->users_count>0){
      mvwprintw(engine->storage->general_win,1,0,"--%d--  \n",engine->storage->users[0].fire);
   }
   for(int i=0;i<engine->storage->users_count;i++)
      graphick_one_user(&engine->storage->users[i],my_pos,x_c,y_c,mils);
}
void center_graphick(Tank *tank,int x_c,int y_c,int mils){
   int mx=(0-tank->pos.x)+x_c,my=(0-tank->pos.y)+y_c;
   graphick_animc(GlobalEngine->storage->general_win,mx,my,BoomAnimationLoop,mils*0.015,0,0);  
}
void graphick_world(GameEngine *engine,int mils){
   Tank *tank=&engine->storage->tank;
   int center_x=getmaxx(GlobalEngine->storage->general_win)/2,center_y=getmaxy(GlobalEngine->storage->general_win)/2;
   int x_m=(tank->rotate==West ? 1 : 0),y_m=(tank->rotate==South ? 1 : 0);
   Animation *anim=(tank->rotate==West || tank->rotate==East) ? tank->anim_h : tank->anim_v;
   coord center_pos={0,0};
   graphick_arrow(tank,center_pos,25);
   center_graphick(tank,center_x,center_y,mils);
   graphick_users(engine, mils,center_x,center_y);
   graphick_animc(GlobalEngine->storage->general_win,center_x,center_y,anim,(tank->dx || tank->dy)*anim->speed*mils/10,x_m,y_m);
   graphick_gun(GlobalEngine->storage->general_win,tank->angle,center_x,center_y,tank->fire);
   graphick_bullets(engine,center_x,center_y);
   mvwprintw(GlobalEngine->storage->general_win,getmaxy(GlobalEngine->storage->general_win),0,"%d %d",(int)tank->pos.x,(int)tank->pos.y);
}
