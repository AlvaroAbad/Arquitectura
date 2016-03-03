#include "math.h"
#include <math.h>
#include "..\include\math.h"

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

double Log2(double x) {
	return log(x) / log(2.0);
}

double DegSin(double degrees) {
	return sin(DEG2RAD * degrees);
}

double DegCos(double degrees) {
	return cos(DEG2RAD * degrees);
}

double DegTan(double degrees) {
	return tan(DEG2RAD * degrees);
}

double DegASin(double sin) {
	return asin(sin) * RAD2DEG;
}

double DegACos(double cos) {
	return acos(cos) * RAD2DEG;
}

double DegATan(double tan) {
	return atan(tan) * RAD2DEG;
}

double DegATan2(double y, double x) {
	return atan2(y, x) * RAD2DEG;
}

double WrapValue(double val, double mod) {
	if (mod == 0) return val;
	return val - mod*floor(val / mod);
}


double Angle(double x1, double y1, double x2, double y2) {
	return WrapValue(DegATan2(y1 - y2, x2 - x1), 360);
}

double Distance(double x1, double y1, double x2, double y2) {
	double x, y;
	x = x2 - x1;
	y = y2 - y1;
	double distance = sqrt((x*x) + (y*y));
	return distance;
}

bool ValueInRange(double value, double min, double max) {
	return (value >= min) && (value <= max);
}

bool PointInRect(double x, double y, double rectx, double recty, double width, double height) {
	return(ValueInRange(x, rectx, rectx + width) && ValueInRange(y, recty, recty + height));
}

void ClosestPointToRect(double x, double y, double rectx, double recty, double width, double height, double* outx, double* outy) {
	*outx = (x < rectx) ? rectx : (x > rectx + width) ? rectx + width : x;
	*outy = (y < recty) ? recty : (y > recty + height) ? recty + height : y;
}

bool RectsOverlap(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2) {
	bool xOverlap1 = ValueInRange(x1, x2, x2 + width2) || ValueInRange(x1 + width1, x2, x2 + width2);
	bool yOverlap1 = ValueInRange(y1, y2, y2 + height2) || ValueInRange(y1 + height1, y2, y2 + height2);
	bool xOverlap2 = ValueInRange(x2, x1, x1 + width1) || ValueInRange(x2 + width2, x1, x1 + width1);
	bool yOverlap2 = ValueInRange(y2, y1, y1 + height1) || ValueInRange(y2 + height2, y1, y1 + height1);
	return (xOverlap1 && yOverlap1) || (xOverlap2 && yOverlap2);
}

void OverlappingRect(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2, double* outx, double* outy, double* outwidth, double* outheight) {
	if (ValueInRange(x1, x2, x2 + width2)) {
		*outx = x1;
	}
	else {
		*outx = x2;
	}
	if (ValueInRange(y1, y2, y2 + height2)) {
		*outy = y1;
	}
	else {
		*outy = y2;
	}
	if (ValueInRange(x1 + width1, x2, x2 + width2)) {
		*outwidth = x1 + width1 - *outx;
	}
	else {
		*outwidth = x2 + width2 - *outx;
	}
	if (ValueInRange(y1 + height1, y2, y2 + height2)) {
		*outheight = y1 + height1 - *outy;
	}
	else {
		*outheight = y2 + height2 - *outy;
	}
}

bool RayRectOverlap(double rayOX, double rayOY, double rayDX, double rayDY, double RectX, double RectY, double RectWidth, double RectHeight)
{
	double tlAngle, brAngle, trAngle, blAngle, lineAngle;
	double tlDistance, brDistance, trDistance, blDistance, lineDistance;

	tlDistance = Distance(RectX, RectY, rayOX, rayOY);
	brDistance = Distance(RectX + RectWidth, rayOY + RectHeight, rayOX, rayOY);
	trDistance = Distance(RectX + RectWidth, rayOY, rayOX, rayOY);
	blDistance = Distance(RectX, rayOY + RectHeight, rayOX, rayOY);
	lineDistance = Distance(rayDX, rayDY, rayOX, rayOY);
	if (lineDistance > tlDistance
		|| lineDistance > brDistance
		|| lineDistance > trDistance
		|| lineDistance > blDistance) {

		tlAngle = Angle(RectX, RectY, rayOX, rayOY);
		brAngle = Angle(RectX + RectWidth, rayOY + RectHeight, rayOX, rayOY);
		trAngle = Angle(RectX + RectWidth, rayOY, rayOX, rayOY);
		blAngle = Angle(RectX, rayOY + RectHeight, rayOX, rayOY);
		lineAngle = Angle(rayDX, rayDY, rayOX, rayOY);
		return ((blAngle >= lineAngle && trAngle <= lineAngle) || (tlAngle >= lineAngle && brAngle <= lineAngle));
	}
	else {
		return false;
	}

}

void TransformIsoCoords(double isoX, double isoY, double isoZ, double* screenX, double* screenY) {
	*screenX = (isoX - isoY) * DegCos(26.6);
	*screenY = isoZ + (isoX + isoY) * DegSin(26.6);
}
