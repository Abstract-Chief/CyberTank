/*File "main.c" create by abstarct, (ср, 06-гру-2023 16:14:09 +0200)*/
#include "game.h"
#include "Debugger/debug.h"
int main(){
   init();
   InitDebugerOutput(1,"Errors");
   init_graphick_obj();
   GameEngine* engine = create_game_engine();
   init_storage(engine->storage);
   add_handler(engine,game,"game");
   game_module(engine,30);
   return close();
}
