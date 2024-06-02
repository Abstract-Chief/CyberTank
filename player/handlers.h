/*File "handlers.c" create by abstarct, (чт, 07-гру-2023 14:43:14 +0200)*/
#ifndef ABSTARCT_GHANDLERS_H_SENTURY
#define ABSTARCT_GHANDLERS_H_SENTURY
#include "../objects/storage.h"
#include "../module/game_module.h"
extern int MovingKeys[4];
extern GameEngine* GlobalEngine;
void TankHandler(Tank *tank,int input);
void move_tank(Tank *tank);
enum GameKeys{
   backspace_key=127,
   enter_key=10,
   esc_key=27,
   UpArrow=259,
   RightArrow=261,
   DownArrow=258,
   LeftArrow=260,
   UpKey=119,
   RightKey=100,
   DownKey=115,
   LeftKey=97,
   UseKeyK=107,
};
#endif
