/*File "debug.c" create by abstarct, (нд, 03-гру-2023 15:59:18 +0200)*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
static char DebugFileNames[255][32]={};

int InitDebugerOutput(int n,const char *name){
   if(name==NULL) return -1;
   if(n+1>255) return 1;
   if(DebugFileNames[n][0]!=0) return 2;

   memcpy(DebugFileNames[n],name,32);
   FILE *file = fopen(DebugFileNames[n],"w");

   time_t rawtime;
   struct tm *timeinfo;
   char buffer[80];
   time(&rawtime);
   timeinfo = localtime(&rawtime);
   strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

   fprintf(file,"Debug %s : %s\n",name,buffer);
   fclose(file);
   return 0;
}
int erprintf(int you_fd,const char *format,...){
   va_list args;
   va_start(args,format);
   if(DebugFileNames[you_fd][0]==0) return -1;
   FILE *file = fopen(DebugFileNames[you_fd],"a+");
   if(file==NULL) return -2;
   char buffer[1024];
   vsnprintf(buffer,sizeof(buffer),format,args);
   int result=fprintf(file,"%s\n",buffer);
   fclose(file);
   return result;
}
