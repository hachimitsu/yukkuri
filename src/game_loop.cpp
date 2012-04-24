#include "game.h"

#define GAME_SPEED 60.0f

void setDestination(Camera &camera, bool *keyStates)
{
	if(keyStates['a'] && keyStates['w']){
		camera.setDestination(7);
	}
	else if(keyStates['d'] && keyStates['w']){
		camera.setDestination(9);
	}
	else if(keyStates['a'] && keyStates['s']){
		camera.setDestination(1);
	}
	else if(keyStates['d'] && keyStates['s']){
		camera.setDestination(3);
	}
	else if(keyStates['a']){
		camera.setDestination(4);
	}
	else if(keyStates['d']){
		camera.setDestination(6);
	}
	else if(keyStates['w']){
		camera.setDestination(8);
	}
	else if(keyStates['s']){
		camera.setDestination(2);
	}
}

void Game::Loop()
{
	static int previousTime = 0;
	int currentTime;
	currentTime = SDL_GetTicks();

	dt = float((currentTime - previousTime) * GAME_SPEED /1000.0f);

	if(keyStates['a'] || keyStates['s'] || keyStates['d'] || keyStates['w'])
		setDestination(camera,keyStates);

	camera.move(dt);

	previousTime = currentTime;
}