/*File "physick.c" create by abstarct, (чт, 07-гру-2023 17:25:08 +0200)*/
#include "physick.h"
#include <math.h>
double degrees_to_radian(double angle){
   return (angle/180)*PI;
}
double radian_to_degrees(double rad){
   return (rad*180)/PI;
}
coord get_angle_vector(coord a,double angle){
   double l=get_module(a);
   coord result={l*sin(degrees_to_radian(angle)),l*cos(degrees_to_radian(angle))};
   return result;
}
double get_module(coord a){
   return sqrt(a.x*a.x+a.y*a.y);
}
coord normilize(coord v){
   double size=get_module(v);
   coord result={v.x/size,v.y/size};
   return result;
}
double get_distance(coord a,coord b){
   b.x-=a.x;
   b.y-=a.y;
   return get_module(b);
}
