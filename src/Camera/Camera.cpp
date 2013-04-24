#include "Camera.h"
#include <SDL/SDL_opengl.h>

Camera::Camera(){

}

// Looks at a given point
void Camera::lookat(vector3f target)
{
	target = target - pos;

	theta = get_angle(-vector3f::i(), target);
	if( target.z > 0 )
		theta = -theta;

	phi = -get_angle(vector3f::j(), target);

	setViewMatrix();
}

// Looks at a given point
void Camera::lookat(float x, float y, float z)
{
	vector3f target(x,y,z);

	target = target - pos;

	theta = get_angle(-vector3f::i(), target);
	if( target.z > 0 )
 		theta = -theta;

	phi = -get_angle(vector3f::j(), target);

	setViewMatrix();
}

// Changes the cameras rotation. Used for free looking with the mouse.
void Camera::lookat(float dx,float dy,float sensitivity,float dt)
{
	theta += dx * sensitivity * dt;
	phi -= dy * sensitivity * dt;

	theta = fmod(theta,360);

	if( phi < -180 )
		phi = -179.9999;
	else if( phi > 0 )
		phi = -0.0001;

	setViewMatrix();
}


// Moves the camera position
void Camera::move(float tick)
{
	pos += (destination-pos) * tick;
	if( (destination-pos).magnitude() < 0.05f )
		in_action = false;
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
	heading.x = cos(to_rad(theta)) * sin(to_rad(phi));
	heading.y = cos(to_rad(phi));
	heading.z = sin(to_rad(theta)) * sin(to_rad(phi));

	heading.normalize();
	right = cross_product(heading,vector3f::j()).unit();
	up = cross_product(right,heading).unit();

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
		gluPerspective(60.0f,ratio,0.1f,100.0f);
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

// setDestination points to where the camera is moving to.
void Camera::setDestination(float i,float j,float k)
{
	destination.x = i;
	destination.y = j;
	destination.z = k;
	in_action = true;
}

void Camera::setDestination(vector3f d, float dragspeed)
{
	vector3f h(heading.x,0,heading.z);
	h = h * d.z + right * -d.x;
	destination = pos + h.unit() * dragspeed;
	in_action = true;
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
			destination = pos + (-right + heading).unit() * speed;
			break;
		case 1:
			destination = pos + (-right - heading).unit() * speed;
			break;
		case 9:
			destination = pos + (right + heading).unit() * speed;
			break;
		case 3:
			destination = pos + (right - heading).unit() * speed;
			break;
	}
	in_action = true;
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
