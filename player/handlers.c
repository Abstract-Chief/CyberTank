/*File "handlers.c" create by abstarct, (чт, 07-гру-2023 14:43:14 +0200)*/
#include "handlers.h"
#include "../init/init.h"
#include "../physick/physick.h"
#include "../net/general/inet_structure.h"
#include "../net/general/packets/packets.h"
#include "../module/game_module.h"
#include "../net/client/client.h"
#include <math.h>
GameEngine* GlobalEngine;
int MovingKeys[4]={UpKey,RightKey,DownKey,LeftKey};
static int FireKeys[3]={106,107,108};
#define GunPower 3
float TankSpeed=1;
float TankRotatingSpeed=2;
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
   bool move=false;
   if(input==-1) return;
   if(input==MovingKeys[0]){
      move=1;
      tank->dy=-TankSpeed;
      tank->rotate=North;
   }
   else if(input==MovingKeys[1]){
      move=1;
      tank->dx=TankSpeed*2;
      tank->rotate=East;
   } 
   else if(input==MovingKeys[2]){
      move=1;
      tank->dy=TankSpeed;
      tank->rotate=South;
   } 
   else if(input==MovingKeys[3]){
      move=1;
      tank->dx=-TankSpeed*2;
      tank->rotate=West;
   } 
   else if(input==FireKeys[0]){
      move=1;
      tank->angle-=TankRotatingSpeed;
      if(tank->angle<0) tank->angle+=360;
      move=1;
   } 
   else if(input==FireKeys[1]){
      werase(tank->win);
      tank->dy-=GunPower*cos(degrees_to_radian(tank->angle));
      tank->dx-=GunPower*sin(degrees_to_radian(tank->angle));
      tank->fire=1;
      move=1;
      Packet packet={UpdateGameInfoFirePacket,0,0};
      session_send(GlobalEngine->client->session,&packet);
   } 
   else if(input==FireKeys[2]){
      move=1;
      tank->angle+=TankRotatingSpeed;
      if(tank->angle>=360) tank->angle-=360;
   } 
   if(move){
      struct UserInfoPos info={tank->pos,tank->rotate,tank->angle};
      Packet packet={UpdateGameInfoTankPacket,sizeof(info),(char*)&info};
      session_send(GlobalEngine->client->session,&packet);
   }
}
