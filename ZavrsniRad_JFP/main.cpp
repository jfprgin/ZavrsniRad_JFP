#include"stdafx.h"
#include "Game.h"

//Used to run the engine and initialize srand
int WinMain()
{
	srand(static_cast<unsigned>(time(0)));

	Game game;

	game.run();

	//End of application
	return 0;
}