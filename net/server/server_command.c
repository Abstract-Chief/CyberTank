/*File "server_command.c" create by abstarct, (сб, 09-гру-2023 15:22:15 +0200)*/
#include "server_command.h"
#include "server_logic.h"
#include "../general/inet_structure.h"
#include <stdio.h>
   /*GetSpawnPacket=2,*/
   /*GetHitPacket,*/
   /*GameInfoResultPacket,*/
   /*LoginServerPacket,*/
   /*LoginServerResultPacket,*/
   /*ConnectGamePacket,*/
   /*GetGameInfoPacket,*/
   /*UpdateGameInfoBulletPacket,*/
   /*UpdateGameTankInfoPacket,*/
int GameInfoResultHandler(Session* session,Packet *packet){
   /*printf("send for %d game info\n",session->id);*/
   return 0;
}
int LoginServerResultHandler(Session* session,Packet *packet){
   char *name=packet->data;  
   /*printf("try login name %s\n",name);*/
   int result=add_player(session,name);
   if(result==0) result=1;
   else result=0;
   Packet packet_send={LoginServerResultPacket,sizeof(int),(char*)&result};
   session_send(session,&packet_send);
   return 0;
}
int UpdateGameInfoFireHadler(Session* session,Packet *packet){
   Player* pl=GetPlayer(session);
   if(pl==NULL) return 0;
   AddBullet(pl);
   /*printf("Add Bullet\n");*/
   return 0;
}
int UpdateGameInfoTankHadler(Session* session,Packet *packet){
   Player* pl=GetPlayer(session);
   if(pl==NULL) return 0;
   struct UserInfoPos *info=(struct UserInfoPos *)packet->data;
   pl->pos=info->pos;
   pl->rotate=info->rotate;
   pl->GunAngle=info->GunAngle;
   return 0;
}
