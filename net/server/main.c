/*File "server.c" create by abstarct, (пт, 08-гру-2023 23:25:47 +0200)*/
#include "../general/socket/socket.h"
#include "server_graphick.h"
#include "server_command.h"
#include "server.h"
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <ncurses.h>
#include <sys/time.h>
#define USEC_TIMEOUT_SERVER 10000
time_t get_utime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
int ConnectHandler(Session *session){
   /*printf("succeful get connection handler %d\n",session->sock);*/
   return 0;
}
int CloseConnectionHandler(Server *server,Session *session){
   /*printf("succeful close connection %d\n",session->sock);*/
   return 0;
}
void init_server_command(Server *server){
   add_command_server(server,LoginServerPacket,LoginServerResultHandler);
   add_command_server(server,GetGameInfoPacket,GameInfoResultHandler);
   add_command_server(server,UpdateGameInfoFirePacket,UpdateGameInfoFireHadler);
   add_command_server(server,UpdateGameInfoTankPacket,UpdateGameInfoTankHadler);
}
int main(int argc,char **argv){
   init_graphick();
   nodelay(stdscr,1);
   keypad(stdscr,1);
   /*nocbreak();*/
   Server *s=create_server("127.0.0.1",1223,ConnectHandler,CloseConnectionHandler);
   GlobalServer.count_bullet=0;
   GlobalServer.count_players=0;
   init_server_command(s);
   time_t start_t=get_utime();
   //Server Work
   for(int i=0;1;i++){
      /*int input=getch();*/
      int mils=get_utime()-start_t;
      ServerLogic(mils);
      start_t=get_utime();
      graphick_server_info(mils,s,5,10);
      struct timeval timeout={0,USEC_TIMEOUT_SERVER};
      s->fdset_ret=s->fdset;
      int nready=select(s->maxfd+2,&s->fdset_ret,NULL,NULL,&timeout);
      if(nready==-1){
         if(errno==EINTR) continue;;
      }
      if(FD_ISSET(s->sock, &s->fdset_ret)){
         Session *session=Listen(s);
         int i,socket=session->sock;
         for(i=0;i<FD_SETSIZE;i++){
            if(s->clientfd[i]==-1){
               s->clientfd[i]=socket;
               s->clientses[i]=session;
               s->count++;
               session->id=i;
               break;
            }
         }
         if(i==FD_SETSIZE) error(1,0,"to many children\n");
         FD_SET(socket,&s->fdset);
         if(s->maxfd<socket) s->maxfd=socket;
         if(i>s->countfd) s->countfd=i;
         if(s->ConnectHandler(session)==1){
            s->CloseConnectionHandler(s,session);
         }
         if(--nready<=0) continue;;
      }     
      for(int i=0;i<=s->countfd;i++,nready--){
         if(FD_ISSET(s->clientfd[i], &s->fdset_ret)){
            Packet packet;
            int r=session_read(s->clientses[i],&packet);
            /*printf("--read packet %d\n",r);*/
            int result=1;
            if(r>=0)
               result=server_handler(s,s->clientses[i],&packet);//handler function must free memory if want this
            if(!result) continue;
            mvprintw(0,0,"Unknown command from %d %d\n",s->clientses[i]->id,packet.type);
            KlientError(s,s->clientses[i],1);//error UnknownPacket
            if(s->clientfd[i]!=-1){
               del_player(s->clientses[i]);
               s->CloseConnectionHandler(s,s->clientses[i]);
               close(s->clientfd[i]);
               free(s->clientses[i]);
               s->clientfd[i]=-1;
            }
         }
      }
   
   }
   close(s->sock);
   endwin();
   return 0;
}
