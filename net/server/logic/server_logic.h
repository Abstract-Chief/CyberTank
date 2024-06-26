/*File "server_logic.c" create by abstarct, (сб, 09-гру-2023 16:20:52 +0200)*/
#ifndef ABSTARCT_SERVER_LOGIC_H_SENTURY
#define ABSTARCT_SERVER_LOGIC_H_SENTURY
#include "../../../physick/physick.h"
#include "../../general/socket/socket.h"
#include "collision.h"
#include <time.h>
#define MAX_PLAYER_COUNT 32
enum WorldSide{
   North=1,
   East=2,
   South=3,
   West=4
};
typedef struct{
   float x,y,dx,dy;
   float speed;
   int TankId;
}Bullet;
typedef struct{
   coord pos;
   enum WorldSide rotate;
   double GunAngle;
   bool move,fire;
   time_t SpawnTime;
   Session *session;
   char name[32];
   HitBox hitbox;
   bool was_updated;
}Player;
typedef struct{
   Player player[MAX_PLAYER_COUNT];
   Bullet bullets[MAX_PLAYER_COUNT*4];
   int count_players,count_bullet;
}ServerInfo;
bool CheckLogin(const char *name);
Player* GetPlayer(Session *session);
int add_player(Session* session,const char *name);
void AddBullet(Player* player);
int del_player(Session* session);
void ServerLogic(int mils);
void active_all_players();
extern ServerInfo GlobalServer;
#endif
