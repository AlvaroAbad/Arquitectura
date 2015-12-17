#include "../include/camera.h"

Camera::Camera() {
	this->x = 0;
	this->y = 0;
	this->boundx0 = 0;
	this->boundy0 = 0;
	this->boundx1 = 0;
	this->boundy1 = 0;
	this->followingSprite = nullptr;
}

void Camera::Update()
{
	int nextX, nextY;
	if (this->followingSprite) {

		nextX = this->followingSprite->GetScreenX() - Screen::Instance().GetWidth() / 2;
		nextY = this->followingSprite->GetScreenY() - Screen::Instance().GetHeight() / 2;
		if (this->HasBounds()) {
			this->x = nextX;
			this->y = nextY;
		}
		else {
			if (nextX >= this->boundx0 && nextX <= this->boundx1 - Screen::Instance().GetWidth()) {
				this->x = nextX;
			}
			if ( nextY >= this->boundy0 && nextY <= this->boundy1 - Screen::Instance().GetHeight()) {
				this->y = nextY;
			}
		}

	}

}
