#include "game.h"

void draw_ring(float size){
	static GLuint index;

	if( !index ){
		index = glGenLists(1);

		glNewList(index,GL_COMPILE);
		glBegin(GL_LINE_LOOP);
			glColor4ub(247,181,27,255);
			int steps = 36;
			float dr = 360.0f/steps;
			for( int i = 0; i <= 360; i += dr ){
				glVertex3f(sin(to_rad(i)),0,cos(to_rad(i)));
			}
		glEnd();
		glEndList();
	}

	glPushMatrix();
	glScalef(size,1,size);
	glCallList(index);
	glPopMatrix();
}

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

void draw_cube(float size){
	float v = size/2.0f;
	glBegin(GL_QUADS);
		glNormal3f(0,0,1);
		glVertex3f(-v,v,v);
		glVertex3f(-v,-v,v);
		glVertex3f(v,-v,v);
		glVertex3f(v,v,v);

		glNormal3f(0,0,-1);
		glVertex3f(v,v,-v);
		glVertex3f(v,-v,-v);
		glVertex3f(-v,-v,-v);
		glVertex3f(-v,v,-v);

		glNormal3f(1,0,0);
		glVertex3f(v,v,v);
		glVertex3f(v,-v,v);
		glVertex3f(v,-v,-v);
		glVertex3f(v,v,-v);

		glNormal3f(-1,0,0);
		glVertex3f(-v,v,-v);
		glVertex3f(-v,-v,-v);
		glVertex3f(-v,-v,v);
		glVertex3f(-v,v,v);

		glNormal3f(0,1,0);
		glVertex3f(-v,v,-v);
		glVertex3f(-v,v,v);
		glVertex3f(v,v,v);
		glVertex3f(v,v,-v);

		glNormal3f(0,-1,0);
		glVertex3f(-v,-v,v);
		glVertex3f(-v,-v,-v);
		glVertex3f(v,-v,-v);
		glVertex3f(v,-v,v);
	glEnd();
}

void Game::drawScene(){
	int r = 30;

	glColor3f(1,1,1);
	draw_cube(0.1);

	glPushMatrix();
	glColor3f(0,1,0);
	glTranslatef(0,0,1);
	draw_cube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(1,0,0);
	draw_cube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(0,1,0);
	draw_cube(0.1);
	glPopMatrix();

	map.display(camera.get_pos());

	draw_hud();
}

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