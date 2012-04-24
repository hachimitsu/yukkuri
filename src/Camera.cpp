#include "Math/Maths.h"
#include "Camera.h"
#include <SDL/SDL_opengl.h>

Camera::Camera(){

}

void Camera::lookat(float dx,float dy,float sensitivity,float dt)
{
	theta += dx * sensitivity * dt/5.0f;
	phi -= dy * sensitivity * dt/5.0f;

	theta = fmod(theta,360);

	if( phi < -180 )
		phi = -179.9999;
	else if( phi > 0 )
		phi = -0.0001;

	setViewMatrix();
}

void Camera::move(float tick)
{
	pos += (destination-pos) * (tick/10.0f);
	setViewMatrix();
}

void Camera::setSpeed(float s)
{
	speed = s;
}

void Camera::init(float ratio)
{
	pos = vector3f(0,0,0);
	heading = vector3f(0,0,-1);
	up = vector3f(0,1,0);
	right = vector3f(1,0,0);
	destination = vector3f(0,0,0);
	theta = 90;
	phi = -90;
	speed = 1.0f;
	in_action = false;

	setViewMatrix();
	setProjectionMatrix(ratio);
}

void Camera::setViewMatrix()
{
	heading.x = cos(M_PI1 * theta) * sin(M_PI1 * phi);
	heading.y = cos(M_PI1 * phi);
	heading.z = sin(M_PI1 * theta) * sin(M_PI1 * phi);

	heading = normalize(heading);
	right = normalize(crossProduct(heading,vector3f(0,1,0)));
	up = normalize(crossProduct(right,heading));

	glPushMatrix();
		glLoadIdentity();
		gluLookAt(pos.x, pos.y, pos.z,
			pos.x + heading.x, pos.y + heading.y, pos.z + heading.z,
			up.x, up.y, up.z);
		glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
	glPopMatrix();
}
	
void Camera::setProjectionMatrix(float ratio)
{
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(90.0f,ratio,0.1f,400.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, projectionMatrix);
	glPopMatrix();
}

void Camera::setPos(float i,float j,float k)
{
	pos.x = i;
	pos.y = j;
	pos.z = k;
}

void Camera::setHeading(float i,float j,float k)
{
	heading.x = i;
	heading.y = j;
	heading.z = k;
}

void Camera::setUp(float i,float j,float k)
{
	up.x = i;
	up.y = j;
	up.z = k;
}

void Camera::setRight(float i,float j,float k)
{
	right.x = i;
	right.y = j;
	right.z = k;
}

void Camera::setAngles(float i,float j)
{
	theta = i;
	phi = j;
}

void Camera::setDestination(float i,float j,float k)
{
	destination.x = i;
	destination.y = j;
	destination.z = k;
}

void Camera::setDestination(int d)
{
	switch(d)
	{
		case 4:
			destination = pos - right * speed;
			break;
		case 6:
			destination = pos + right * speed;
			break;
		case 8:
			destination = pos + heading * speed;
			break;
		case 2:
			destination = pos - heading * speed;
			break;
		case 7:
			destination = pos + normalize(right * -1 + heading) * speed;
			break;
		case 1:
			destination = pos + normalize(right * -1 - heading) * speed;
			break;
		case 9:
			destination = pos + normalize(right + heading) * speed;
			break;
		case 3:
			destination = pos + normalize(right - heading) * speed;
			break;
	}
}

void Camera::setPos(vector3f v)
{
	pos = v;
}

void Camera::setHeading(vector3f v)
{
	heading = v;
}

void Camera::setUp(vector3f v)
{
	up = v;
}

void Camera::setRight(vector3f v)
{
	right = v;
}

void Camera::setDestination(vector3f v)
{
	destination = v;
}
