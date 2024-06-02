/*File "packet.c" create by abstarct, (пт, 08-гру-2023 21:57:38 +0200)*/
#include "packet.h"
Packet create_packet(unsigned char type,unsigned char size,char *data){
   Packet result={type,size,data};
   return result;
}
