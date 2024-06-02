/*File "physick.h" create by abstarct, (чт, 07-гру-2023 17:25:08 +0200)*/
#ifndef ABSTARCT_PHYSICK_H_SENTURY
#define ABSTARCT_PHYSICK_H_SENTURY
#define PI 3.14159265359
typedef struct{
   float x,y;
} coord;
double degrees_to_radian(double angle);
double radian_to_degrees(double rad);
coord get_angle_vector(coord a,double angle);
coord normilize(coord v);
double get_module(coord v);

#endif
