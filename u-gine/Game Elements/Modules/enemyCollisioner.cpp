#include "..\Headers\enemyCollisioner.h"

void EnemyCollisioner::update(double elapsed)
{
	Sprite * sprite = getSprite();
	sprite->SetX(sprite->GetX() + elapsed*getSpeed());
	if (sprite->GetX() <= 0-getWidth()) {
		kill();
	}
}
