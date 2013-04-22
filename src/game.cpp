#include "game.h"
#ifdef __linux__
#include <unistd.h>
#endif

Game::Game(){
	Surf_Display  = NULL;
	Running       = true;
	winWidth      = 800;
	winHeight     = 600;
	keyStates     = new bool[256];
	moving        = false;
	active        = true;
	mouse.left    = mouse.middle = mouse.right = false;
	freelook_dx   = freelook_dy = 0;
}

int Game::Execute(){
	if(Init() == false){
		Cleanup();
		return -1;
	}

	SDL_Event event;

	while(Running){
		while(SDL_PollEvent(&event))
			Events(&event);
		
		Loop();
		if( active )
			Render();

		if( !active )
		#ifdef __linux__
			usleep(10000);
		#endif
		#ifdef _WIN32 
			Sleep(10);
		#endif
	}

	Cleanup();
	return 1;
}

int main(int argc, char* argv[]){
	#ifdef _WIN32 
	FreeConsole();
	#endif
 	Game theGame;
    return theGame.Execute();
}