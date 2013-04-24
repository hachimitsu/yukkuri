#include "game.h"

#define GAME_SPEED 25.0f
#define SKIP_TICKS 1000.0f/GAME_SPEED
#define MAX_FRAMESKIP 5
#define MOUSE_SENSITIVITY 0.5f

// Update the game state
void Game::update(){
	
}

// Move the camera depending on the keys pressed
void setDestination(Camera &camera, bool *keyStates){
	Uint8 *keystate = SDL_GetKeyState(NULL);
	bool a,s,d,w;

	a = keystate[SDLK_a];
	s = keystate[SDLK_s];
	d = keystate[SDLK_d];
	w = keystate[SDLK_w];

	if(a && w)
		camera.setDestination(7);
	else if(d && w)
		camera.setDestination(9);
	else if(a && s)
		camera.setDestination(1);
	else if(d && s)
		camera.setDestination(3);
	else if(a)
		camera.setDestination(4);
	else if(d)
		camera.setDestination(6);
	else if(w)
		camera.setDestination(8);
	else if(s)
		camera.setDestination(2);
}

// The game loop for timing and updating
// Updates the game at GAME_SPEED frames per second and will skip MAX_FRAMESKIP if it is behind
// Calculates dt for interpolation
void Game::Loop(){
	static unsigned long int next_game_tick = SDL_GetTicks();
	static int loops;

	if( active )
		setDestination(camera,keyStates);

	if( SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP ){
		if( active ){
			update();

			if( freelook_dx != 0 || freelook_dy != 0 )
				camera.lookat(freelook_dx,freelook_dy,MOUSE_SENSITIVITY,1);

			if( camera.moving())
				camera.move(1);
		}

		next_game_tick += SKIP_TICKS;
		loops++;
	}
	else loops = 0;

	if( active){
		dt = (SDL_GetTicks() + SKIP_TICKS - next_game_tick ) / float(SKIP_TICKS);
		if( dt > 1 ) dt = 1;

		if( camera.moving() )
			camera.move(dt);

		if( freelook_dx != 0 || freelook_dy != 0 ){
			camera.lookat(freelook_dx,freelook_dy,MOUSE_SENSITIVITY,dt);
			freelook_dy = freelook_dx = 0;
		}
	}
}