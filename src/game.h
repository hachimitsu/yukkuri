#ifndef game_h
#define game_h 

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "Math/Maths.h"
#include "Camera/Camera.h"
#include "Map/Map.h"

#define MOUSEMINSPEED 0.1f
#define MOUSEMAXSPEED 0.2f

struct Mouse{
	vector3f pos;
	bool left, middle, right;
};

class Game{
private:
	bool Running, active;
	SDL_Surface* Surf_Display;

	int winWidth;
	int winHeight;

	bool moving, disable;
	vector3f destination;

	bool* keyStates;

	Mouse mouse;
	int freelook_dx, freelook_dy;
	Camera camera;
	vector3f light;

	float dt;

	Map map;

	bool Init();
	void Events(SDL_Event* Event);
	void Loop();
	void Render();
	void Cleanup();
	void drawScene();
	void update();
	void interpolate();
	void draw_hud();

public:
	Game();
	~Game(){};

	int Execute();
};

#endif