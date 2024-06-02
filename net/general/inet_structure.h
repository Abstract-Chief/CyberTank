/*File "inet_structure.h" create by abstarct, (сб, 09-гру-2023 21:31:27 +0200)*/
#ifndef ABSTARCT_INET_STRUCTURE_H_SENTURY
#define ABSTARCT_INET_STRUCTURE_H_SENTURY
#include "../../physick/physick.h"
#include <curses.h>
struct UserInfoPos {
   coord pos;
   int rotate;
   double GunAngle;
   char id;
   bool move,fire;
};
#define UserInfoPosSize (sizeof(struct UserInfoPos))

#endif
