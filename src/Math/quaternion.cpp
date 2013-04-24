#include "quaternion.h"
#define EPSILON 0.00001f

float quaternion::magnitude(){
	return sqrt(w*w + dot_product(v,v));
}

void quaternion::normalize(){
	float mag = magnitude();
	if( mag > EPSILON && fabs(mag-1.0f) > EPSILON ){
		v /= mag;
		w /= mag;
	}
}

quaternion quaternion::unit(){
	quaternion q(v.x,v.y,v.z,w);
	float mag = magnitude();
	if( mag > EPSILON && fabs(mag-1.0f) > EPSILON ){
		q.normalize();
	}

	return q;
}

quaternion quaternion::conjugate(){
	return quaternion(-v, w);
}

float quaternion::dotproduct(quaternion _q){
	return w * _q.w + dot_product(v, _q.v);
}

float quaternion::get_angle(quaternion _q){
	quaternion q = unit();
	_q.normalize();

	return to_deg(acos(q.dotproduct(_q)));
}

vector3f quaternion::rotate(vector3f _p, vector3f _axis, float _angle){
	float angle = to_rad(_angle);
	quaternion q((float)sin(0.5f*angle) * _axis, cos(0.5f*angle)), p(_p);
	q.normalize();

	return (q * p * q.conjugate()).v;
}

vector3f quaternion::slerp(quaternion _q, float angle, float t){
	return ((float)sin((1-t)*angle)/(float)sin(angle)**this + (float)sin(t*angle)/(float)sin(angle)*_q).v;
}

vector3f quaternion::slerp(quaternion _q1, quaternion _q2, float angle, float t){
	return ((float)sin((1-t)*angle)/(float)sin(angle)*_q1 + (float)sin(t*angle)/(float)sin(angle)*_q2).v;
}

float* quaternion::matrix(){
	quaternion q = unit();
	float x2 = q.v.x * q.v.x;
	float y2 = q.v.y * q.v.y;
	float z2 = q.v.z * q.v.z;
	float xy = q.v.x * q.v.y;
	float xz = q.v.x * q.v.z;
	float yz = q.v.y * q.v.z;
	float wx = q.w   * q.v.x;
	float wy = q.w   * q.v.y;
	float wz = q.w   * q.v.z;

	static float result[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.0f};
	
	result[0] =	1.0f - 2.0f * (y2 + z2);
	result[1] = 2.0f * (xy - wz);
	result[2] = 2.0f * (xz + wy);
	result[4] = 2.0f * (xy + wz);
	result[5] = 1.0f - 2.0f * (x2 + z2);
	result[6] = 2.0f * (yz - wx);
	result[8] = 2.0f * (xz - wy);
	result[9] = 2.0f * (yz + wx);
	result[10] =  1.0f - 2.0f * (x2 + y2);
	
	return result;
}

void quaternion::from_axis(){
	v *= (float)sin(0.5f*w);
	w = cos(0.5f*w);
	normalize();
}

quaternion quaternion::from_axis(vector3f _v, float _w){
	quaternion q(_v,_w);
	q.v *= (float)sin(0.5f*_w);
	q.w = cos(0.5f*_w);
	q.normalize();
	return q;
}

quaternion quaternion::from_axis(float _x, float _y, float _z, float _w){
	quaternion q(_x,_y,_z,_w);
	q.v *= (float)sin(0.5f*_w);
	q.w = cos(0.5f*_w);
	q.normalize();
	return q;
}

quaternion::quaternion(){
	w = 0;
}

quaternion::quaternion(vector3f _v){
	v = _v;
	w = 0;
}

quaternion::quaternion(vector3f _v, float _w){
	v = _v;
	w = _w;
}

quaternion::quaternion(float x, float y, float z, float _w){
	v.set(x,y,z);
	w = _w;
}

quaternion::~quaternion(){}

quaternion quaternion::operator*(const quaternion& rhs){
	quaternion q;
	q.w = -v.x*rhs.v.x - v.y*rhs.v.y - v.z*rhs.v.z + w*rhs.w;
	q.v.x = v.x*rhs.w + v.y*rhs.v.z - v.z*rhs.v.y + w*rhs.v.x;
	q.v.y = -v.x*rhs.v.z + v.y*rhs.w + v.z*rhs.v.x + w * rhs.v.y;
	q.v.z = v.x*rhs.v.y - v.y*rhs.v.x + v.z*rhs.w + w*rhs.v.z;

	return q;
}

quaternion quaternion::operator*(const float& rhs){
	return quaternion(v * rhs, w * rhs);
}

quaternion quaternion::operator*(const int& rhs){
	return quaternion(v * rhs, w * rhs);
}

quaternion operator*(const float& lhs, const quaternion& rhs){
	return quaternion(lhs * rhs.v, lhs * rhs.w);
}

quaternion operator*(const int& lhs, const quaternion& rhs){
	return quaternion(lhs * rhs.v, lhs * rhs.w);
}

quaternion& quaternion::operator*=(const quaternion& rhs){
	*this = *this * rhs;

	return *this;
}

quaternion& quaternion::operator*=(const float& rhs){
	v *= rhs;
	w *= rhs;

	return *this;
}

quaternion& quaternion::operator*=(const int& rhs){
	v *= rhs;
	w *= rhs;

	return *this;
}

quaternion quaternion::operator+(const quaternion& rhs){
	return quaternion(v + rhs.v, w + rhs.w);
}

quaternion quaternion::operator-(const quaternion& rhs){
	return quaternion(v - rhs.v, w - rhs.w);
}

quaternion quaternion::operator-(){
	return quaternion(-v, -w);
}

quaternion& quaternion::operator+=(const quaternion& rhs){
	v += rhs.v;
	w += rhs.w;

	return *this;
}

quaternion& quaternion::operator-=(const quaternion& rhs){
	v -= rhs.v;
	w -= rhs.w;

	return *this;
}

quaternion& quaternion::operator=(const quaternion& rhs){
	if( this == &rhs)
		return *this;
	v = rhs.v;
	w = rhs.w;

	return *this;
}

bool quaternion::operator==(const quaternion& rhs) const{
	return v == rhs.v && fabs(w-rhs.w) < EPSILON;
}

bool quaternion::operator!=(const quaternion& rhs) const{
	return !(*this == rhs);
}