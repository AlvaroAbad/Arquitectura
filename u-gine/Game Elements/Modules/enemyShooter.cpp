#include "..\Headers\enemyShooter.h"
#include "../../include/screen.h"
void EnemyShooter::update(double elapsed){
	Sprite * sprite = this->getSprite();
	sprite->SetX(sprite->GetX() + elapsed*this->getSpeedX());
	sprite->SetY(sprite->GetY() + elapsed*this->getSpeedY());
	if (sprite->GetY() >= Screen::Instance().GetHeight() / 2) {
		sprite->SetY(Screen::Instance().GetHeight() / 2);
		this->setSpeedY(this->getSpeedY() * -1);
	}
	else if (sprite->GetY() < 0-this->getHeight()) {
		this->kill();
	}
	if (sprite->GetX() >= Screen::Instance().GetWidth() || sprite->GetX() <= 0) {
		this->setSpeedX(this->getSpeedX() * -1);
	}
}

