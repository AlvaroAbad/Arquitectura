#include "..\include\isometricsprite.h"
#include "../include/math.h"
#include "../include/image.h"
#include <math.h>
void IsometricSprite::SetPosition(double x, double y, double z)
{
	Sprite::SetPosition(x, y, z);
}
void IsometricSprite::SetCollision(CollisionMode mode)
{
	(mode != CollisionMode::COLLISION_PIXEL ? Sprite::SetCollision(mode) : Sprite::SetCollision(CollisionMode::COLLISION_RECT));
}
void IsometricSprite::Update(double elapsed, const Map * map)
{
	Sprite::Update(elapsed, map);
	TransformIsoCoords(GetX(), GetY(), GetZ(), &screenX, &screenY);

}

void IsometricSprite::UpdateCollisionBox()
{
	double x, y, w, h,cx,cy;
	x = GetX() - GetImage()->GetHandleX() *fabs(GetScaleX());
	y = GetY() - GetImage()->GetHandleX() *fabs(GetScaleY());
	w = GetImage()->GetWidth()*fabs(GetScaleX());
	h = GetImage()->GetWidth()*fabs(GetScaleX());
	cx = x + w / 2;
	cy = y + h / 2;
	Sprite::UpdateCollisionBox(x, y, w, h, cx, cy);

}
