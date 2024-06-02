/*File "packet.h" create by abstarct, (пт, 08-гру-2023 21:57:19 +0200)*/
#ifndef ABSTARCT_PACKET_H_SENTURY
#define ABSTARCT_PACKET_H_SENTURY

typedef struct{
   unsigned char type;
   unsigned short size;
   char *data;
}Packet;
Packet create_packet(unsigned char type,unsigned char size,char *data);

#endif
