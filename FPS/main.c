/*File "main.c" create by abstarct, (сб, 25-лис-2023 10:50:05 +0200)*/
#include <ncurses.h>
#include <sys/time.h>
#include <time.h>
time_t get_utime(){

    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
int main(){
   initscr();
   time_t time_s,time_end;
   struct timespec tv={0,5000000};
   while(1){
      time_s=get_utime();
      nanosleep(&tv,NULL);
      time_end=get_utime();
      int fps=1000;
      if(time_end-time_s>0)
         fps/=(time_end-time_s);
      mvprintw(0,0,"%ld %d",time_end-time_s,fps);
      refresh();
   }

   endwin();
}
