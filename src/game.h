#ifndef game_h
#define game_h 

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "Math/Maths.h"
#include "Camera.h"
#include <iostream>

#define MOUSE_SENSITIVITY 1.0f
#define GAME_SPEED 60.0f

struct Mouse{
	vector3f pos;
	bool left, middle, right;
};

class Game{
private:
	bool Running;
	SDL_Surface* Surf_Display;

	int winWidth;
	int winHeight;

	bool moving;
	vector3f destination;
	float movementSpeed;

	float cameraProjectionMatrix[16], cameraViewMatrix[16];

	bool* keyStates;

	Mouse mouse;
	Camera camera;
	vector3f light;

	float dt;

public:
	Game();

	int Execute();
	bool Init();
	void Events(SDL_Event* Event);
	void Loop();
	void Render();
	void Cleanup();
};

#endif