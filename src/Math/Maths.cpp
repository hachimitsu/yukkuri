#include "Maths.h"

float real_rand(){
	return (float)rand()/(float)RAND_MAX;
}

int rand_range(int b, int e){
	return rand() % (e-b) + b;
}

float get_angle(vector3f u, vector3f v)
{
	return to_deg(acos(dot_product(u,v)/(u.magnitude() * v.magnitude())));
}

vector3f normal(vector3f i, vector3f j, vector3f k)
{
	vector3f v1 = (j-i);
	vector3f v2 = (k-i);

	return cross_product(v1,v2).unit();
}

float to_rad(float d){
	return d * M_PI1;
}

float to_deg(float r){
	return r * M_PI2;
}

void set_colour(colour &c, int r, int g, int b, int o){
	c.r = r;
	c.g = g;
	c.b = b;
	c.o = o;
}