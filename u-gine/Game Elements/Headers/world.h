#ifndef WORLDDEFENDER_WORLD_H
#define WORLDDEFENDER_WORLD_H
#include "entity.h"
#include "../../include/scene.h"
class World
{
public:
	World();
	void worldInit();
	~World();
	Entity * getPlayer() {
		return this->player;
	}
	void setMousX(int32 mouseX) { this->mouseX = mouseX; }
	void setMousY(int32 mouseY) { this->mouseY = mouseY; }
	bool isEndGame() { return this->endGame; }
	void run();
	void draw();
	void CreateBullet(Image * image,double originX, double originY, double directionX, double directionY);
	Array<Entity*> * GetEntities() { return &entities; }
protected:
	void createPlayer();
	void createCollider();
	void createShooter();
	void playerUpdate(double elapsed);
	void enemiesUpdate(double elapsed);
	bool rectCircleColision(double rX, double rY, double rWidth, double rHeight, double cX, double cY, double cR1, double cR2);
	
private:
	int32 mouseX, mouseY;
	Font *font;
	Image *collisionerImage;
	Image *playerImage;
	Image *bulletImage;
	Entity *player;
	Array<Entity*> entities;
	Array<Entity*> deadEnemies;
	Entity * firstImpact;
	Scene * scene;
	double collisionersElapsedSpawnTime;
	double shootersElapsedSpawnTime;
	bool endGame;
};
#endif