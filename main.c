/*File "main.c" create by abstarct, (ср, 06-гру-2023 16:14:09 +0200)*/
#include <curses.h>
#include <stdbool.h>
#include "game_module.h"
void init(){
   initscr();
   curs_set(0);
   nocbreak();
   nodelay(stdscr,true);
   keypad(stdscr,1);
}
int close(){
   endwin();
   return 0;
}
typedef struct{
   float x,y;
   int hp;
   float reload;
} Tank;
typedef struct{
   float x,y;
   float dx,dy;
   Tank* tank;
} Bullet;

void graphick_tank(Tank* tank){

}
int game(GameEngine *engine,int mils){
   static int n=0;
   mvprintw(0,0,"%d %d\n",mils,++n);
   refresh();
   return 0;
}
int main(){
   init();
   GameEngine* engine = create_game_engine();
   add_handler(engine,game,"game");
   game_module(engine,30);
   return close();
}
