#include "..\include\affector.h"
#include <stdlib.h>
Affector::Affector(String id,double bound0X, double bound0Y, double bound1X, double bound1Y)
{
	this->id = id;
	this->bound0X = bound0X;
	this->bound0Y = bound0Y;
	this->bound1X = bound1X;
	this->bound1Y = bound1Y;
	affectVelocityX = affectVelocityY = affectAngularVelocity = AffectLifeTime = affectedColor = false;
	minVelocityX = maxVelocityX = minVelocityY = maxVelocityY = minAangularVelocity = maxAngularVelocity = minLifetime = maxLifetime = 0;
}
uint8 Affector::getR()
{
	if (this->maxR == this->minR) {
		return this->maxR;
	}
	else {
		return (rand() % static_cast<unsigned int>(this->maxR + 1 - this->minR)) + this->minR;
	}
}
uint8 Affector::getG()
{
	if (this->maxG == this->minG) {
		return this->maxG;
	}
	else {
		return (rand() % static_cast<unsigned int>(this->maxG + 1 - this->minG)) + this->minG;
	}
}
uint8 Affector::getB()
{
	if (this->maxB == this->minB) {
		return this->maxB;
	}
	else {
		return (rand() % static_cast<unsigned int>(this->maxB + 1 - this->minB)) + this->minB;
	}
}
double Affector::getVelocityX()
{
	if (this->minVelocityX == this->maxVelocityX) {
		return this->maxVelocityX;
	}
	else {
		return (rand() % static_cast<unsigned int>(this->maxVelocityX + 1 - this->minVelocityX)) + this->minVelocityX;
	}
}
double Affector::getVelocityY()
{
	if (this->minVelocityY == this->maxVelocityY) {
		return this->maxVelocityY;
	}
	else {
		return (rand() % static_cast<unsigned int>(this->maxVelocityY + 1 - this->minVelocityY)) + this->minVelocityY;
	}
}

double Affector::getAngularVelocity()
{

	if (this->minAangularVelocity == this->maxAngularVelocity) {
		return this->maxAngularVelocity;
	}
	else {
		return (rand() % static_cast<unsigned int>(this->maxAngularVelocity + 1 - this->minAangularVelocity)) + this->minAangularVelocity;
	}
}
double Affector::getLifeTime()
{
	if (this->minLifetime == this->maxLifetime) {
		return this->maxLifetime;
	}
	else {
		return (rand() % static_cast<unsigned int>(this->maxLifetime + 1 - this->minLifetime)) + this->minLifetime;
	}
}