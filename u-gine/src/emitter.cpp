#include "..\include\emitter.h"
Emitter::Emitter(Image * image, bool autofade)
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
}

void Emitter::Update(double elapsed)
{
	uint8 r, g, b;
	for (uint32 i = 0;i < this->particles.Size();i++) {
		if (this->maxr == this->minr) {
			r = this->maxr;
		}
		else {
			r = (rand() % static_cast<unsigned int>(this->maxr - this->minr)) + this->minr;
		}
		if (this->maxg == this->ming) {
			g = this->maxg;
		}
		else {
			g = (rand() % static_cast<unsigned int>(this->maxg - this->ming)) + this->ming;
		}
		if (this->maxb == this->minb) {
			b = this->maxb;
		}
		else {
			b = (rand() % static_cast<unsigned int>(this->maxb - this->minb)) + this->minb;
		}
		this->particles[i].SetColor(r, g, b, this->particles[i].GetAlpha());
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
			rate = (rand() % static_cast<unsigned int>(this->maxrate - this->minrate)) + this->minrate;
		}
		
		rate = rate*elapsed;
		for (uint32 i = 0; i < rate;i++)
		{
			if (this->maxvelx == this->minvelx) {
				velX = this->maxvelx;
			}
			else {
				velX = (rand() % static_cast<unsigned int>(this->maxvelx - this->minvelx)) + this->minvelx;
			}
			if (this->maxvely == this->minvely) {
				velY = this->maxvely;
			}
			else {
				velY = (rand() % static_cast<unsigned int>(this->maxvely - this->minvely)) + this->minvely;
			}

			if (this->maxangvel == this->minangvel) {
				angVel = this->maxangvel;
			}
			else {
				angVel = (rand() % static_cast<unsigned int>(this->maxangvel - this->minangvel)) + this->minangvel;
			}
			if (this->maxlifetime == this->minlifetime) {
				lifeTime = this->maxlifetime;
			}
			else {
				lifeTime = (rand() % static_cast<unsigned int>(this->maxlifetime - this->minlifetime)) + this->minlifetime;
			}
			if (this->maxr == this->minr) {
				r = this->maxr;
			}
			else {
				r = (rand() % static_cast<unsigned int>(this->maxr - this->minr)) + this->minr;
			}
			if (this->maxg == this->ming) {
				g = this->maxg;
			}
			else {
				g = (rand() % static_cast<unsigned int>(this->maxg - this->ming)) + this->ming;
			}
			if (this->maxb == this->minb) {
				b = this->maxb;
			}
			else {
				b = (rand() % static_cast<unsigned int>(this->maxb - this->minb)) + this->minb;
			}
			this->particles.Add(Particle(this->image, velX, velY, angVel, lifeTime, this->autofade));
			this->particles.Last().SetPosition(this->x, this->y);
			this->particles.Last().SetColor(r, g, b, 255);
			this->particles.Last().SetBlendMode(this->blendMode);
		}
	}
}

void Emitter::Render() const
{
	for (uint32 i = 0;i < this->particles.Size();i++) {
		this->particles[i].Render();
	}
}
