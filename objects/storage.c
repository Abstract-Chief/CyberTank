/*File "storage.c" create by abstarct, (чт, 07-гру-2023 21:07:43 +0200)*/
#include "storage.h"
#include <string.h>
#include "../Debugger/debug.h"
static OneTimeAnim AnimationList[1024];
static int CountAnimationList=0;

/*static Bullet BulletStorage[256];*/
/*static int CountBullet=0;*/
void ActivateAnimation(int x,int y,Animation* anim,WINDOW *win){
   Layer* l=anim->layers[0];
   if(win==NULL){
      AnimationList[CountAnimationList].win=newwin(l->rows,l->cols,y-l->rows/2,x-l->cols/2);
      AnimationList[CountAnimationList].dx=0;
      AnimationList[CountAnimationList].dy=0;
      AnimationList[CountAnimationList].win_b=true;
   }
   else{
      AnimationList[CountAnimationList].win=win;
      AnimationList[CountAnimationList].dx=x-l->cols/2;
      AnimationList[CountAnimationList].dy=y-l->rows/2;
      AnimationList[CountAnimationList].win_b=false;
   } 
   AnimationList[CountAnimationList].anim=malloc(sizeof(Animation));
   memcpy(AnimationList[CountAnimationList].anim,anim,sizeof(Animation));
   CountAnimationList++;
}
void DelAnimation(int index){
   CountAnimationList--;
   if(AnimationList[index].win_b){
      werase(AnimationList[index].win);
      wrefresh(AnimationList[index].win);
      delwin(AnimationList[index].win);
   }
   free(AnimationList[index].anim);
   for(int i=index;i<CountAnimationList;i++){
      OneTimeAnim *a=&AnimationList[i],*b=&AnimationList[i+1];
      a->win=b->win;
      a->anim=b->anim;
      a->dx=b->dx;
      a->dy=b->dy;
      a->win_b=b->win_b;
   }
}
void AnimationLoop(int mils){
   int arr[32];
   int n=0;
   for(int i=0;i<CountAnimationList;i++){
      OneTimeAnim *a=&AnimationList[i];
      if(a->win_b)
         werase(a->win);
      if(graphick_anim(a->win,AnimationList[i].dx,a->dy,AnimationList[i].anim,
               a->anim->speed*mils,0,0))
         DelAnimation(i--);
         /*arr[n++]=i;//оптимизировать вывод*/
      wrefresh(a->win);
   }
   //отрисовка не должна быть здесь
   for(int i=0;i<n;i++)
      DelAnimation(arr[i]);
}
/*void AddBullet(Tank *tank,coord vector){*/
   /*Bullet *bullet=&BulletStorage[CountBullet++];*/
   /*bullet->dx=vector.x;bullet->dy=vector.y;*/
   /*coord center_tank=CenterAnimation(tank->anim_h);*/
   /*bullet->x=center_tank.x+tank->x+5;*/
   /*bullet->y=center_tank.y+tank->y+5;*/
   /*erprintf(1,"create bullet with coord %f %f\ncenter tank %f %f",bullet->x,bullet->y,center_tank.x,center_tank.y);*/
   /*bullet->tank=tank;*/
/*}*/
/*void DelBullet(int index){*/
   /*CountBullet--;*/
   /*mvprintw(BulletStorage[index].y,BulletStorage[index].x,"0");*/
   /*for(int i=index;i<CountBullet;i++){*/
      /*Bullet *a=&BulletStorage[i];*/
      /*Bullet *b=&BulletStorage[i+1];*/
      /*a->x=b->x;*/
      /*a->y=b->y;*/
      /*a->dx=b->dx;*/
      /*a->dy=b->dy;*/
      /*a->tank=b->tank;*/
   /*}*/
   /*erprintf(1,"del bullet %d\n",CountBullet);*/
   /*for(int i=0;i<CountBullet;i++){*/
      /*erprintf(1,"--b: %f %f\n",BulletStorage[i].x,BulletStorage[i].y);*/
   /*}*/
/*}*/
/*#define BulletVelocityAlpha -0.0005*/
/*#define BulletVelocity 0.1*/
/*void BulletLoop(int mils){*/
   /*for(int i=0;i<CountBullet;i++){*/
      /*Bullet *bullet=&BulletStorage[i];*/
      /*mvaddch(bullet->y,bullet->x,' ');*/
      /*bullet->x+=bullet->dx*mils*BulletVelocity;*/
      /*bullet->y+=bullet->dy*mils*BulletVelocity;*/
      /*if(bullet->dx>0)*/
         /*bullet->dx+=BulletVelocityAlpha*mils;*/
      /*if(bullet->dy>0)*/
         /*bullet->dy+=BulletVelocityAlpha*mils/2;*/
      /*mvaddch(bullet->y,bullet->x,'#');*/
      /*if(bullet->dx<=0 && bullet->dy<=0)*/
         /*DelBullet(i--);*/
   /*}*/
/*}*/
