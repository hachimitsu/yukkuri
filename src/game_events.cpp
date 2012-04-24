#include "game.h"

#define MOUSE_SENSITIVITY 1.0f

void Game::Events(SDL_Event* Event)
{
	switch(Event->type)
	{
		case SDL_QUIT:
			Running = false;
			break;
		case SDL_KEYDOWN:
			switch(Event->key.keysym.sym)
			{
				case SDLK_ESCAPE:
					Running = false;
					break;
				case SDLK_a:
					keyStates['a'] = true;
					break;
				case SDLK_s:
					keyStates['s'] = true;
					break;
				case SDLK_d:
					keyStates['d'] = true;
					break;
				case SDLK_w:
					keyStates['w'] = true;
					break;
				case SDLK_LSHIFT:
					camera.setSpeed(2.0f);
					break;
			}
			break;
		case SDL_KEYUP:
			switch(Event->key.keysym.sym)
			{
				case SDLK_a:
					keyStates['a'] = false;
					break;
				case SDLK_s:
					keyStates['s'] = false;
					break;
				case SDLK_d:
					keyStates['d'] = false;
					break;
				case SDLK_w:
					keyStates['w'] = false;
					break;
				case SDLK_LSHIFT:
					camera.setSpeed(1.0f);
					break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch(Event->button.button)
			{
				case SDL_BUTTON_MIDDLE:
					mouse.middle = true;
					mouse.pos.x = Event->button.x;
					mouse.pos.y = Event->button.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch(Event->button.button)
			{
				case SDL_BUTTON_MIDDLE:
					mouse.middle = false;
					break;
			}
			break;
		case SDL_MOUSEMOTION:
			if( mouse.middle )
			{
				camera.lookat(float(Event->motion.x - mouse.pos.x),float(Event->motion.y - mouse.pos.y), MOUSE_SENSITIVITY, dt);
				mouse.pos.x = Event->motion.x;
				mouse.pos.y = Event->motion.y;
			}
			break;
	}
}