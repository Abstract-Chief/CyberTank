/*File "handlers.c" create by abstarct, (чт, 07-гру-2023 14:43:14 +0200)*/
#include "handlers.h"
#include "../init/init.h"
#include "../physick/physick.h"
#include "../net/general/inet_structure.h"
#include "../net/general/packets/packets.h"
#include "../module/game_module.h"
#include "../net/client/client.h"
#include "../Debugger//debug.h"
#include <math.h>
GameEngine* GlobalEngine;
int MovingKeys[4]={UpKey,RightKey,DownKey,LeftKey};
static int FireKeys[3]={106,107,108};
#define GunPower 3
#define InetSendingN 1
float TankSpeed=1;
float TankRotatingSpeed=2;
int IndexerCount=0;
int module(int a){
   if(a<0) a*=-1; 
   return a;
}
void move_tank(Tank *tank){
   tank->pos.x+=tank->dx;
   tank->pos.y+=tank->dy;
}
void TankHandler(Tank *tank,int input){
   tank->dx=0;
   tank->dy=0;
   bool t_fire=tank->fire;
   bool need_send=tank->fire;
   if(tank->fire) tank->fire=0;
   if(input==-1) return;
   if(input==MovingKeys[0]){
      tank->dy=-TankSpeed;
      tank->rotate=North;
      need_send=1;
   }
   else if(input==MovingKeys[1]){
      tank->dx=TankSpeed*2;
      tank->rotate=East;
      need_send=1;
   } 
   else if(input==MovingKeys[2]){
      tank->dy=TankSpeed;
      tank->rotate=South;
      need_send=1;
   } 
   else if(input==MovingKeys[3]){
      tank->dx=-TankSpeed*2;
      tank->rotate=West;
      need_send=1;
   } 
   else if(input==FireKeys[0]){
      tank->angle-=TankRotatingSpeed;
      if(tank->angle<0) tank->angle+=360;
      need_send=1;
   } 
   else if(input==FireKeys[1]){
      tank->fire=1;
      Packet packet={UpdateGameInfoFirePacket,0,0};
      session_send(GlobalEngine->client->session,&packet);
      need_send=1;
   } 
   else if(input==FireKeys[2]){
      tank->angle+=TankRotatingSpeed;
      if(tank->angle>=360) tank->angle-=360;
      need_send=1;
   } 
   if(need_send){
      struct UserInfoPos info={tank->pos,tank->rotate,
         (double)tank->angle,0,(tank->dx || tank->dy),t_fire};
      Packet packet={UpdateGameInfoTankPacket,UserInfoPosSize,(char*)&info};
      session_send(GlobalEngine->client->session,&packet);
      erprintf(1,"send to server %f %f %d",tank->pos.x,tank->pos.y,tank->angle);
   }
}
