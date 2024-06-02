/*File "collision.h" create by abstarct, (нд, 10-гру-2023 01:43:03 +0200)*/
#ifndef ABSTARCT_COLLISION_H_SENTURY
#define ABSTARCT_COLLISION_H_SENTURY

#include "../../../physick/physick.h"
#include <stdbool.h>

typedef struct {
   coord size;
   bool center;
} HitBox;

HitBox create_hitbox(coord size,bool center);
bool check_collision(HitBox* h,coord pos,coord check);

#endif
