#ifndef UGINE_PARTICLE_H
#define UGINE_PARTICLE_H
#include "sprite.h"
#include "affector.h"
class Particle: public Sprite{
public:
	Particle();
	Particle(Image* image, double velx, double vely, double angularVel, double lifetime, bool autofade);
	virtual void setVelocityX(double velocityx) {this->velocityx = velocityx;}
	virtual void setVelocityY(double velocityy) { this->velocityy = velocityy; }
	virtual void setAngularVelocity(double angularVelocity) { this->angularVelocity = angularVelocity; }
	virtual void setLifetime(double lifetime) { 
		this->lifetime = lifetime-(this->initialLifetime-this->lifetime);
		this->initialLifetime = lifetime; 
	}
	virtual double GetLifetime()const { return this->lifetime; };
	virtual void Update(double elapsed);
	virtual bool isAffectable() {
		return !this->affected;
	}
	virtual void affect() { this->affected=true; };
private:
	double velocityx,velocityy;
	double angularVelocity;
	double lifetime;
	double initialLifetime;
	bool autofade;
	bool affected;
};

#endif