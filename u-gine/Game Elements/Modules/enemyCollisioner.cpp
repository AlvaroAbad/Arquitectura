#include "..\Headers\enemyCollisioner.h"

void EnemyCollisioner::update(double elapsed)
{
	Sprite * sprite = getSprite();
	sprite->SetX(sprite->GetX() + elapsed*speed);
	if (sprite->GetX() <= 0-getWidth()) {
		kill();
	}
}
