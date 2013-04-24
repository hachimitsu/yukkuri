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
	float dot_product(vector3f);
	vector3f cross_product(vector3f);
	void normalize();
	vector3f unit();

	static vector3f i();
	static vector3f j();
	static vector3f k();

	vector3f& operator=(const vector3f &);
	vector3f operator+(const vector3f &);
	vector3f& operator+=(const vector3f&);
	vector3f operator-(const vector3f&);
	vector3f operator-();
	vector3f& operator-=(const vector3f&);
	vector3f operator*(const vector3f&);
	vector3f operator*(const float&);
	vector3f operator*(const int&);
	vector3f& operator*=(const vector3f&);
	vector3f& operator*=(const float&);
	vector3f& operator*=(const int&);
	vector3f operator/(const vector3f&);
	vector3f operator/(const float&);
	vector3f operator/(const int&);
	vector3f& operator/=(const vector3f&);
	vector3f& operator/=(const float&);
	vector3f& operator/=(const int&);
	friend vector3f operator*(const float&, const vector3f&);
	friend vector3f operator*(const int&, const vector3f&);
	bool operator==(const vector3f&) const;
	bool operator!=(const vector3f&) const;
};

#endif