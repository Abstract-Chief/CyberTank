/*File "fps_module.c" create by abstarct, (ср, 06-гру-2023 16:18:41 +0200)*/
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "game_module.h"
#include <stdlib.h>
#include "../net/client/client.h"
#include "../net/general/packets/packets.h"
#include "../Debugger/debug.h"
time_t get_utime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
void game_module(Client *client,GameEngine *engine,int fps_limit){
   time_t time_s,time=1;
   struct timespec sleep={0,0};
   int FPS_LIMIT=fps_limit;
   while(1){
      time_s=get_utime();
      engine->actual(engine,time);
      sleep.tv_nsec=1000000*(1000/FPS_LIMIT)-time;
      nanosleep(&sleep,NULL);
      time=get_utime()-time_s;
      time=(time ? time : 1);
      int fps=1000;
      if(time>0)
         fps/=(time);
   }

}
int add_handler(GameEngine *engine,int (*handler)(GameEngine*,int),const char *name){
   if(handler==NULL) return -1;
   engine->handlers[engine->count]=handler;
   memcpy(engine->names[engine->count],name,GameEngineNameSize);
   if(engine->actual_n==-1)
      set_actual(engine, engine->count);
   erprintf(1,"add handler %d",handler);
   return engine->count++;
}
int use_handler(GameEngine *engine,int input){
   return engine->actual(engine,input);
}
int set_actual(GameEngine *engine,int n){
   if(engine->handlers[n]==0) return 1;
   engine->actual_n=n;
   engine->actual=engine->handlers[n];
   clear();
   erprintf(1,"set_actualhandler %d",engine->actual);
   return 0;
}
int set_with_name(GameEngine *engine,const char *name){
   for(int i=0;i<engine->count;i++){
      if(!strcmp(name,engine->names[i])){
         return set_actual(engine,i);
      }
   }
   return 1;
}
GameEngine* create_game_engine(){
   GameEngine *engine=malloc(sizeof(GameEngine));
   engine->count=0;
   engine->actual_n=-1;
   engine->actual=NULL;
   memset(engine->handlers,0,GameEngineMaxCount*sizeof(char*));
   engine->storage=malloc(sizeof(StorageGame));
   return engine;
}
