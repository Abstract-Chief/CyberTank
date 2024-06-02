/*File "game.h" create by abstarct, (нд, 03-гру-2023 15:49:53 +0200)*/
#ifndef ABSTARCT_GAME_H_SENTURY
#define ABSTARCT_GAME_H_SENTURY

int handler(int input);
#define GameEngineMaxCount 64
struct GameEngine{
   int count,actual_n;
   int (*actual)(int);
   int (*handlers[GameEngineMaxCount])(int);
   const char *names[GameEngineMaxCount];
};

int add_handler(GameEngine *engine,int (*handler)(int),const char *name);
int use_handler(GameEngine *engine);
int set_actual(GameEngine *engine,int n);
int set_with_name(GameEngine *engine,const char *name);

#endif
