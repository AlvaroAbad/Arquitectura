//#include "..\Headers\enemyShooter.h"
//#include "../../include/screen.h"
//void EnemyShooter::update(double elapsed){
//	if (cooldown) {
//		cooldown -= elapsed;
//		if (cooldown < 0) {
//			cooldown = 0;
//		}
//	}
//	Sprite * sprite = getSprite();
//	sprite->SetX(sprite->GetX() + elapsed*getSpeedX());
//	sprite->SetY(sprite->GetY() + elapsed*getSpeedY());
//	if (sprite->GetY() >= Screen::Instance().GetHeight() / 2) {
//		sprite->SetY(Screen::Instance().GetHeight() / 2);
//		setSpeedY(getSpeedY() * -1);
//	}
//	else if (sprite->GetY() < 0) {
//		kill();
//	}
//	if (sprite->GetX() >= Screen::Instance().GetWidth() || sprite->GetX() <= 0) {
//		setSpeedX(getSpeedX() * -1);
//	}
//}

