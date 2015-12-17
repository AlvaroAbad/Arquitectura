#ifndef WORLDDEFENDER_ENEMY_H
#define WORLDDEFENDER_ENEMY_H
#include "../../include/string.h"
#include "../../include/sprite.h"
#include "../../include/image.h"
class Entity{
public:
	Entity(Image *image, String id, double x, double y, double height, double width) :id(id), x(x), y(y), height(height), width(width) {
		this->sprite = new Sprite(image);
		this->sprite->SetPosition(x, y);
		this->sprite->SetScale(width / this->sprite->GetImage()->GetWidth(), height / this->sprite->GetImage()->GetHeight());
		this->dead = false;
	};
	~Entity() { delete(sprite); }
	//Position setters and getters
	virtual void setX(double x) { this->sprite->SetX(x); }
	virtual double getX()const { return this->sprite->GetX(); }
	virtual void setY(double y) { this->sprite->SetY(y); }
	virtual double getY()const { return this->sprite->GetY();}
	virtual void setHeight(double height) { 
		this->height = height;
		this->sprite->SetScaleY(height / this->sprite->GetImage()->GetHeight());
	}
	virtual double getHeight()const { return this->height; }
	virtual void setWidth(double width) { this->width = width;
	this->sprite->SetScaleX(width / this->sprite->GetImage()->GetWidth());
	}
	virtual double getWidth()const {return this->width;	}
	virtual bool isDead() const { return this->dead; }
	virtual void kill() { this->dead = true; }

	virtual void setColor(uint8 r, uint8 g, uint8 b) {
		this->sprite->SetColor(r, g, b, 255);
	}

	//Game Methods
	virtual void update(double elapsed) = 0;
	virtual void render() {
			this->sprite->Render();
	}
	bool operator==(const Entity& rhs) {
				return this->id == rhs.id;
		}
	virtual char getType() { return this->id[0]; }
protected:
	virtual Sprite * getSprite() { return this->sprite; }
private:
	String id;
	double x,y, height, width;
	Sprite *sprite;
	bool dead;
};
#endif
