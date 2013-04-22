#include "game.h"

//Set light position and properties
void setLights(vector3f light, float intensity){
	GLfloat sun[]  = { 1, 1, 1, 1 };
	GLfloat ambient[]  = { 1, 1, 1, 1 };
	GLfloat diffuse[]  = { 0.4, 0.4, 0.4, 1 };
	GLfloat specular[] = { 1, 1, 1, 1 };
	float light_position[] = {light.x, light.y, light.z, 0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

// Draw the HUD
void Game::draw_hud(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,winWidth,winHeight,0,-1,1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

//Draw the world and all objects
void Game::drawScene(){
	int r = 10;

	glColor3f(1,0,0);
	glNormal3f(0,1,0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0,0);
	for( int i = 0; i >= -360; i-=10 ){
		vector3f p(r * cos(to_rad(i)), 0, r * sin(to_rad(i)));
		glVertex3f(p.x,p.y,p.z);
	}
	glEnd();


	draw_hud();
}

// Setup the environment for drawing
void Game::Render(){
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(camera.getProjectionMatrix());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(camera.getViewMatrix());

	setLights(light, 0.5);

	drawScene();
	SDL_GL_SwapBuffers();
}