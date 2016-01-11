#include "..\Headers\game.h"
#include "../../include/resourcemanager.h"
#include "../../include/screen.h"
#include "../Headers/externs.h"

void Game::initialize()
{
	world = new World();
	world->worldInit();
	ui = new UserInterface(world);
	//Load Font
	String fontFileName = FONT_DIR;
	font = ResourceManager::Instance().LoadFont(fontFileName);

	playingTime = 0;
	score = 0;
}

void Game::run()
{
	playingTime += Screen::Instance().ElapsedTime();
	timePlayed = String::FromInt(playingTime / 60 / 60);
	timePlayed += ":";
	timePlayed += String::FromInt(playingTime / 60);
	timePlayed += ":";
	timePlayed += String::FromInt(playingTime);
	world->run();
}

void Game::draw()const{
	String text = String::FromInt(playingTime / 60 / 60);
	text += ":";
	text += String::FromInt(playingTime / 60 );
	text += ":";
	text += String::FromInt(playingTime);
	world->draw();
	Renderer::Instance().SetColor(255, 0, 0, 255);
	Renderer::Instance().DrawText(font, text, 0, 0);
	text = "Score: ";
	text += String::FromInt(score);
	Renderer::Instance().DrawText(font, text, 0, 16);
}

void Game::getInput()
{
	ui->run();
}
