#include "game.h"

bool Game::Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

    if((Surf_Display = SDL_SetVideoMode(winWidth, winHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL)) == NULL)
    {
        return false;
    }
    
    glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
	glEnable( GL_POINT_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonOffset(1, 4);
	glEnable(GL_POLYGON_OFFSET_FILL);

	for (int i = 0; i < 256; ++i)
	{
		keyStates[i] = false;
	}

	camera.init((float)winWidth/(float)winHeight);
	camera.setPos(0,5,5);
	camera.setDestination(camera.getPos());
	camera.setViewMatrix();

	light.set(0,5,0);

	float global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	return true;
}