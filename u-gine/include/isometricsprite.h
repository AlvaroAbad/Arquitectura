#ifndef UGINE_ISOMETRICSPRITE_H
#define UGINE_ISOMETRICSPRITE_H
#include "sprite.h"

class IsometricSprite: public Sprite{
public:
	IsometricSprite(Image* image) :Sprite(image) {
		this->screenX = 0;
		this->screenY = 0;
	}
	virtual void SetPosition(double x,double y,double z);
	virtual double GetScreenX()const { return this->screenX; }
	virtual double GetScreenY()const { return this->screenY; }
	virtual void SetCollision(CollisionMode mode);
	virtual void Update(double elapsed, const Map*map = NULL);
protected:
	virtual void UpdateCollisionBox();
private:
	double screenX,screenY;
};
#endif