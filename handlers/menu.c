/*File "menu.c" create by abstarct, (сб, 09-гру-2023 16:58:19 +0200)*/
#include <string.h>
#include "handlers.h"
#include "../Debugger/debug.h"
#define mvprintw_c(Y,X,SIZE,STR) mvprintw(Y,X+(SIZE-strlen(STR))/2,"%s",STR)
#define CountMenuItems 4
const char* MenuItems[CountMenuItems+1]={"login","settings","autors","exit"};
void graphick_menu(int x,int y,int cur){
   for(int i=0;i<CountMenuItems;i++){
      if(cur==i)
         attron(COLOR_PAIR(RedWhite));
      mvprintw_c(y+i*2,x,10,MenuItems[i]);
      if(cur==i)
         attroff(COLOR_PAIR(RedWhite));
   }
}
int menu(GameEngine *engine,int mils){
   static int cur=0;
   int input=0,buf=0;
   while(buf!=-1){
      input=buf;
      buf=getch();
   }
   if(input==MovingKeys[0]) cur-=(cur!=0);
   if(input==MovingKeys[2]) cur+=(cur!=3);
   if(input==UseKeyK){
      if(cur==3){
         endwin();
         exit(0);
      }
      erprintf(1,"try open menu %s",MenuItems[cur]);
      set_with_name(engine,MenuItems[cur]);
      return 0;
   }
   graphick_menu(8,4,cur);
   refresh();
   return 0;
}
