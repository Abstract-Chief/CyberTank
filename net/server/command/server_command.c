/*File "server_command.c" create by abstarct, (сб, 09-гру-2023 15:22:15 +0200)*/
#include "server_command.h"
#include "../logic/server_logic.h"
#include "../../general/inet_structure.h"
#include <stdio.h>
#include "../../general/packets/packets.h"
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
   Packet packet_send={GameInfoResultPacket,0,0};
   session_send(session,&packet_send);
   int n_pl=GlobalServer.count_players-1;
   write(session->sock,&GlobalServer.count_bullet,sizeof(int));
   write(session->sock,&n_pl,sizeof(int));
   for(int i=0;i<GlobalServer.count_bullet;i++){
      coord bullet_pos={GlobalServer.bullets[i].x,GlobalServer.bullets[i].y};
      write(session->sock,&bullet_pos,sizeof(coord));
   }
   for(int i=0;i<GlobalServer.count_players;i++){
      Player* pl=&GlobalServer.player[i];
      if(pl->session->id==session->id) continue;
      struct UserInfoPos info={pl->pos,pl->rotate,pl->GunAngle,pl->session->id,pl->move,pl->fire};
      write(session->sock,&info,sizeof(info));
   }
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
   Packet packet_send_spawn={GetSpawnPacket,sizeof(coord),(char*)&GlobalServer.player[GlobalServer.count_players-1].pos};
   session_send(session,&packet_send_spawn);
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
   pl->fire=info->fire;
   pl->GunAngle=info->GunAngle;
   pl->move=info->move;
   return 0;
}
