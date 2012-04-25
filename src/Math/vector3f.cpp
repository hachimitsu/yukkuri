#include <string>
#include <stdio.h>
#include "Maths.h"

#define EPSILON 0.00001

vector3f::vector3f()
{
	x = 0;
	y = 0;
	z = 0;
}

vector3f::vector3f(float i, float j, float k)
{
	x = i;
	y = j;
	z = k;
}

void vector3f::set(float i, float j, float k)
{
	x = i;
	y = j;
	z = k;
}

float vector3f::magnitude()
{
	return sqrt(x*x + y*y + z*z);
}

std::string vector3f::tostring()
{
	char result[99];
	sprintf(result,"%.4f, %.4f, %.4f",x,y,z);

	return std::string(result);
}

float* vector3f::toarray(){
	float result[] = {x,y,z};
	return result;
}

vector3f vector3f::operator+(const vector3f& rhs)
{
	vector3f result;
	result.x = x + rhs.x;
	result.y = y + rhs.y;
	result.z = z + rhs.z;

	return result;
}

vector3f& vector3f::operator+=(const vector3f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

vector3f vector3f::operator-(const vector3f& rhs)
{
	vector3f result;
	result.x = x - rhs.x;
	result.y = y - rhs.y;
	result.z = z - rhs.z;

	return result;
}

vector3f& vector3f::operator-=(const vector3f& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

vector3f vector3f::operator*(const vector3f& rhs)
{
	vector3f result;
	result.x = x * rhs.x;
	result.y = y * rhs.y;
	result.z = z * rhs.z;

	return result;
}

vector3f vector3f::operator*(const float& rhs)
{
	vector3f result;
	result.x = x * rhs;
	result.y = y * rhs;
	result.z = z * rhs;

	return result;
}

vector3f vector3f::operator*(const int& rhs)
{
	vector3f result;
	result.x = x * rhs;
	result.y = y * rhs;
	result.z = z * rhs;

	return result;
}

vector3f operator*(const float lhs, const vector3f& rhs)
{
	vector3f result;
	result.x = rhs.x * lhs;
	result.y = rhs.y * lhs;
	result.z = rhs.z * lhs;

	return result;
}

vector3f operator*(const int lhs, const vector3f& rhs)
{
	vector3f result;
	result.x = rhs.x * lhs;
	result.y = rhs.y * lhs;
	result.z = rhs.z * lhs;

	return result;
}

vector3f vector3f::operator/(const vector3f& rhs)
{
	vector3f result;
	result.x = x / rhs.x;
	result.y = y / rhs.y;
	result.z = z / rhs.z;

	return result;
}

vector3f& vector3f::operator=(const vector3f& rhs)
{
	if( this == &rhs)
		return *this;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

bool vector3f::operator==(const vector3f& rhs) const
{
	float i = fabs(x-rhs.x);
	float j = fabs(y-rhs.y);
	float k = fabs(z-rhs.z);
	return i < EPSILON && j < EPSILON && k < EPSILON;
}

bool vector3f::operator!=(const vector3f& rhs) const
{
	return !(*this == rhs);
}