/*File "server_logic.c" create by abstarct, (сб, 09-гру-2023 16:20:52 +0200)*/
#include "server_logic.h"
#include <string.h>
#include <stdio.h>
#define BulletVelocityAlpha -0.00001
#define BulletVelocity 0.2
float mod(float data){
   return (data<0 ? data*-1:data);
}
float get_znak(float data){
   return (data<0 ? -1:1);
}
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
void set_player(Session *session,const char *name,int index){
   GlobalServer.player[index].session=session;
   memcpy(GlobalServer.player[index].name,name,sizeof(GlobalServer.player[index].name));
}
int add_player(Session *session,const char *name){
   if(GlobalServer.count_players>=MAX_PLAYER_COUNT-1) return -1;
   if(CheckLogin(name)) return -2;
   set_player(session,name,GlobalServer.count_players);
   GlobalServer.count_players++;
   /*printf("succeful add player %s\n",name);*/
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
         /*printf("del player %d %s\n",session->id,GlobalServer.player[i].name);*/
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
void PlayerCheck(int mils){
}
void ServerLogic(int mils){
   BulletHandler(mils);
   PlayerCheck(mils);
}
void AddBullet(Player* player){
   Bullet *bullet=&GlobalServer.bullets[GlobalServer.count_bullet++];
   bullet->x=player->pos.x;//chyba
   bullet->y=player->pos.y;//chyba
   coord one_vector={0,1};
   coord result=get_angle_vector(one_vector,player->GunAngle+5);
   bullet->speed=BulletVelocity;
   bullet->dx=result.x;
   bullet->dy=result.y;
   bullet->TankId=player->session->id;
}

