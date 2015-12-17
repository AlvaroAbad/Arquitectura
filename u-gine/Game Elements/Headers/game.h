#ifndef WORLDDEFENDER_GAME_H
#define WORLDDEFENDER_GAME_H
#include "userinterface.h"
#include "world.h"
class Game
{
public:
	Game(){};
	~Game() {  
		delete ui; 
	}
	void initialize();
	void run();
	void draw();
	void getInput();
	bool isEndGame() { return this->world->isEndGame(); }
private:
	
	World * world;
	UserInterface * ui;
};
#endif