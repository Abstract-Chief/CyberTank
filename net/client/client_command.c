/*File "client_command.c" create by abstarct, (сб, 09-гру-2023 18:11:44 +0200)*/
#include <string.h>
#include "client_command.h"
#include "../../Debugger/debug.h"
#include "../../player/handlers.h"
#include "../../graphick/reader.h"
#include "../../objects/storage.h"
int LoginServerHandler(Session* session,Packet *packet){
   int data=*packet->data;
   if(data) session->login=1;
   else session->login=-1;
   erprintf(1,"LoginServerHandler %d",data);
   return 0;
}
int GameInfoResultHandler(Session* session,Packet *packet){
   int bullets_count,user_count;
   read(session->sock,&bullets_count,sizeof(int));
   read(session->sock,&user_count,sizeof(int));
   erprintf(1,"get from server info\nbullets_count %d user_count %d",bullets_count,user_count);
   for(int i=0;i<bullets_count;i++){
      read(session->sock,&GlobalEngine->storage->bullets[i].pos,sizeof(coord));
      erprintf(1,"bullet: %f %f",GlobalEngine->storage->bullets[i].pos.x,GlobalEngine->storage->bullets[i].pos.y);
   }
   for(int i=0;i<GlobalEngine->storage->users_count;i++){
      memset(&GlobalEngine->storage->users[i],0,sizeof(struct UserInfoPos));
   }
   for(int i=0;i<user_count;i++){
      read(session->sock,&GlobalEngine->storage->users[i],UserInfoPosSize);
      struct UserInfoPos *info = &GlobalEngine->storage->users[i];
      erprintf(1,"user: %f %f %d %lf %d",info->pos.x,info->pos.y,info->rotate,info->GunAngle,info->fire);
   }
   GlobalEngine->storage->users_count=user_count;
   GlobalEngine->storage->bullets_count=bullets_count;
   return 0;
}
int GetHitHandler(Session* session,Packet *packet){
   endwin();
   coord *pos=(coord*)packet->data;
   printf("get git to %f %f\n",pos->x,pos->y);
   exit(1);
   return 0;
}
int GetSpawnHandler(Session* session,Packet *packet){
   coord *pos=(coord*)packet->data;
   GlobalEngine->storage->tank.pos=*pos;
   return 0;
}
#include <stdio.h>
int SetBoomInfoHandler(Session* session,Packet *packet){
   coord *pos=(coord*)packet->data;
   ActivateAnimation(pos->x,pos->y,BoomAnimation,stdscr);
   erprintf(1,"set bomb %f %f\n",pos->x,pos->y);
   return 0;
}
