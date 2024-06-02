/*File "client_command.c" create by abstarct, (сб, 09-гру-2023 18:11:44 +0200)*/
#include "client_command.h"
#include "../../Debugger/debug.h"
int LoginServerHandler(Session* session,Packet *packet){
   int data=*packet->data;
   if(data) session->login=1;
   else session->login=-1;
   erprintf(1,"LoginServerHandler %d",data);
   return 0;
}
