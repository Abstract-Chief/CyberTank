/*File "fps_module.h" create by abstarct, (ср, 06-гру-2023 16:18:41 +0200)*/
#ifndef ABSTARCT_FPS_MODULE_H_SENTURY
#define ABSTARCT_FPS_MODULE_H_SENTURY
#include <time.h>

//GAME STRUCT MODULE
#define GameEngineMaxCount 64
#define GameEngineNameSize 32
typedef struct GameEngine{
   int count,actual_n;
   int (*actual)(struct GameEngine*,int);
   int (*handlers[GameEngineMaxCount])(struct GameEngine *,int);
   char names[GameEngineMaxCount][GameEngineNameSize];
} GameEngine;

GameEngine* create_game_engine();
int add_handler(GameEngine *engine,int (*handler)(GameEngine*,int),const char *name);
int use_handler(GameEngine *engine,int input);
int set_actual(GameEngine *engine,int n);
int set_with_name(GameEngine *engine,const char *name);

//FPS MODULE
time_t get_utime();
void game_module(GameEngine *engine,int fps_limit);

#endif
