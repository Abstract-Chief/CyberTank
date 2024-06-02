/*File "server_logic.c" create by abstarct, (сб, 09-гру-2023 16:20:52 +0200)*/
#include "server_logic.h"
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include "collision.h"
#include <time.h>
#include <stdlib.h>
#include "../command/server_command.h"
#define BulletVelocityAlpha -0.0001
#define BulletVelocity 0.1
#define MAP_SIZE 200
#define MINIMAL_SPAWN_DISTANCE 50
int generateRandomNumber(int a, int b) {
    return rand() % (b - a + 1) + a;
}
float mod(float data){
   return (data<0 ? data*-1:data);
}
float get_znak(float data){
   return (data<0 ? -1:1);
}
/*void set_boom_all_player(Session* session,coord pos){*/
   /*Packet packet={SetBoomInfo,sizeof(coord),(char*)&pos};*/
   /*for(int i=0;i<GlobalServer.count_players;i++)*/
      /*if(GlobalServer.player[i].session->id!=session->id)*/
         /*session_send(GlobalServer.player[i].session,&packet);*/
/*}*/
Player* GetPlayer(Session *session){
   for(int i=0;i<GlobalServer.count_players;i++){
      if(GlobalServer.player[i].session->id==session->id){
         return &GlobalServer.player[i];
      }
   }
   return NULL;
}
bool CheckLogin(const char *name){
   for(int i=0;i<GlobalServer.count_players;i++){
      if(!strcmp(GlobalServer.player[i].name,name)){
         return 1;
      }
   }
   return 0;
}
coord get_spawn_point(){
   coord r={0,0};
   bool flag=0;
   do{
      r.x=generateRandomNumber(-MAP_SIZE,MAP_SIZE);
      r.y=generateRandomNumber(-MAP_SIZE,MAP_SIZE);
      for(int i=0;i<GlobalServer.count_players;i++){
         Player *pl=&GlobalServer.player[i];
         if(get_distance(r,pl->pos)<=MINIMAL_SPAWN_DISTANCE) flag=1;
      }
   }while(flag);
   return r;
}
void spawn_player(Player *pl){
   pl->SpawnTime=time(NULL);
   pl->pos=get_spawn_point();
}
void set_player(Session *session,const char *name,int index){
   Player *pl=&GlobalServer.player[index];
   pl->session=session;
   coord size={26,13};
   pl->hitbox=create_hitbox(size,true);//center hitbox
   memcpy(pl->name,name,sizeof(pl->name));
   spawn_player(pl);
}
int add_player(Session *session,const char *name){
   if(GlobalServer.count_players>=MAX_PLAYER_COUNT-1) return -1;
   if(CheckLogin(name)) return -2;
   set_player(session,name,GlobalServer.count_players);
   GlobalServer.count_players++;
   return 0;
}
int del_player_index(int index){
   for(int i=index;i<GlobalServer.count_players-1;i++){
      Player *a=&GlobalServer.player[i],*b=&GlobalServer.player[i+1];
      memcpy(a,b,sizeof(Player));
   }
   GlobalServer.count_players--;
   return 0;
}
int del_player(Session* session){
   for(int i=0;i<GlobalServer.count_players;i++){
      GlobalServer.player[i].session->id=session->id;
      if(GlobalServer.player[i].session->id==session->id){
         mvprintw(0,0,"del player %d",session->id);
         refresh();
         del_player_index(i);
         return 1;   
      }
   }
   return 0;
}
void DelBullet(int index){
   GlobalServer.count_bullet--;
   for(int i=index;i<GlobalServer.count_bullet;i++){
      Bullet *a=&GlobalServer.bullets[i];
      Bullet *b=&GlobalServer.bullets[i+1];
      a->x=b->x;
      a->y=b->y;
      a->dx=b->dx;
      a->dy=b->dy;
      a->TankId=b->TankId;
   }
}
void BulletHandler(int mils){
   for(int i=0;i<GlobalServer.count_bullet;i++){
      Bullet *bullet=&GlobalServer.bullets[i];
      if(mils==0) mils=1;
      bullet->x+=bullet->dx*mils*bullet->speed;
      bullet->y+=bullet->dy*mils*bullet->speed;
      bullet->speed+=BulletVelocityAlpha*mils;
      if(bullet->speed<0)
         DelBullet(i--);
   }
}
int CheckPlayerCollisionBullet(Player *p,coord *pos){
   for(int i=0;i<GlobalServer.count_bullet;i++){
      Bullet *bullet=&GlobalServer.bullets[i];
      coord pos_b={bullet->x,bullet->y};
      if(bullet->TankId==p->session->id) continue;
      if(check_collision(&p->hitbox,p->pos,pos_b)){
         *pos=pos_b;
         return i;
      }
   }
   return -1;
}
void PlayerCheck(){
   for(int i=0;i<GlobalServer.count_players;i++){
      Player *pl = &GlobalServer.player[i];
      coord pos;
      int r=CheckPlayerCollisionBullet(pl,&pos);
      if(r>=0){
         Packet packet={GetHitPacket,sizeof(coord),(char*)&pos};
         session_send(pl->session,&packet);
         DelBullet(r);
         del_player_index(i);
      }
   }
}
void ServerLogic(int mils){
   BulletHandler(mils);
   PlayerCheck();
}
void AddBullet(Player* player){
   Bullet *bullet=&GlobalServer.bullets[GlobalServer.count_bullet++];
   bullet->x=player->pos.x;
   bullet->y=player->pos.y;
   coord one_vector={0,1};
   coord result=get_angle_vector(one_vector,player->GunAngle);
   /*coord boom_pos={bullet->x+result.x,bullet->y};*/
   /*set_boom_all_player(player->session,boom_pos);*/
   bullet->speed=BulletVelocity;
   bullet->dx=result.x*2;
   bullet->dy=result.y;
   bullet->TankId=player->session->id;
}

