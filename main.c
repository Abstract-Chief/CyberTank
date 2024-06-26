/*File "main.c" create by abstarct, (ср, 06-гру-2023 16:14:09 +0200)*/
#include "handlers/handlers.h"
#include "Debugger/debug.h"
#include "net/general/packets/packets.h"
#include "net/client/client_command.h"
extern GameEngine* GlobalEngine;
int main(int argc,char **argv){
   if(argc<2){ 
      printf("none ip\n");
      return 1;
   }
   init();
   InitDebugerOutput(1,"Errors");
   init_graphick_obj();
   timeout(0);
   raw();
   Client *client=create_client(argv[1],1223);
   add_client_command(client,GetSpawnPacket,GetSpawnHandler);
   add_client_command(client,GetHitPacket,GetHitHandler);
   add_client_command(client,GameInfoResultPacket,GameInfoResultHandler);
   add_client_command(client,LoginServerResultPacket,LoginServerHandler);
   add_client_command(client,SetBoomInfo,SetBoomInfoHandler);
   GlobalEngine = create_game_engine();
   GlobalEngine->client=client;
   init_storage(GlobalEngine->storage);
   add_handler(GlobalEngine,menu,"menu");
   add_handler(GlobalEngine,login,"login");
   add_handler(GlobalEngine,game,"game");
   set_with_name(GlobalEngine,"menu");
   game_module(client,GlobalEngine,30);
}
