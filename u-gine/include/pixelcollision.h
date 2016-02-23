#ifndef UGINE_PIXEL_COLLISION_H
#define UGINE_PIXEL_COLLISION_H

#include "collision.h"
#include "../include/collisionmanager.h"
#include "string.h"
#include "resourcemanager.h"

class PixelCollision : public Collision {
public:
	PixelCollision(String image, double* x, double* y) : x(x), y(y){
		pixels = ResourceManager::Instance().LoadCollisionPixelData(image);
	}
	PixelCollision(const CollisionPixelData* pixels, double* x, double* y) :pixels(pixels), x(x), y(y) {}
	virtual bool DoesCollide(const Collision* other) const { return other->DoesCollide(pixels,*x, *y); }
	virtual bool DoesCollide(double cx, double cy, double cradius) const { return CollisionManager::Instance().CircleToPixels(cx, cy, cradius, pixels, *x, *y); }
	virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const { return CollisionManager::Instance().PixelsToRect(pixels, *x, *y, rx, ry, rwidth, rheight); }
	virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const { return CollisionManager::Instance().PixelsToPixels(pixels, px, py, pixels, *x, *y); }
private:
	const CollisionPixelData* pixels;
	double* x;
	double* y;
};

#endif
