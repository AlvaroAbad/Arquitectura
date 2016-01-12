#ifndef UGINE_AFFECTOR_H
#define UGINE_AFFECTOR_H
#include "types.h"
#include "string.h"
class Affector {
public:
	Affector() { 
		affectVelocityX = affectVelocityY = affectAngularVelocity = AffectLifeTime = affectedColor=false;
		minVelocityX= maxVelocityX= minVelocityY= maxVelocityY = minAangularVelocity= maxAngularVelocity = minLifetime= maxLifetime = 0;
	}
	Affector(String id,double bound0X, double bound0Y, double bound1X, double bound1Y);
	
	virtual String getId(){ return this->id; }
	virtual double getBound0X() { return this->bound0X; }
	virtual double getBound0Y() { return this->bound0Y; }
	virtual double getBound1X() { return this->bound1X; }
	virtual double getBound1Y() { return this->bound1Y; }
	virtual bool colorAffected() { return this->affectedColor; }
	virtual void SetMinColor(uint8 r, uint8 g, uint8 b) {
		this->affectedColor = true;
		this->minR = r;
		this->minG = g;
		this->minB = b;
	}
	virtual void SetMaxColor(uint8 r, uint8 g, uint8 b) {
		this->affectedColor = true;
		this->maxR = r;
		this->maxG = g;
		this->maxB = b;
	}
	virtual uint8 getR();
	virtual uint8 getG();
	virtual uint8 getB();

	virtual bool velocityXAffected() { return this->affectVelocityX; }
	virtual void setVelocityX(double minVelocityX, double maxVelocityX) { 
		this->affectVelocityX = true;
		this->minVelocityX = minVelocityX;
		this->maxVelocityX = maxVelocityX;
	}
	virtual double getVelocityX();

	virtual bool velocityYAffected() { return this->affectVelocityY; }
	virtual void setVelocityY(double minVelocityY, double maxVelocityY) {
		this->affectVelocityY = true;
		this->minVelocityY = minVelocityY;
		this->maxVelocityY = maxVelocityY;
	}
	virtual double getVelocityY();

	virtual bool angularVelocityAffected() { 
		return this->affectAngularVelocity; 
	}
	virtual void setAngularVelocity(double minAangularVelocity, double maxAngularVelocity) {
		this->affectAngularVelocity = true;
		this->minAangularVelocity = minAangularVelocity;
		this->maxAngularVelocity = maxAngularVelocity;
	}
	virtual double getAngularVelocity();

	virtual bool lifeTimeAffected() { return this->AffectLifeTime; }
	virtual void setLifeTime(double minLifetime, double maxLifetime) {
		this->AffectLifeTime = true;
		this->minLifetime = minLifetime;
		this->maxLifetime = maxLifetime;
	}
	virtual double getLifeTime();
private:
	String id;
	uint8 minR, maxR, minG, maxG, minB, maxB;
	bool affectVelocityX,affectVelocityY, affectAngularVelocity, AffectLifeTime, affectedColor;
	double bound0X, bound0Y, bound1X, bound1Y;
	double minVelocityX, maxVelocityX, minVelocityY, maxVelocityY;
	double minAangularVelocity, maxAngularVelocity;
	double minLifetime, maxLifetime;
};
#endif
