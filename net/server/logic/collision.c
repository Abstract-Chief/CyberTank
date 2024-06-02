/*File "collision.c" create by abstarct, (нд, 10-гру-2023 14:36:39 +0200)*/
#include "collision.h"
HitBox create_hitbox( coord size, bool center){
   HitBox r={size,center};
   return r;
}
bool check_collision(HitBox* h,coord pos,coord check){
   if(!h->center){
      if(pos.x<=check.x && pos.x+h->size.x>=check.x && pos.y<=check.y && pos.y+h->size.y>=check.y)
         return true;
   }
   else{
      float sx=h->size.x/2,sy=h->size.y/2;
      if(pos.x-sx<=check.x && pos.x+sx>=check.x
            && pos.y-sy<=check.y && pos.y+sy>=check.y)
         return true;
   }
   return false;
}


