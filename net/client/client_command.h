/*File "client_command.c" create by abstarct, (сб, 09-гру-2023 18:11:44 +0200)*/
#ifndef ABSTARCT_CLIENT_COMMAND_H_SENTURY
#define ABSTARCT_CLIENT_COMMAND_H_SENTURY
#include "client.h"
int LoginServerHandler(Session* session,Packet *packet);
int GameInfoResultHandler(Session* session,Packet *packet);
int GetHitHandler(Session* session,Packet *packet);
int GetSpawnHandler(Session* session,Packet *packet);

#endif
