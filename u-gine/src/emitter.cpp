#include "..\include\emitter.h"
Emitter::Emitter(Image * image, bool autofade, uint32 particlesMaxAffectors)
{
	this->image = image;
	this->autofade = autofade;
	this->x = 0;
	this->y = 0;
	this->minrate = 0;
	this->maxrate = 100;
	this->minvelx = 0;
	this->maxvelx = 100;
	this->minvely = 0;
	this->maxvely = 100;
	this->minangvel = 0;
	this->maxangvel = 100;
	this->minlifetime = 0;
	this->maxlifetime = 100;
	this->minr = 0;
	this->ming = 0;
	this->minb = 0;
	this->maxr = 255;
	this->maxg = 255;
	this->maxb = 255;
	this->blendMode = Renderer::ADDITIVE;
	this->emitting = false;
	this->acumulative = 0;
}

Affector * Emitter::getAffector(String id)
{
	uint32 numAffector = 0;
	while (affectors.Size()>numAffector && affectors[numAffector].getId() != id) {
		numAffector++;
	}
	if (affectors.Size() > numAffector) {
		return &(affectors[numAffector]);
	}
	return nullptr;
}

void Emitter::Update(double elapsed)
{
	uint8 r, g, b,a;
	uint32 affector;
	for (uint32 i = 0;i < this->particles.Size();i++) {
		affector = 0;
		while (affectors.Size() > affector && particles[i].isAffectable()) {
				if (particles[i].GetX() >= affectors[affector].getBound0X() && particles[i].GetX() <= affectors[affector].getBound1X()) {
					if (particles[i].GetY() >= affectors[affector].getBound0Y() && particles[i].GetY() <= affectors[affector].getBound1Y()) {
						double LifeTime;
						if (affectors[affector].velocityXAffected()) {
							particles[i].setVelocityX(affectors[affector].getVelocityX());
						}
						if (affectors[affector].velocityYAffected()) {
							particles[i].setVelocityY(affectors[affector].getVelocityY());
						}
						if (affectors[affector].angularVelocityAffected()) {
							particles[i].setAngularVelocity(affectors[affector].getAngularVelocity());
						}
						if (affectors[affector].lifeTimeAffected()) {
							LifeTime = affectors[affector].getLifeTime();

							particles[i].setLifetime(LifeTime);
						}
						if (affectors[affector].colorAffected()) {
							r= affectors[affector].getR();
							g= affectors[affector].getG();
							b= affectors[affector].getB();
							if (affectors[affector].lifeTimeAffected()) {
								a = 255*(1-(particles[i].GetLifetime() / LifeTime));
							}
							else {
								a = particles[i].GetAlpha();
							}
							
							particles[i].SetColor(r,g,b,a);
						}
						particles[i].affect();
					}
				}
			affector++;
		}
		this->particles[i].Update(elapsed);
		if (!this->particles[i].GetAlpha()) {
			this->particles.RemoveAt(i);
		}
	}
	if (this->emitting) {
		double velX, velY, angVel, lifeTime, rate;
		if (this->maxrate == this->minrate) {
			rate = this->maxrate;
		}
		else {
			rate = (rand() % static_cast<unsigned int>(this->maxrate + 1 - this->minrate)) + this->minrate;
		}

		rate = rate*elapsed;
		rate += acumulative;
		acumulative = rate-static_cast<uint32>(rate);
		for (uint32 i = 0; i < static_cast<uint32>(rate);i++)
		{
			if (this->maxvelx == this->minvelx) {
				velX = this->maxvelx;
			}
			else {
				velX = (rand() % static_cast<unsigned int>(this->maxvelx+1 - this->minvelx)) + this->minvelx;
			}
			if (this->maxvely == this->minvely) {
				velY = this->maxvely;
			}
			else {
				velY = (rand() % static_cast<unsigned int>(this->maxvely + 1 - this->minvely)) + this->minvely;
			}

			if (this->maxangvel == this->minangvel) {
				angVel = this->maxangvel;
			}
			else {
				angVel = (rand() % static_cast<unsigned int>(this->maxangvel + 1 - this->minangvel)) + this->minangvel;
			}
			if (this->maxlifetime == this->minlifetime) {
				lifeTime = this->maxlifetime;
			}
			else {
				lifeTime = (rand() % static_cast<unsigned int>(this->maxlifetime + 1 - this->minlifetime)) + this->minlifetime;
			}
			if (this->maxr == this->minr) {
				r = this->maxr;
			}
			else {
				r = (rand() % static_cast<unsigned int>(this->maxr + 1 - this->minr)) + this->minr;
			}
			if (this->maxg == this->ming) {
				g = this->maxg;
			}
			else {
				g = (rand() % static_cast<unsigned int>(this->maxg + 1 - this->ming)) + this->ming;
			}
			if (this->maxb == this->minb) {
				b = this->maxb;
			}
			else {
				b = (rand() % static_cast<unsigned int>(this->maxb + 1 - this->minb)) + this->minb;
			}
			this->particles.Add(Particle(this->image, velX, velY, angVel, lifeTime, this->autofade));
			this->particles.Last().SetPosition(this->x, this->y);
			this->particles.Last().SetColor(r, g, b, 255);
			this->particles.Last().SetBlendMode(this->blendMode);
			this->particles.Last().setScaleTransformation(this->minScale, this->maxScale);
		}
	}
}

void Emitter::Render() const
{
	for (uint32 i = 0;i < this->particles.Size();i++) {
			this->particles[i].Render();
	}
}
