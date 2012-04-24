#include "game.h"

using namespace std;

Game::Game()
{
	Surf_Display = NULL;
	Running = true;
	winWidth = 800;
	winHeight = 600;
	keyStates = new bool[256];
	moving = false;
}

int Game::Execute()
{
	if(Init() == false)
		return -1;

	SDL_Event event;

	while(Running)
	{
		while(SDL_PollEvent(&event))
		{
			Events(&event);
		}
		Loop();
		Render();
		Sleep(16);
	}

	Cleanup();
}

int main(int argc, char* argv[])
{
	FreeConsole();
    Game theGame;
    return theGame.Execute();
}