#include "..\Headers\game.h"

void Game::initialize()
{
	world = new World();
	world->worldInit();
	ui = new UserInterface(world);
}

void Game::run()
{
	world->run();
}

void Game::draw()
{
	world->draw();
}

void Game::getInput()
{
	ui->run();
}
