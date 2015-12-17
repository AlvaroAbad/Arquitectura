#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H
#include "types.h"
class Glyph {
public:
	Glyph() {};
	Glyph(uint32 offsetX, uint32 offsetY, uint32 width, uint32 height);
	void setSize(uint32 width, uint32 height) {
		this->width = width;
		this->height = height;
	}
	void setWidth(uint32 width) { this->width = width; }
	uint32 getWidth() const{ return this->width; }
	void setHeight(uint32 height) { this->height = height; }
	uint32 getHeight() const { return this->height; }
	void setOffset(uint32 offsetX, uint32 offsetY) { 
		this->offsetX = offsetX;
		this->offsetY = offsetY;
	}
	void setOffsetX(uint32 offsetX) { this->offsetX = offsetX; }
	uint32 getOffsetX()const { return this->offsetX; }
	uint32 setOffsetY(uint32 offsetY) { this->offsetY = offsetY; }
	uint32 getOffsetY()const { return this->offsetY; }
private:
	uint32 offsetX;
	uint32 offsetY;
	uint32 height;
	uint32 width;
};
#endif
