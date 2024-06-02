/*File "server_command.h" create by abstarct, (сб, 09-гру-2023 15:22:15 +0200)*/
#ifndef ABSTARCT_SERVER_COMMAND_H_SENTURY
#define ABSTARCT_SERVER_COMMAND_H_SENTURY

#include "server.h"
#include "../general/packets/packets.h"

int GameInfoResultHandler(Session* session,Packet *packet);
int LoginServerResultHandler(Session* session,Packet *packet);
int UpdateGameInfoFireHadler(Session* session,Packet *packet);
int UpdateGameInfoTankHadler(Session* session,Packet *packet);
#endif
