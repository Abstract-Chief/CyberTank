/*File "server.c" create by abstarct, (сб, 09-гру-2023 11:29:23 +0200)*/
#ifndef ABSTARCT_SERVER_H_SENTURY
#define ABSTARCT_SERVER_H_SENTURY
#include "../../general/socket/socket.h"
#include "../../general/storage/tree.h"
#include "../logic/server_logic.h"
#include <stdlib.h>
typedef struct Server{
   int stdinput;bool stdflag;
   int sock;
   int count,maxfd,countfd;
   int clientfd[FD_SETSIZE];
   fd_set fdset_ret,fdset;
   Session *clientses[FD_SETSIZE];
   int (*ConnectHandler)(Session* session);
   int (*CloseConnectionHandler)(struct Server* server,Session* session);
   struct TreeBlock* tree;
} Server;
Server* create_server(const char *ip,int port,int (*ConnectHandler)(Session*),int (*CloseConnectionHandler)(struct Server*,Session*));
int close_server(Server *server);
Session* Listen(Server* server);
void add_command_server(Server* server,int id,int (*command)(Session*,Packet*));
int server_handler(Server* server,Session *session,Packet *packet);
void KlientError(Server* server,Session *session,int error);


#endif
