#include "..\include\collisionmanager.h"
#include "..\include\math.h"

CollisionManager* CollisionManager::manager = nullptr;

CollisionManager & CollisionManager::Instance()
{
	if (!manager) {
		manager=new CollisionManager();
	}
	return *manager;
}

bool CollisionManager::CircleToCircle(double x1, double y1, double r1, double x2, double y2, double r2) const
{
	double centerX1, centerY1, centerX2, centerY2;
	double distC;
	distC=Distance(x1, y1, x2, y2);
	if (r1 + r2 >= distC) {
		return true;
	}
	else {
		return false;
	}
}

bool CollisionManager::CircleToPixels(double cx, double cy, double cr, const CollisionPixelData * pixels, double px, double py) const
{
	double overlapRectX, overlapRectY, overlapRectW, overlapRectH;
	double x, y;
	//check overlap
	if (RectsOverlap(cx-cr, cy-cr, cr*2, cr*2, px, py, pixels->GetWidth(), pixels->GetHeight())) {
		//get overlapingRect
		OverlappingRect(cx-cr, cy-cr, cr * 2, cr * 2, px, py, pixels->GetWidth(), pixels->GetHeight(), &overlapRectX, &overlapRectY, &overlapRectW, &overlapRectH);
		//reference coords
		x = overlapRectX;
		y = overlapRectY;

		//cicle through pixels
		bool collision = false;
		while (!collision && y < (overlapRectY + overlapRectH))
		{
			while (!collision && x <(overlapRectX + overlapRectW))
			{
				collision = pixels->GetData(x - px, y - py) && Distance(x, y, cx, cy) < cr;
				x++;
			}
			y++;
			x = overlapRectX;
		}
		return collision;
	}
	else {
return false;
	}

	
}

bool CollisionManager::CircleToRect(double cx, double cy, double cr, double rx, double ry, double rw, double rh) const
{
	double closestX, closestY;
	ClosestPointToRect(cx, cy, rx, ry, rw, rh, &closestX, &closestY);
	if (Distance(cx, cy, closestX, closestY) <= cr) {
		return true;
	}
	else {
		return false;
	}
}

bool CollisionManager::PixelsToPixels(const CollisionPixelData * p1, double x1, double y1, const CollisionPixelData * p2, double x2, double y2) const
{
	double overlapRectX, overlapRectY, overlapRectW, overlapRectH;
	double x, y, p1x, p1y, p2x, p2y;
	if(RectsOverlap(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight())){
	OverlappingRect(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight(), &overlapRectX, &overlapRectY, &overlapRectW, &overlapRectH);
	x = overlapRectX;
	y = overlapRectY;

	bool collision = false;
	while (!collision && y < (overlapRectY + overlapRectH))
	{
		while (!collision && x <(overlapRectX + overlapRectW))
		{
			collision = (p1->GetData(x - x1, y - y1) && p2->GetData(x - x2, y - y2));
			x++;
		}
		y++;
		x = overlapRectX;
	}
	return collision;
	}
	else {
		return false;
	}
}

bool CollisionManager::PixelsToRect(const CollisionPixelData * pixels, double px, double py, double rx, double ry, double rw, double rh) const
{
	double overlapRectX, overlapRectY, overlapRectW, overlapRectH,x,y;
	if (RectsOverlap(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh)) {
		OverlappingRect(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh, &overlapRectX, &overlapRectY, &overlapRectW, &overlapRectH);
		x = overlapRectX;
		y = overlapRectY;

		bool collision = false;
		while (!collision && y < (overlapRectY + overlapRectH))
		{
			while (!collision && x <(overlapRectX + overlapRectW))
			{
				collision = pixels->GetData(x - px, y - py);
				x++;
			}
			y++;
			x = overlapRectX;
		}
		return collision;
	}
	else {
return false;
	}
	
}

bool CollisionManager::RectToRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) const
{
	return RectsOverlap(x1, y1, w1, h1, x2, y2, w2, h2);
}
