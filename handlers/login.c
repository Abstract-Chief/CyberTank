/*File "login.c" create by abstarct, (сб, 09-гру-2023 17:30:08 +0200)*/
#include "handlers.h"
#include <ctype.h>
#include <curses.h>
#include <string.h>
#include "../net/general/packets/packets.h"
#define mvprintw_c(Y,X,SIZE,STR) mvprintw(Y,X+(SIZE-strlen(STR))/2,"%s",STR)
void graphick_login(int x,int y,char *text,bool wait){
   attron(COLOR_PAIR(NUllRed));
   mvprintw(y,x,"login:");
   mvprintw_c(y+2,x+6,32,"for login");
   mvprintw_c(y+3,x+6,32,"press enter");
   if(wait)
      mvprintw_c(y+4,x+6,32,"Wait server answer");
   attroff(COLOR_PAIR(NUllRed));
   mvprintw(y,x+6,"                                ");
   mvprintw_c(y,x+6,32,text);
}
int login(GameEngine *engine, int mils){
   static bool wait=0;
   static char text[32]="";
   static int count=0;
   int input=0;
   input=getch();
   if(input==3){
      endwin();
      exit(1);
   }
   if(input==KEY_BACKSPACE || input==backspace_key){
      text[count]=0;
      count-=(count!=0);
   }else if(isalpha(input)){
      text[count++]=input;
   }else if(input==enter_key){
      Packet packet={LoginServerPacket,32,text};
      session_send(engine->client->session,&packet);
      wait=1;
   }
   graphick_login(8,4,text,wait);
   refresh();
   if(engine->client->session->login==1){
      wait=0;
      set_with_name(engine,"game");
      return 0;
   }else if(engine->client->session->login==-1){
      wait=0;
      engine->client->session->login=0;
      attron(COLOR_PAIR(NUllRed));
      mvprintw(0,0,"incorect login");
      attroff(COLOR_PAIR(NUllRed));
      refresh();
      napms(1000);
      erase();
   }
   client_handler(engine->client);
   return 0;
}
