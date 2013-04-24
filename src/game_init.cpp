#include "game.h"
#include "time.h"

bool Game::Init()
{
	putenv("SDL_VIDEO_CENTERED=1"); 
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
        return false;
    }

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    if((Surf_Display = SDL_SetVideoMode(winWidth, winHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL | SDL_RESIZABLE)) == NULL)
    {
        return false;
    }

    SDL_WM_SetCaption( "Project Touka", NULL );

    glViewport(0, 0, winWidth, winHeight);
    
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
	
	// GLfloat fogcolor[4] = {1,1,1,1};
	// glEnable(GL_FOG);
	// glFogi(GL_FOG_MODE,GL_LINEAR);
	// glFogfv(GL_FOG_COLOR,fogcolor);
	// glFogf(GL_FOG_DENSITY,0.02);
	// glFogf(GL_FOG_START,0.1f);
	// glFogf(GL_FOG_END,15.0f);
	// glHint(GL_FOG_HINT, GL_DONT_CARE);

	for (int i = 0; i < 256; ++i)
		keyStates[i] = false;

	camera.init(winWidth/float(winHeight));
	camera.setPos(0,3,3);
	camera.lookat(0, 0, 0);
	camera.setSpeed(MOUSEMINSPEED);

	light.set(-0.5,2,-2.7);
	float global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	map.init(30,30);
	
	return true;
}
