/*File "server.c" create by abstarct, (сб, 09-гру-2023 12:14:59 +0200)*/
#include "server.h"
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdio.h>
#define SERVER_QUEQE 10
ServerInfo GlobalServer;
void KlientError(Server* server,Session *session,int error){
   /*Packet p={4,0};*/
   /*session_send(session,&p);*/
}
Server* create_server(const char *ip,int port,int (*ConnectHandler)(Session*),int (*CloseConnectionHandler)(struct Server*,Session*)){
   Server *s=malloc(sizeof(Server));
   s->sock=create_socket(ip,port);
   s->ConnectHandler=ConnectHandler;
   s->CloseConnectionHandler=CloseConnectionHandler;
   s->tree=create_tree();
   if(listen(s->sock,SERVER_QUEQE)==-1) error(1,0,"error start listen");
   memset(s->clientfd,-1,FD_SETSIZE*sizeof(int));
   s->stdinput=fileno((stdin));
   FD_ZERO(&s->fdset);
   FD_SET(s->sock, &s->fdset);
   FD_SET(s->stdinput, &s->fdset);
   s->maxfd=((int)s->sock>s->stdinput ? (int)s->sock : s->stdinput);
   s->stdflag=false;
   return s;
}
int close_server(Server *server){
   for(int i=0;i<=server->countfd;i++){
      if(server->clientfd[i]==-1) continue;
      close(server->clientfd[i]);
      free(server->clientses[i]);
      //FD_CLR(clientfd[i],&fdset);
      printf("succeful close connection %d\n",server->clientfd[i]);
      server->clientfd[i]=-1;
   }
   printf("close all connection\n");
   FD_CLR(server->sock, &server->fdset);
   close(server->sock);
   printf("close Listen socket\n");
   return 0;
}
Session* Listen(Server* server){
   struct sockaddr_in addr;
   int len=sizeof(addr);
loop:;
   int s=accept(server->sock,(struct sockaddr*)&addr,(socklen_t*)&len);
   if(s<0){
      //если что либо прервало системный вызов то мы повторяем слушанье
      //тут рекурсия
      /*if(errno==EINTR) Listen();*/
      if(errno==EINTR) goto loop; //а тут прыжок
      else error(1,0,"error accept in Listen");
   }
   return create_server_session(s,&addr,0);
}
void add_command_server(Server* server,int id,int (*command)(Session*,Packet*)){
   tree_add(server->tree,id,command);
}
int server_handler(Server* server,Session *session,Packet *packet){
   int (*handle_function)(Session*,Packet*) = tree_get(server->tree,packet->type);
   if(handle_function==0) return -1;
   return handle_function(session,packet);
}
