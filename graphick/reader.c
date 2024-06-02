/*File "reader.c" create by abstarct, (Вс 19 ноя 2023 21:06:01)*/
#include "../physick/physick.h"
#include "reader.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>

void parse_color(FILE *file,short *r,short *g,short *b){
      fread(r,sizeof(short),1,file);
      fread(g,sizeof(short),1,file);
      fread(b,sizeof(short),1,file);
}
void ParseColors(FILE *file){
   int count=0;
   fread(&count,sizeof(char),1,file);
   for(int i=2;i<count;i++){
      short r,g,b;
      parse_color(file,&r,&g,&b);
      short a=(r*1000)/255,f=(g*1000)/255,c=(b*1000)/255;
      init_color(i+1,a,f,c);
   }
}
void ParsePair(FILE *file){
   ParseColors(file);
   short n;
   fread(&n,sizeof(n),1,file);
   short a,b;
   for(int i=1;i<=n;i++){
      fread(&a,sizeof(a),1,file);
      fread(&b,sizeof(b),1,file);
      init_pair(i,a,b);
   }
}
Point* deserialize_point(FILE *file){
   Point* p=malloc(sizeof(Point));
   fread(&p->symbol,1,1,file);
   fread(&p->x,sizeof(short),1,file);
   fread(&p->y,sizeof(short),1,file);
   fread(&p->color,sizeof(short),1,file);
   return p;
}
Layer* ParseLayer(FILE *file){
   Layer* layer=malloc(sizeof(Layer));
   fread(&layer->count,sizeof(int),1,file);
   fread(&layer->cols,sizeof(int),1,file);
   fread(&layer->rows,sizeof(int),1,file);
   layer->data=malloc(sizeof(Point*)*layer->rows*layer->cols);
   for(int i=0;i<layer->count;i++){
      layer->data[i]=deserialize_point(file);
   }
   return layer;
}
Animation* ParseAnim(FILE *file){
   Animation* anim=malloc(sizeof(Animation));
   fread(&anim->count,sizeof(int),1,file);
   int rows=-1,cols=-1;
   for(int i=0;i<anim->count;i++){
      anim->layers[i]=ParseLayer(file);
      if(rows==-1 && cols==-1){
         rows=anim->layers[i]->rows;
         cols=anim->layers[i]->cols;
      }
      anim->layers[i]->rows=rows;
      anim->layers[i]->cols=cols;

   }
   ParsePair(file);
   return anim;
}

Animation* AnimationParse(const char* filename){
   FILE *file=fopen(filename,"rb");
   if(file==NULL){
      printf("error open %s",filename);
      exit(1);
   }
   Animation* anim=ParseAnim(file);
   fclose(file);
   return anim;
}
Layer* LayerParse(const char* filename){
   FILE *file=fopen(filename,"rb");
   if(file==NULL){
      printf("error open %s",filename);
      exit(1);
   }
   Layer* layer=ParseLayer(file);
   fclose(file);
   return layer;
}
#define MIRROR(MAX,COORD,TASK)  ((TASK ? MAX : 0)-(COORD))*(TASK ? 1 : -1)
void graphick_layer(WINDOW *win,int x,int y,Layer *layer,bool mirror_x,bool mirror_y){
   for(int i=0;i<layer->count;i++){
      Point *p=layer->data[i];
      wattron(win,COLOR_PAIR(p->color));
      mvwaddch(win,MIRROR(layer->rows,p->y,mirror_y)+y,MIRROR(layer->cols,p->x,mirror_x)+x,p->symbol);
      wattroff(win,COLOR_PAIR(p->color));
   }
}
bool graphick_anim(WINDOW *win,int x,int y,Animation *anim,float d,bool mirror_x,bool mirror_y){
   graphick_layer(win,x,y,anim->layers[(int)roundf(anim->n_layer)],mirror_x,mirror_y);
   anim->n_layer+=d;
   if(anim->n_layer>=anim->count-1){
      anim->n_layer=0;
      return 1;
   } 
   return 0;
}
coord CenterAnimation(Animation *tank){
   coord res={(float)tank->layers[0]->cols/2,(float)tank->layers[0]->rows/2};
   return res;
}
