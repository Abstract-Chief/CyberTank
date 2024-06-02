/*File "tree.c" create by abstarct, (сб, 09-гру-2023 11:36:25 +0200)*/
#include "../socket/socket.h"
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
struct TreeBlock{
   int id;
   int (*handler)(Session*,Packet*);
   struct TreeBlock *l,*r;
};
struct TreeBlock** find_block(struct TreeBlock **ptr,int id){
   if(*ptr==0) return ptr;
   char flag=id>(*ptr)->id;
   struct TreeBlock** ptr_c;
   if(flag<0) ptr_c=&(*ptr)->l;
   else if(flag==0) return ptr;
   else ptr_c=&(*ptr)->r;
   return find_block(ptr_c,id);
}
struct TreeBlock *tree_add(struct TreeBlock* tree,int id,int (*handler)(Session*,Packet*)){
   struct TreeBlock **result=find_block(&tree, id);
   *result=malloc(sizeof(struct TreeBlock));
   (*result)->id=id;
   (*result)->handler=handler;
   (*result)->l=0;
   (*result)->r=0;
   return *result;
}
struct TreeBlock* create_tree(){
   return tree_add(0,0,0);
}
int (*tree_get(struct TreeBlock *tree,int id))(Session*,Packet*) {
   struct TreeBlock *block=*find_block(&tree,id);
   if(block==NULL) return 0;
   return block->handler;
}
