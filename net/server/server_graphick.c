/*File "server_graphick.c" create by abstarct, (сб, 09-гру-2023 22:05:08 +0200)*/
#include <curses.h>
#include "server_graphick.h"
#include "server_logic.h"
enum BaseColorPair {
   RedWhite=230,
   NUllRed,
   YellowBlue,
   Yellow,
   Red,
   Blue,
};
void init_graphick(){
   initscr();
   start_color();
   use_default_colors();
   init_pair(RedWhite,COLOR_WHITE,COLOR_RED);
   init_pair(NUllRed,COLOR_RED,-1);
   init_pair(YellowBlue,COLOR_BLUE,COLOR_YELLOW);
   init_pair(Yellow,COLOR_YELLOW,COLOR_YELLOW);
   init_pair(Red,COLOR_RED,COLOR_RED);
   init_pair(Blue,COLOR_BLUE,COLOR_BLUE);
}
const char *WorldSideText[4]={"North","East","South","West"};
void graphick_server_info(int mils,Server *s,int x,int y){
   erase();
   mvprintw(y,x,"ServerInfo: (players count) (bullets count) (session count) (time)");
   attron(COLOR_PAIR(NUllRed));
   mvprintw(y+1,x,"                  %d             %d                  %d      %d",
         GlobalServer.count_players,GlobalServer.count_bullet,s->count,mils);
   attroff(COLOR_PAIR(NUllRed));
   mvprintw(y+2,x,"PlayerInfo");
   for(int i=0;i<GlobalServer.count_players;i++){
      Player* pl=&GlobalServer.player[i];
      if(pl->rotate==0) pl->rotate=North;
      mvprintw(y+3+i,x,"name ");
      attron(COLOR_PAIR(NUllRed));
      printw("%s ",pl->name);
      attroff(COLOR_PAIR(NUllRed));
      addstr("x: ");
      attron(COLOR_PAIR(NUllRed));
      printw("%d ",(int)pl->pos.x);
      attroff(COLOR_PAIR(NUllRed));
      addstr("y: ");
      attron(COLOR_PAIR(NUllRed));
      printw("%d ",(int)pl->pos.y);
      attroff(COLOR_PAIR(NUllRed));
      addstr("direction: ");
      attron(COLOR_PAIR(NUllRed));
      printw("%s ",WorldSideText[pl->rotate-1]);
      attroff(COLOR_PAIR(NUllRed));
      addstr("angle: ");
      attron(COLOR_PAIR(NUllRed));
      printw("%f",pl->GunAngle);
      attroff(COLOR_PAIR(NUllRed));
   }
   y+=4+GlobalServer.count_players;
   mvprintw(y,x,"BulletInfo");
   for(int i=0;i<GlobalServer.count_bullet;i++){
      Bullet* b=&GlobalServer.bullets[i];
      mvprintw(y+i,x,"%d : x %f y %f dx %f dy %f from %d",i+1,b->x,b->y,b->dx,b->dy,b->TankId);
   }
   refresh();
}
