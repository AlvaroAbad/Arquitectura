#ifndef WORLDDEFENDER_ENEMY_SHOOTER_H
#define WORLDDEFENDER_ENEMY_SHOOTER_H
#include "entity.h"
class EnemyShooter : public Entity {
public:
	EnemyShooter(Image *image, String id, double x, double y, double height, double width) :Entity(image, String::Chr('S') + id, x, y, width, height) { this->cooldown = 0; };
	virtual void setSpeedX(double speedX) { this->speedX = speedX; }
	virtual double getSpeedX() const { return this->speedX; }
	virtual void setSpeedY(double speedY) { this->speedY = speedY; }
	virtual double getSpeedY() const { return this->speedY; }
	virtual void fire() { this->cooldown = 1; }
	virtual void update(double elapsed);
	virtual double readyToShoot() { return !this->cooldown; }
private:
	double speedX,speedY;
	double cooldown;
};

#endif