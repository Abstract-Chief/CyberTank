/*File "main.c" create by abstarct, (нд, 03-гру-2023 17:29:42 +0200)*/
#include "game.h"
#include <ncurses.h>
#include <stdlib.h>

int Handler1(GameEngine *engine,int input){
   if(input==258){
      if(set_with_name(engine, "h2")) exit(1);
   }
   mvprintw(0,0, "Handler1 %d  ",input);
   return 0;
}
int Handler2(GameEngine *engine,int input){
   if(input==258){
      if(set_with_name(engine, "h1")) exit(1);
   }
   mvprintw(0,0, "Handler2 %d  ",input);
   return 0;
}

int main(){
   GameEngine *engine=create_game_engine();
   add_handler(engine,Handler1,"h1");
   add_handler(engine,Handler2,"h2");
   initscr();
   cbreak();
   keypad(stdscr,1);
   while(1){
      use_handler(engine,getch());
      refresh();
      clear();
      napms(1000);
   }
   endwin();
}
