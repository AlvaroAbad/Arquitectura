#include "..\Headers\game.h"

void Game::initialize()
{
	ui = new UserInterface();
	this->ui->userInterfaceInit();
	world = this->ui->getWorld();
	
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
