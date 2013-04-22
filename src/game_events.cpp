#include "game.h"

// Keyboard and mouse input handler
void Game::Events(SDL_Event* Event)
{
	// If window is not active, disables all input and pauses the game
	// Renables everything when window regains focus
	if ( Event->type == SDL_ACTIVEEVENT){
		if(Event->active.state & SDL_APPACTIVE || Event->active.state & SDL_APPINPUTFOCUS){
			if(Event->active.gain){
				active = true;	
				//SDL_ShowCursor(0);
				SDL_WarpMouse(winWidth/2, winHeight/2);
				SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
				SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
				SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);
				SDL_EventState(SDL_KEYUP, SDL_ENABLE);
				SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
			}
			else{	
				active = false;
				//SDL_ShowCursor(1);
				SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
				SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
				SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
				SDL_EventState(SDL_KEYUP, SDL_IGNORE);
				SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
			}
		}
	}
	if( active ){
		switch(Event->type){
			case SDL_VIDEORESIZE:
				winWidth = Event->resize.w;
				winHeight = Event->resize.h;

				glViewport(0, 0, winWidth, winHeight);
				camera.setProjectionMatrix((float)winWidth/(float)winHeight);
				break;
			case SDL_QUIT: // Quits the game when pressing the close button
				Running = false;
				break;
			case SDL_KEYDOWN: // Sets the keystate for the pressed key
				switch(Event->key.keysym.sym){
					case SDLK_ESCAPE: // Quits the game when the ESC key is pressed
						Running = false;
						break;
					case SDLK_LSHIFT: // Doubles the movement speed for the camera
						camera.setSpeed(0.05f);
						break;
				}
				break;
			case SDL_KEYUP:
				switch(Event->key.keysym.sym)
				{
					case SDLK_LSHIFT:
						camera.setSpeed(0.025f);
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN: // Handles mouse button presses
				switch(Event->button.button){
					case SDL_BUTTON_MIDDLE:{
						mouse.middle = true;
						SDL_ShowCursor(0);
						SDL_WarpMouse(winWidth/2, winHeight/2);
						break;
					}
					case SDL_BUTTON_LEFT:{
						break;
					}
					case SDL_BUTTON_RIGHT:{
						mouse.right = true;
						mouse.pos.x = Event->button.x;
						mouse.pos.y = Event->button.y;
						break;
					}
					case SDL_BUTTON_WHEELUP:{
						camera.setSpeed(0.25);
						camera.setDestination(8);
						camera.setSpeed(0.025);
						break;
					}
					case SDL_BUTTON_WHEELDOWN:{
						camera.setSpeed(0.25);						
						camera.setDestination(2);
						camera.setSpeed(0.025);
						break;
					}
				}
				break;
			case SDL_MOUSEBUTTONUP: // Handles mouse button releases
				switch(Event->button.button){
					case SDL_BUTTON_MIDDLE:{
						mouse.middle = false;
						freelook_dx = freelook_dy = 0;
						SDL_ShowCursor(1);
						break;
					}
					case SDL_BUTTON_LEFT:{
						break;
					}
					case SDL_BUTTON_RIGHT:{
						mouse.right = false;
						break;
					}
				}
				break;
			case SDL_MOUSEMOTION:{ // Handles mouse motion
				if( mouse.middle ){ // Handles free look
					freelook_dx = Event->motion.x - winWidth/2;
					freelook_dy = Event->motion.y - winHeight/2;

					SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
					SDL_WarpMouse(winWidth/2, winHeight/2);
					SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
				}
				else if( mouse.right ){ // Handles dragging the map
					destination.set(Event->motion.x-mouse.pos.x, 0, Event->motion.y-mouse.pos.y);
					camera.setDestination(destination.unit(), 0.1f * camera.get_pos().y);
					mouse.pos.x = Event->motion.x;
					mouse.pos.y = Event->motion.y;
				}
			}
		}
	}
}