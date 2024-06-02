/*File "main.c" create by abstarct, (ср, 06-гру-2023 16:14:09 +0200)*/
#include "handlers/handlers.h"
#include "Debugger/debug.h"
#include "net/general/packets/packets.h"
#include "net/client/client_command.h"
extern GameEngine* GlobalEngine;
int main(){
   init();
   InitDebugerOutput(1,"Errors");
   init_graphick_obj();
   raw();
   Client *client=create_client("127.0.0.1",1223);
   add_client_command(client,GameInfoResultPacket,GameInfoResultHandler);
   add_client_command(client,LoginServerResultPacket,LoginServerHandler);
   GlobalEngine = create_game_engine();
   GlobalEngine->client=client;
   init_storage(GlobalEngine->storage);
   add_handler(GlobalEngine,menu,"menu");
   add_handler(GlobalEngine,login,"login");
   add_handler(GlobalEngine,game,"game");
   set_with_name(GlobalEngine,"login");
   game_module(client,GlobalEngine,30);
   /*return close();*/
}
