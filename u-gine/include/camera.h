#ifndef UGINE_CAMERA_H
#define UGINE_CAMERA_H
#include "sprite.h"
#include "screen.h"
class Camera{
public:
	Camera();
	virtual void SetPosition(double x, double y) {
		this->x = x;
		this->y = y;
	}
	virtual void SetX(double x) { this->x = x; }
	virtual void SetY(double y) { this->y = y; }
	virtual double GetX()const { return this->x; }
	virtual double GetY()const { return this->y; }
	virtual void SetBounds(double bx0, double by0, double bx1, double by1) {
		this->boundx0 = bx0;
		this->boundy0 = by0;
		this->boundx1 = bx1;
		this->boundy1 = by1;
	}
	virtual bool HasBounds()const { return this->boundx0 == this->boundx1; }
	virtual double GetMinX()const { return this->boundx0; }
	virtual double GetMinY()const { return this->boundy0; }
	virtual double GetMaxX()const { return this->boundx1-Screen::Instance().GetWidth(); }
	virtual double GetMaxY()const { return this->boundy1 - Screen::Instance().GetHeight(); }
	virtual void FollowSprite(Sprite*sprite) { this->followingSprite = sprite; }
virtual void Update();
private:
	double x, y;
	double boundx0, boundy0, boundx1, boundy1;
	Sprite * followingSprite;
};
#endif