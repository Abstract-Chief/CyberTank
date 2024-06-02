/*File "game.c" create by abstarct, (чт, 07-гру-2023 16:50:05 +0200)*/
#include "handlers.h"
#include "../net/client/client.h"
#include "../net/general/packets/packets.h"
int game(GameEngine *engine,int mils){
   int input=0,buf=0;
   while(buf!=-1){
      input=buf;
      buf=getch();
   }
   Tank* tank=&engine->storage->tank;
   TankHandler(tank,input);
   move_tank(tank);
   graphick_tank(tank,mils);
   /*BulletLoop(mils);*/
   AnimationLoop(mils);
   refresh();
   werase(tank->win);
   Packet p={GetGameInfoPacket,0,0};
   session_send(engine->client->session,&p);
   client_handler(engine->client);

   return 0;
}
