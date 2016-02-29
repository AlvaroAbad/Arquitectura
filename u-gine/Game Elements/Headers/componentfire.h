#ifndef WORLDDEFENDER_COMPONENT_FIRE_H
#define WORLDDEFENDER_COMPONENT_FIRE_H
#include "component.h"
#include "world.h"
class ComponentFire : public Component
{
public:
	ComponentFire(double cooldown, Image * fireImage, World *world)
		: cooldown(cooldown), remeiningCD(0),
		fireImage(fireImage), world(world) {
		fire = false;
		heated = false;
	}
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);
protected:
	bool rayRectColision(double rX, double rY, double rWidth, double rHeight, double oX, double oY, double dX, double dY);
	int32 closestRectToPoint(double oX, double oY, double r1X, double r1Y, double r1Width, double r1Height, double r2X, double r2Y, double r2Width, double r2Height);
private:
	bool fire, heated;
	double targetX, targetY;
	double cooldown, remeiningCD;
	double originX, originY, distance;
	World * world;
	Image * fireImage;
};
#endif // !WORLDDEFENDER_COMPONENT_FIRE_H
