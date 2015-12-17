#include "..\Headers\enemyCollisioner.h"

void EnemyCollisioner::update(double elapsed)
{
	Sprite * sprite = this->getSprite();
	sprite->SetX(sprite->GetX() + elapsed*this->getSpeed());
	if (sprite->GetX() <= 0-this->getWidth()) {
		this->kill();
	}
}
