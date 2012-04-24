#ifndef vector3f_h
#define vector3f_h

class vector3f{
public:
	float x,y,z;
	vector3f();
	vector3f(float,float,float);

	void set(float,float,float);
	float magnitude();
	std::string tostring();
	float* toarray();

	vector3f& operator=(const vector3f &);
	vector3f operator+(const vector3f &);
	vector3f operator-(const vector3f&);
	vector3f operator*(const vector3f&);
	vector3f operator*(const float&);
	vector3f operator*(const int&);
	vector3f& operator+=(const vector3f&);
	vector3f& operator-=(const vector3f&);
	friend vector3f operator*(const float&, const vector3f&);
	friend vector3f operator*(const int&, const vector3f&);
	vector3f operator/(const vector3f&);
	bool operator==(const vector3f&) const;
	bool operator!=(const vector3f&) const;
};

#endif