/*File "client.c" create by abstarct, (сб, 09-гру-2023 13:19:42 +0200)*/
#include "client.h"
#include "general/socket/socket.h"
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
//connect ip connect port
Client* create_client(const char *ip,int port){
   Client* client=malloc(sizeof(Client));
   client->session=create_user_session("127.0.0.1",0);
   client->stdin_flag=false;
   client->reconn=false;
   client->stdinput=fileno(stdin);
   client->maxfd=(client->stdinput>client->session->sock ? client->stdinput : client->session->sock)+1;
   client->tree=create_tree();
   connect_session(client->session,ip,port);
   return client;
}
int client_handler(Client *client){
   FD_ZERO(&client->fdset);
   if(!client->stdin_flag)
      FD_SET(client->stdinput,&client->fdset);
   FD_SET(client->session->sock, &client->fdset);

   select(client->maxfd,&client->fdset,NULL,NULL,NULL);     
   if(FD_ISSET(client->stdinput, &client->fdset))//дискриптор ввода готов на чтение
      return 1;
   if(FD_ISSET(client->session->sock, &client->fdset)){//сокет готов на чтение
      Packet packet;
      int result=session_read(client->session,&packet);
      printf("read packet %d %d\n",result,packet.type);
      if(result<0 && client->stdin_flag) return 0;
      if(result<0){printf("server terminated\n"); exit(1);}
      int (*command)(Session*,Packet*) = tree_get(client->tree,packet.type);
      if(command==0) error(1,0,"unknown packet from server");
      command(client->session,&packet);
   }
   return 0;
}
void close_client(Client *client){
   close(client->session->sock);
   FD_CLR(client->session->sock,&client->fdset);
}
void add_client_command(Client* client,int id,int (*command)(Session*,Packet*)){
   tree_add(client->tree,id,command);
}
