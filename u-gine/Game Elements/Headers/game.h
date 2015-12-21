#ifndef WORLDDEFENDER_GAME_H
#define WORLDDEFENDER_GAME_H
#include "userinterface.h"
#include "world.h"
class Game
{
public:
	Game(){};
	~Game() {  
		delete world;
		delete ui; 
	}
	void initialize();
	void run();
	void draw() const;
	void getInput();
	bool isEndGame() { return this->world->isEndGame(); }
	uint32 getScore() { return this->score; }
	void setScore(uint32 score) { this->score = score; }
private:
	
	World * world;
	UserInterface * ui;
	Font *font;
	double playingTime;
	String timePlayed;
	uint32 score;
};
#endif