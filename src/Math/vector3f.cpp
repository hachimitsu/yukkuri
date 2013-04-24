#include <string>
#include <stdio.h>
#include "Maths.h"

#define EPSILON 0.00001f

vector3f::vector3f(){
	x = 0;
	y = 0;
	z = 0;
}

vector3f::vector3f(float i, float j, float k){
	x = i;
	y = j;
	z = k;
}

void vector3f::set(float i, float j, float k){
	x = i;
	y = j;
	z = k;
}

void vector3f::normalize(){
	float mag = magnitude();

	if( mag > EPSILON && fabs(mag-1.0f) > EPSILON ){
		mag = 1.0f / mag;
		x *= mag;
		y *= mag;
		z *= mag;
	}
}

vector3f vector3f::unit(){
	float mag = magnitude();

	if( mag > EPSILON && fabs(mag-1.0f) > EPSILON ){
		mag = 1.0f / mag;
		return vector3f(x*mag, y*mag, z*mag);
	}

	return *this;	
}

float vector3f::magnitude(){
	return sqrt(x*x + y*y + z*z);
}

float vector3f::dot_product(vector3f v){
	return x*v.x + y*v.y + z*v.z;
}

float dot_product(vector3f u, vector3f v){
	return u.x*v.x + u.y*v.y + u.z*v.z;
}

vector3f vector3f::cross_product(vector3f v){
	return vector3f(y*v.z - z*v.y,
		z*v.x - x*v.z,
		x*v.y - y*v.x);
}

vector3f cross_product(vector3f u, vector3f v){
	return vector3f(u.y*v.z - u.z*v.y,
		u.z*v.x - u.x*v.z,
		u.x*v.y - u.y*v.x);
}

std::string vector3f::tostring(){
	char result[99];
	sprintf(result,"%.4f, %.4f, %.4f",x,y,z);

	return std::string(result);
}

float* vector3f::toarray(){
	static float result[] = {x,y,z};
	return result;
}

vector3f vector3f::i(){
	return vector3f(1,0,0);
}

vector3f vector3f::j(){
	return vector3f(0,1,0);
}

vector3f vector3f::k(){
	return vector3f(0,0,1);
}

vector3f vector3f::operator+(const vector3f& rhs){
	vector3f result;
	result.x = x + rhs.x;
	result.y = y + rhs.y;
	result.z = z + rhs.z;

	return result;
}

vector3f& vector3f::operator+=(const vector3f& rhs){
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

vector3f vector3f::operator-(const vector3f& rhs){
	vector3f result;
	result.x = x - rhs.x;
	result.y = y - rhs.y;
	result.z = z - rhs.z;

	return result;
}

vector3f vector3f::operator-(){
	vector3f result;
	result.x = -x;
	result.y = -y;
	result.z = -z;

	return result;
}

vector3f& vector3f::operator-=(const vector3f& rhs){
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

vector3f vector3f::operator*(const vector3f& rhs){
	vector3f result;
	result.x = x * rhs.x;
	result.y = y * rhs.y;
	result.z = z * rhs.z;

	return result;
}

vector3f vector3f::operator*(const float& rhs){
	vector3f result;
	result.x = x * rhs;
	result.y = y * rhs;
	result.z = z * rhs;

	return result;
}

vector3f vector3f::operator*(const int& rhs){
	vector3f result;
	result.x = x * rhs;
	result.y = y * rhs;
	result.z = z * rhs;

	return result;
}

vector3f& vector3f::operator*=(const vector3f& rhs){
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

vector3f& vector3f::operator*=(const float& rhs){
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

vector3f& vector3f::operator*=(const int& rhs){
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

vector3f vector3f::operator/(const vector3f& rhs){
	vector3f result;
	result.x = x / rhs.x;
	result.y = y / rhs.y;
	result.z = z / rhs.z;

	return result;
}

vector3f vector3f::operator/(const float& rhs){
	vector3f result;
	result.x = x / rhs;
	result.y = y / rhs;
	result.z = z / rhs;

	return result;
}

vector3f vector3f::operator/(const int& rhs){
	vector3f result;
	result.x = x / float(rhs);
	result.y = y / float(rhs);
	result.z = z / float(rhs);

	return result;
}

vector3f& vector3f::operator/=(const vector3f& rhs){
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;

	return *this;
}

vector3f& vector3f::operator/=(const float& rhs){
	x /= rhs;
	y /= rhs;
	z /= rhs;

	return *this;
}

vector3f& vector3f::operator/=(const int& rhs){
	x /= rhs;
	y /= rhs;
	z /= rhs;

	return *this;
}

vector3f operator*(const float& lhs, const vector3f& rhs){
	vector3f result;
	result.x = rhs.x * lhs;
	result.y = rhs.y * lhs;
	result.z = rhs.z * lhs;

	return result;
}

vector3f operator*(const int& lhs, const vector3f& rhs){
	vector3f result;
	result.x = rhs.x * lhs;
	result.y = rhs.y * lhs;
	result.z = rhs.z * lhs;

	return result;
}

vector3f& vector3f::operator=(const vector3f& rhs){
	if( this == &rhs)
		return *this;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

bool vector3f::operator==(const vector3f& rhs) const{
	float i = fabs(x-rhs.x);
	float j = fabs(y-rhs.y);
	float k = fabs(z-rhs.z);
	return i < EPSILON && j < EPSILON && k < EPSILON;
}

bool vector3f::operator!=(const vector3f& rhs) const{
	return !(*this == rhs);
}