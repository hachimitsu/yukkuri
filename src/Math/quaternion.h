#pragma once
#include "Maths.h"

class quaternion
{

public:
	vector3f v;
	float w;

	quaternion();
	quaternion(vector3f);
	quaternion(vector3f,float);
	quaternion(float,float,float,float);
	~quaternion();

	float magnitude();
	void normalize();
	quaternion unit();
	quaternion conjugate();
	float dotproduct(quaternion);
	float get_angle(quaternion);
	static vector3f rotate(vector3f,vector3f,float);
	vector3f slerp(quaternion,float,float);
	static vector3f slerp(quaternion,quaternion,float,float);
	float* matrix();
	void from_axis();
	static quaternion from_axis(vector3f,float);
	static quaternion from_axis(float,float,float,float);

	quaternion operator*(const quaternion&);
	quaternion operator*(const float&);
	quaternion operator*(const int&);
	quaternion& operator*=(const quaternion&);
	quaternion& operator*=(const float&);
	quaternion& operator*=(const int&);
	friend quaternion operator*(const float&, const quaternion&);
	friend quaternion operator*(const int&, const quaternion&);

	quaternion operator+(const quaternion&);
	quaternion operator-(const quaternion&);
	quaternion operator-();
	quaternion& operator+=(const quaternion&);
	quaternion& operator-=(const quaternion&);

	quaternion& operator=(const quaternion&);
	bool operator==(const quaternion&) const;
	bool operator!=(const quaternion&) const;
};