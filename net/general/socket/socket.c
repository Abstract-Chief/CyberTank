/*File "socket.c" create by abstarct, (пт, 08-гру-2023 21:59:38 +0200)*/
#include "socket.h"
#include <error.h>
#include <stdlib.h>
#include <errno.h>
struct sockaddr_in GetServAddr(const char *ip,int port){
   struct sockaddr_in server_addr;
   server_addr.sin_family=AF_INET;
   server_addr.sin_port=htons(port);
   server_addr.sin_addr.s_addr=inet_addr(ip);
   if(server_addr.sin_addr.s_addr<0)
      error(1,0,"get server addr error");
   return server_addr;
}
int create_socket(const char *ip,int port){
   int sock=socket(AF_INET,SOCK_STREAM,0);
   if(sock<0){
      error(1,0,"create socket");
   }
   struct sockaddr_in socket_addr;
   socket_addr.sin_family=AF_INET;
   socket_addr.sin_port=htons(port);
   if(ip!=NULL) socket_addr.sin_addr.s_addr=inet_addr(ip);
   else socket_addr.sin_addr.s_addr=htons(INADDR_ANY);
   if(bind(sock,(struct sockaddr*)&socket_addr,sizeof(socket_addr))<0)
      error(1,0,"bind socket");
   return sock;
}
Session* create_user_session(const char *ip,int port){
   Session* session = malloc(sizeof(Session));
   session->sock=create_socket(ip,port);
   session->conect=false;
   session->login=0;
   session->id=-1;
   session->port=-1;session->ip=-1;
   return session;
}
Session* create_server_session(int sock_,struct sockaddr_in *addr_,short id){
   char buf[16];
   Session* session = malloc(sizeof(Session));
   session->sock=sock_;
   session->conect=1;
   session->login=0;
   session->ip=addr_->sin_addr.s_addr;
   inet_ntop(AF_INET, &addr_->sin_addr, buf, 1024);
   session->port=ntohs(addr_->sin_port);
   return session;
}
bool connect_session(Session* session,const char* ip,int port){
   struct sockaddr_in server_addr=GetServAddr(ip,port);
   socklen_t size=(socklen_t)sizeof(server_addr);
   if(connect(session->sock,(struct sockaddr *)&server_addr,size)<0){
      if(errno==ECONNREFUSED) error(1,0,"connect error: server off");
      error(1,0,"connect error: unknown");
   }
   return session->conect=true;
}
bool connect_session_addr(Session* session,struct sockaddr *addr){
   socklen_t size=(socklen_t)sizeof(struct sockaddr_in);
   if(connect(session->sock,addr,size)<0){
      if(errno==ECONNREFUSED) error(1,0,"connect error: server off");
      error(1,0,"connect error: unknown");
   }
   return session->conect=true;
}
void close_session(Session* session){
   close(session->sock);
   free(session);
}
struct sockaddr_in get_addr_session(int sock){
   struct sockaddr_in addr;
   socklen_t len=(socklen_t)sizeof(struct sockaddr_in);
   if (getpeername(sock, (struct sockaddr*)&addr,&len) == -1)
      error(1,0,"error get peer sock");
   return addr;
}
struct sockaddr_in get_addr_sock(int sock){
   struct sockaddr_in addr;
   socklen_t len=(socklen_t)sizeof(struct sockaddr_in);
   if (getsockname(sock, (struct sockaddr*)&addr,&len) == -1)
      error(1,0,"error get name sock");
   return addr;
}
int getip_sock(int sock,char ip[16]){//return port
   struct sockaddr_in addr=get_addr_sock(sock);
   inet_ntop(AF_INET, &(addr.sin_addr), ip, INET_ADDRSTRLEN);
   return htons(addr.sin_port);
}
int getip_session(Session* session,char ip[16]){
   struct sockaddr_in addr=get_addr_session(session->sock);
   inet_ntop(AF_INET, &(addr.sin_addr), ip, INET_ADDRSTRLEN);
   session->ip=addr.sin_addr.s_addr;
   return session->port=htons(addr.sin_port);
}
int session_send(Session* session,Packet *packet){
   if(session->conect==0) return -1;
   if(write(session->sock,&packet->type,sizeof(packet->type))<0)
      error(1,0,"send error(type)\n");
   if(write(session->sock,&packet->size,sizeof(packet->size))<0)
      error(1,0,"send error(size)\n");
   if(packet->size==0) return 0;
   if(write(session->sock,packet->data,packet->size)<0) 
      error(1,0,"send error(packet->data)\n");
   return 0;
}
int session_read(Session* session,Packet *packet){
   int result=read(session->sock,&packet->type,sizeof(packet->type));
   if(result<=0)
      return -1;
   result=read(session->sock,&packet->size,sizeof(packet->size));
   if(result<=0)
      return -2;
   if(packet->size==0){
      packet->data=0;
      return 0;
   }
   packet->data=malloc(sizeof(char)*packet->size);
   result=read(session->sock,packet->data,packet->size);
   if(result<=0)
      return -3;
   return packet->size;
}
