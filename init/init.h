/*File "init.c" create by abstarct, (чт, 07-гру-2023 16:39:15 +0200)*/
#ifndef ABSTARCT_INIT_H_SENTURY
#define ABSTARCT_INIT_H_SENTURY
#include "../objects/storage.h"
enum BaseColorPair {
   RedWhite=230,
   NUllRed,
   YellowBlue,
   Yellow,
   Red,
   Blue,
};
void init_tank(Tank *tank,int x,int y,int hp,int reload,const char *filename_v,const char *filename_h,float speed_anim);
void init_storage(StorageGame *storage);
void init_graphick_obj();
void init();
int close();



#endif
