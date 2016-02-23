#ifndef WORLDDEFENDER_PLAYER_H
#define WORLDDEFENDER_PLAYER_H
#include "../../include/types.h"
#include "entity.h"
class Player : public Entity{
	
public:
	enum direction {
		UP=-1,
		DOWN=1,
		LEFT=-1,
		RIGHT=1,
		STOP=0
	};
	Player(Sprite * sprite,String id,double x, double y, double radius) : radius(radius),Entity(sprite,String::Chr('P')+id,x,y,2*radius,2*radius) { 
		this->status = 0; 
		this->firing = 0;
		this->overheat = 0;
		this->direction = UP;
		this->movement = STOP;
	};
	//Position setter and getters
	virtual void setRadius(double radius) { 
		this->radius = radius; 
		this->setWidth(radius * 2);
		this->setHeight(radius * 2);
	}
	virtual double getRadius()const { return this->radius; }
	virtual void setMovement(direction movement) { this->movement = movement; }
	virtual direction getMovement() { return this->movement; }
	//status
	virtual bool isJumping()const { return  this->status & 0x01; }
	virtual void jump() { this->status |= 0x01; }
	virtual void land() { this->status &= ~0x01; }
	virtual bool isOverheated() const { return  (this->status & 0x02)!=0; }
	virtual void overheated() { this->status |= 0x02; }
	virtual void cooled() { this->status &= ~0x02; }
	virtual bool isFiring()const { return  this->firing>0; }
	
	//indicators setters and getters
	virtual void setFiringLimit(double time) { this->firing = time; }
	virtual double getFiringLimit() { return this->firing; }
	virtual void setOverheat(int32 overheat) { this->overheat = overheat; }
	virtual int32 getOverheat()const { return this->overheat; }
	virtual void setDirection(int32 direction) { this->direction = direction; }
	virtual int32 getDirection()const { return this->direction; }

	virtual void update(double elapsed);
	virtual void render();
private:
	double radius;
	direction movement;
	uint8 status;
	double overheat, direction, firing;
};
#endif