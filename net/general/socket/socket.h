/*File "socket.c" create by abstarct, (пт, 08-гру-2023 21:48:09 +0200)*/
#ifndef ABSTARCT_SOCKET_H_SENTURY
#define ABSTARCT_SOCKET_H_SENTURY
//base libs
#include <stdbool.h>
//net libs
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
//my libs
#include "packet.h"

struct sockaddr_in GetServAddr(const char *ip,int port);
//Socket
int create_socket(const char *ip,int port);
//Session
typedef struct {
   short id;
   int sock;
   int ip,port;
   bool conect;
   int login;
   struct sockaddr addr;
}Session;

Session* create_user_session(const char *ip,int port);//in user 
Session* create_server_session(int sock_,struct sockaddr_in *addr_,short id);//in server 
                                                                             //
bool connect_session(Session* session,const char* ip,int port);
bool connect_session_addr(Session* session,struct sockaddr *addr);

void close_session(Session* session);

int getip_sock(int sock,char ip[16]);
int getip_session(Session* session,char ip[16]);

int session_send(Session* session,Packet *packet);
int session_read(Session* session,Packet *packet);

#endif
