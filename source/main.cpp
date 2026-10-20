#include "Game.h"

extern std::string_view PROJECT_NAME = "Hello Raylib";

int main()
{
	Game game = Game();
	game.run();
}