/*File "tree.h" create by abstarct, (сб, 09-гру-2023 11:36:25 +0200)*/
#ifndef ABSTARCT_TREE_H_SENTURY
#define ABSTARCT_TREE_H_SENTURY

#include "../socket/socket.h"
struct TreeBlock{
   int id;
   int (*handler)(Session*,Packet*);
   struct TreeBlock *l,*r;
};
struct TreeBlock *tree_add(struct TreeBlock* tree,int id,int (*handler)(Session*,Packet*));
struct TreeBlock* create_tree();
void delete_tree(struct TreeBlock* tree);
int (*tree_get(struct TreeBlock *tree,int id))(Session*,Packet*);
#endif
