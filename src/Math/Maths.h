#ifndef Maths_h
#define Maths_h

#define M_PI 3.14159265358979323846
#define M_PI1 M_PI/180.0f
#define M_PI2 180.0f/M_PI

#include <string>
#include <math.h>
#include "vector3f.h"
#include "quaternion.h"
#include <cstdlib>
#include <vector>

struct colour
{
	int r, g, b, o;
};

float dot_product(vector3f, vector3f);
float get_angle(vector3f, vector3f);
vector3f cross_product(vector3f, vector3f);
vector3f normal(vector3f,vector3f,vector3f);
float real_rand();
float to_rad(float);
float to_deg(float);
void set_colour(colour&,int,int,int,int);



#endif