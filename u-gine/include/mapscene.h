#ifndef UGINE_MAPSCENE_H
#define UGINE_MAPSCENE_H
#include "map.h"
#include "parallaxscene.h"
class MapScene:public ParallaxScene{
public:
	MapScene(Map* map,Image* imageBack = 0,Image* imageFront = 0);
	virtual const Map* GetMap()const { return this->map; }
	virtual void Update(double elapsed) { ParallaxScene::Update(elapsed,this->map); }
protected:
	virtual void RenderAfterBackground()const;
private:
	Map* map;
};
#endif
