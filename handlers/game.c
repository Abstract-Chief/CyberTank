/*File "game.c" create by abstarct, (чт, 07-гру-2023 16:50:05 +0200)*/
#include "handlers.h"
#include "../net/client/client.h"
#include "../net/general/packets/packets.h"
#include "../graphick/map.h"
int game(GameEngine *engine,int mils){
   int input=0,buf=0;
   while(buf!=-1){
      input=buf;
      buf=getch();
      if(buf==3){
         endwin();
         exit(1);
      }
   }
   Tank* tank=&engine->storage->tank;
   TankHandler(tank,input);
   move_tank(tank);
   werase(engine->storage->general_win);
   box(engine->storage->general_win,0,0);
   graphick_world(engine,mils);
   AnimationLoop(mils);
   wrefresh(engine->storage->general_win);
   refresh();
   Packet p={GetGameInfoPacket,0,0};
   session_send(engine->client->session,&p);
   client_handler(engine->client);
   return 0;
}
