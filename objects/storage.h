/*File "storage.c" create by abstarct, (чт, 07-гру-2023 10:45:47 +0200)*/
#ifndef ABSTARCT_STORAGE_H_SENTURY
#define ABSTARCT_STORAGE_H_SENTURY
#include "../graphick/reader.h"
#include "../physick/physick.h"
extern Animation* BoomAnimation;
extern Animation* TankAnimationV;
extern Animation* TankAnimationH;
enum WorldSide{
   North=1,
   East=2,
   South=3,
   West=4
};
typedef struct{
   coord pos;
   float dx,dy;
   int angle;
   int hp;
   float reload;
   Animation *anim_v,*anim_h;
   enum WorldSide rotate;
   WINDOW *win;
   bool fire;
} Tank;
typedef struct{
   float x,y;
   float dx,dy;
   Tank* tank;
} Bullet;
typedef struct StorageGame{
   Tank tank;
   Bullet bullets[16];
} StorageGame;
typedef struct{
   WINDOW *win;
   bool win_b;
   Animation *anim;
   int dx,dy;
} OneTimeAnim;

//void AddBullet(Tank *tank,coord vector);
//void BulletLoop(int mils);
void ActivateAnimation(int x,int y,Animation* anim,WINDOW *win);
void DelAnimation(int index);
void AnimationLoop(int mils);
#endif
