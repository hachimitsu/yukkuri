#include "game.h"

void Game::Cleanup()
{
	delete keyStates;
	SDL_Quit();
}