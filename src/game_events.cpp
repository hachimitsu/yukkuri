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
					break;
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
			camera.lookat(float(Event->motion.x - winWidth/2),float(Event->motion.y - winHeight/2), MOUSE_SENSITIVITY, dt);
			SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
			SDL_WarpMouse(winWidth/2, winHeight/2);
			SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
			break;
	}
}