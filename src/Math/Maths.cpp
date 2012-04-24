#include "Maths.h"

float dotProduct(vector3f u, vector3f v)
{
	return u.x*v.x + u.y*v.y + u.z*v.z;
}

float getAngle(vector3f u, vector3f v)
{
	return 180.0f/M_PI * acos(dotProduct(u,v)/(u.magnitude() * v.magnitude()));
}

vector3f normalize(vector3f u)
{
	float mag = u.magnitude();

	return vector3f(u.x/mag, u.y/mag, u.z/mag);
}

vector3f crossProduct(vector3f u, vector3f v)
{
	return vector3f(u.y*v.z - u.z*v.y,
		u.z*v.x - u.x*v.z,
		u.x*v.y - u.y*v.x);
}

vector3f normal(vector3f i, vector3f j, vector3f k)
{
	vector3f v1 = normalize(j-i);
	vector3f v2 = normalize(k-i);

	return crossProduct(v1,v2);
}