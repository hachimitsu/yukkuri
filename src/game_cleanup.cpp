#include "game.h"

void Game::Cleanup()
{
	delete keyStates;
	SDL_FreeSurface(Surf_Display);
	SDL_Quit();
}