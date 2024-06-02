/*File "main.c" create by abstarct, (сб, 25-лис-2023 10:50:05 +0200)*/
#include <ncurses.h>
#include <sys/time.h>
#include <time.h>
time_t get_utime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
void game(float time){
   static float ball_v=0;
   static float ball_pose=0;
   mvprintw(1,0,"%f %f\n",ball_v,ball_pose);
   ball_pose+=ball_v*time+0.098*time*time/2;
   ball_v+=0.098*time;
   mvprintw(ball_pose,5,"$$$");
   mvprintw(ball_pose+1,5,"$$$");
   mvprintw(ball_pose+2,5,"$$$");
}
int main(){
   initscr();
   time_t time_s,time=1;
   time_t time_s_over;
   struct timespec sleep={0,0};
   int FPS_LIMIT=5;
   while(1){
      time_s_over=time_s=get_utime();
      game((float)time/100);
      refresh();
      sleep.tv_nsec=1000000*(1000/FPS_LIMIT)-time;
      nanosleep(&sleep,NULL);
      time=get_utime()-time_s;
      time=(time ? time : 1);
      int fps=1000;
      if(time>0)
         fps/=(time);
      mvprintw(0,0,"%ld %d\n",time,fps);
      /*nanosleep()*/
   }

   endwin();
}
