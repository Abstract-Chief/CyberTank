/*File "storage.h" create by abstarct, (пн, 04-гру-2023 18:28:49 +0200)*/
#ifndef ABSTARCT_STORAGE_H_SENTURY
#define ABSTARCT_STORAGE_H_SENTURY

#define BufferAddedObject 64
#define BufferGetedObj 64

typedef struct{
   int x,y,w,h,index,type;
} StorageObject;

typedef struct Storage{
   int n,max;
   StorageObject **objects;
} Storage;

Storage* init_storage_area();
int get_object_area(StorageObject *result[BufferGetedObj],Storage *area,StorageObject *object);
int add_object(Storage *storage,StorageObject *object);
int del_object(Storage *area,int index);
void del_storage(Storage *storage);

#endif
