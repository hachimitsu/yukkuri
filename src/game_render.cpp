#include "game.h"

void drawHex(float x, float z)
{
	glBegin(GL_LINE_LOOP);
		glNormal3f(0,1,0);
		glVertex3f(x, 0, z+0.5f);
		glVertex3f(x + 0.433f, 0, z+0.25f);
		glVertex3f(x + 0.433f, 0, z-0.25f);
		glVertex3f(x, 0, z-0.5f);
		glVertex3f(x - 0.433f, 0, z-0.25f);
		glVertex3f(x - 0.433f, 0, z+0.25f);
	glEnd();
}

void setLights(vector3f light, float intensity)
{
	float white[] = {1*intensity,1*intensity,1*intensity,1};
	float specular[] = {0.8*intensity,0.8*intensity,0.8*intensity};
	float diffuse[] = {0.8*intensity,0.8*intensity,0.8*intensity};
	float light_position[] = {light.x, light.y, light.z};

	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void drawScene()
{
	GLfloat material_diffuse[] = {1,1,1,1};
	GLfloat material_specular[] = {1,1,1,1 };
    GLfloat material_shininess[] = { 60 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	static int gridSize = 26;
	float x = -(gridSize*2*0.866f)/2.0f, z = -float(gridSize/2.0f + (gridSize * 0.5)/2.0f);
	for (int i = 0; i <= gridSize*2; i++)
	{
		if(i%2 == 0)
			x = -(gridSize*2*0.866f)/2.0f;
		else
			x = -(gridSize*2*0.866f)/2.0f + 0.433;
		for (int j = 0; j <= gridSize*2; j++)
		{
			// glPushMatrix();
			// 	glColor4f(0,0,0,0);
			// 	glTranslatef(x,0.1,z);
			// 	glScalef(0.8,1,0.8);
			// 	glTranslatef(-x,0,-z);
			// 	drawHex(x,z);
			// glPopMatrix();	
			glColor3f(0.2,0.2,0.2);
			drawHex(x,z);
			x += 0.866;
		}
		z += .75;
	}
}

void Game::Render()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, winWidth, winHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(camera.getProjectionMatrix());
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(camera.getViewMatrix());

	setLights(light, 0.5);

	drawScene();

	SDL_GL_SwapBuffers();
}