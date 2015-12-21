#ifndef WORLDDEFENDER_WORLD_H
#define WORLDDEFENDER_WORLD_H
#include "player.h"
#include "enemyShooter.h"
#include "enemyCollisioner.h"
class World
{
public:
	World();
	void worldInit();
	~World();
	Player * getPlayer() {
		return this->player;
	}
	void setMousX(int32 mouseX) { this->mouseX = mouseX; }
	void setMousY(int32 mouseY) { this->mouseY = mouseY; }
	bool isEndGame() { return this->endGame; }
	void run();
	void draw();
protected:
	void playerUpdate(double elapsed);
	void enemiesUpdate(double elapsed);
	bool rectCircleColision(double rX, double rY, double rWidth, double rHeight, double cX, double cY, double cR1, double cR2);
	bool rayRectColision(double rX, double rY, double rWidth, double rHeight, double oX, double oY, double dX, double dY);
	int32 closestRectToPoint(double oX, double oY, double r1X, double r1Y, double r1Width, double r1Height, double r2X, double r2Y, double r2Width, double r2Height);
private:
	int32 mouseX, mouseY;
	Font *font;
	Image *collisionerImage;
	Image *shooterImage;
	Image *playerImage;
	Image *backgroundImage;
	double speedBoost;
	Player *player;
	Array<Entity*> entities;
	Array<Entity*> deadEnemies;
	Entity * firstImpact;
	double collisionersElapsedSpawnTime;
	double shootersElapsedSpawnTime;
	bool endGame;
};
#endif