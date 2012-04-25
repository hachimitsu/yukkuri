#include "game.h"

Game::Game()
{
	Surf_Display = NULL;
	Running = true;
	winWidth = 800;
	winHeight = 600;
	keyStates = new bool[256];
	moving = false;
	active = true;
}

int Game::Execute()
{
	if(Init() == false)
		return -1;

	SDL_Event event;

	while(Running)
	{
		while(SDL_PollEvent(&event))
				Events(&event);
		if( active ){
			Loop();
			Render();
		}
		Sleep(10);
	}

	Cleanup();
}

int main(int argc, char* argv[])
{
	//FreeConsole();
 	Game theGame;
    return theGame.Execute();
}