/*File "storage.c" create by abstarct, (пн, 04-гру-2023 18:28:49 +0200)*/
#include "storage.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
int in_area(StorageObject *area,StorageObject *obj){
   if(obj->x<area->x || obj->y<area->y) return false;
   if(obj->x+obj->w>area->x+area->w) return false;
   if(obj->y+obj->h>area->y+area->h) return false;
   return true;
}
Storage* init_storage_area(){
   Storage* res=malloc(sizeof(Storage));
   res->objects=0;
   res->max=BufferAddedObject;
   res->objects=malloc(sizeof(StorageObject*)*BufferAddedObject);
   return res;
}
int get_object_area(StorageObject *result[BufferGetedObj],Storage *storage,StorageObject *area){
   int n=0;
   for(int i=0;i<storage->n;i++){
      if(storage->objects[i]==NULL) continue;
      if(in_area(area,storage->objects[i])){
         result[n++]=storage->objects[i];
      }
   }  
   return n;
}
int add_object(Storage *storage,StorageObject *object){
   if(storage->n>=storage->max-1){
      storage->max+=BufferAddedObject;
      storage->objects=realloc(storage->objects,storage->max*sizeof(StorageObject));
   }
   int index=storage->n;
   for(int i=0;i<storage->n;i++){
      if(storage->objects[i]==NULL){
         index=i;
         break;
      }
   }
   storage->objects[index]=object;
   storage->n++;
   return index;
}
int del_object(Storage *storage,int index){
   if(storage->objects[index]==NULL) return 1;
   storage->objects[index]=NULL;
   return 0;
}
void del_storage(Storage *storage){
   free(storage->objects);
   free(storage);
}
