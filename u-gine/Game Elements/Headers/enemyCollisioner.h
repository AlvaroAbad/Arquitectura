#ifndef WORLDDEFENDER_ENEMY_COLLISIONER_H
#define WORLDDEFENDER_ENEMY_COLLISIONER_H
#include "entity.h"
class EnemyCollisioner: public Entity{
public:
	EnemyCollisioner(Image *image, String id, double x, double y, double height, double width) :Entity(image,String::Chr('C')+id, x, y, width, height) {};
	virtual void setSpeed(double speed) { this->speed = speed; }
	virtual double getSpeed() const { return this->speed; }

	virtual void update(double elapsed);
private:
	double speed;
};

#endif