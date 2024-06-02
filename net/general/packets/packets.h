/*File "packets.h" create by abstarct, (сб, 09-гру-2023 15:00:57 +0200)*/
#ifndef ABSTARCT_PACKETS_H_SENTURY
#define ABSTARCT_PACKETS_H_SENTURY
#include "../socket/packet.h"
extern Packet GetGameInfoDataP;
enum ClientPacketsType{
   GetSpawnPacket=2,
   GetHitPacket,
   GameInfoResultPacket,
   LoginServerPacket,
   LoginServerResultPacket,
   ConnectGamePacket,
   GetGameInfoPacket,
   UpdateGameInfoFirePacket,
   UpdateGameInfoTankPacket,
   SetBoomInfo,
};

#endif
