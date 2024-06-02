/*File "inet_structure.h" create by abstarct, (сб, 09-гру-2023 21:31:27 +0200)*/
#ifndef ABSTARCT_INET_STRUCTURE_H_SENTURY
#define ABSTARCT_INET_STRUCTURE_H_SENTURY
#include "../../physick/physick.h"
#include <curses.h>
#define UserInfoPosSize (sizeof(coord)+sizeof(int)+sizeof(double)+sizeof(char)+2*sizeof(bool))
struct UserInfoPos {
   coord pos;
   int rotate;
   double GunAngle;
   char id;
   bool move,fire;
   WINDOW *win;
};

#endif
