#include "..\include\isometricscene.h"
#include "../include/array.h"
#include "../include/isometricmap.h"

IsometricScene::IsometricScene(IsometricMap * map, Image * imageBack, Image * imageFront): MapScene(map,imageBack,imageFront)
{
	map->GenerateLayerSprites(this);
}

IsometricSprite * IsometricScene::CreateSprite(Image * image, Layer layer)
{
	IsometricSprite* spr = new IsometricSprite(image);
	AddSprite(spr, layer);
	return spr;
}

void IsometricScene::Update(double elapsed)
{
	MapScene::Update(elapsed);
	for (int i = 0; i < LAYER_COUNT; i++) {
		GetSprites((Layer)i).Sort(&CompareSprites);
	}
}

bool IsometricScene::CompareSprites(Sprite *& first, Sprite *& second)
{
	if (first->GetScreenY() <= second->GetScreenY()) {
		if (first->GetScreenY() == second->GetScreenY()) {
			if (first->GetScreenX() == second->GetScreenX()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
		
	}
	else {
		return false;
	}
}
