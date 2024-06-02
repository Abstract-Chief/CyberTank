/*File "client.h" create by abstarct, (сб, 09-гру-2023 13:18:26 +0200)*/
#ifndef ABSTARCT_KLIENT_H_SENTURY
#define ABSTARCT_KLIENT_H_SENTURY
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include "general/socket/socket.h"
#include "general/storage/tree.h"
typedef struct Client{
   bool stdin_flag,reconn;
   int stdinput;
   fd_set fdset;
   int maxfd;
   Session *session;
   struct TreeBlock *tree;
}Client;
Client* create_client(const char *ip,int port);
int client_handler(Client *client);
void close_client(Client *client);
void add_client_command(Client* client,int id,int (*command)(Session*,Packet*));

#endif
