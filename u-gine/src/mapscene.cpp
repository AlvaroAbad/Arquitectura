#include "..\include\mapscene.h"

MapScene::MapScene(Map * map, Image * imageBack, Image * imageFront): ParallaxScene(imageBack,imageFront)
{
	this->map = map;
}

void MapScene::RenderAfterBackground() const
{
	ParallaxScene::RenderAfterBackground();
	map->Render();
}
