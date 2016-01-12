#ifndef WORLDDEFENDER_BULLET_H
#define WORLDDEFENDER_BULLET_H
#include "entity.h"
class Bullet : public Entity {
public:
	Bullet(Image *image, String id, double x, double y, double height, double width) :Entity(image, String::Chr('B') + id, x, y, width, height) {};

	virtual void setSpeed(double speed) { this->speed = speed; }
	virtual double getSpeed() const { return this->speed; }

	virtual void update(double elapsed);
private:
	double speed;
};
#endif