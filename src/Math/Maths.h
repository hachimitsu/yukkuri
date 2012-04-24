#ifndef Maths_h
#define Maths_h

#define M_PI 3.14159265358979323846
#define M_PI1 M_PI/180.0f

#include <string>
#include <math.h>
#include "vector3f.h"

float dotProduct(vector3f, vector3f);
float getAngle(vector3f, vector3f);
vector3f crossProduct(vector3f, vector3f);
vector3f normalize(vector3f);
vector3f normal(vector3f,vector3f,vector3f);

#endif