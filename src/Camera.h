#ifndef Camera_H
#define Camera_H 

#include "Math/Maths.h"

class Camera{
private:
	vector3f pos;
	vector3f heading;
	vector3f up;
	vector3f right;
	float phi,theta;

	vector3f destination;
	float speed;
	bool in_action;

	float projectionMatrix[16], viewMatrix[16];

public:
	Camera();

	void setPos(float,float,float);
	void setHeading(float,float,float);
	void setUp(float,float,float);
	void setRight(float,float,float);
	void setAngles(float,float);
	void setDestination(float,float,float);
	void setDestination(int);
	void setSpeed(float);

	void setPos(vector3f);
	void setHeading(vector3f);
	void setUp(vector3f);
	void setRight(vector3f);
	void setDestination(vector3f);

	vector3f getPos(){ return pos; }
	vector3f getHeading(){ return heading; }
	vector3f getUp(){ return up; }
	vector3f getRight(){ return right; }

	void setViewMatrix();
	void setProjectionMatrix(float ratio);
	float* getViewMatrix(){ return viewMatrix; }
	float* getProjectionMatrix(){ return projectionMatrix; }

	void init(float);
	void move(float);
	void lookat(float,float,float);
	void lookat(vector3f);
	void lookat(float,float,float,float);

	bool moving(){ return in_action; }
};

#endif