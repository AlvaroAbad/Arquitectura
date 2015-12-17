#ifndef UGINE_PARALLAXSCENE_H
#define UGINE_PARALLAXSCENE_H
#include "scene.h"
class ParallaxScene :public Scene {
public:
	ParallaxScene(Image* imageBack, Image* imageFront = 0);
	virtual const Image* GetBackLayer()const { return this->backLayer; }
	virtual const Image* GetFrontLayer()const { return this->frontLayer; }
	virtual void SetRelativeBackSpeed(double x, double y) {
		this->relBackSpeedX = x;
		this->relBackSpeedY = y;
	}
	virtual void SetRelativeFrontSpeed(double x, double y) {
		this->relFrontSpeedX = x;
		this->relFrontSpeedY = y;
	}
	virtual void SetAutoBackSpeed(double x, double y) {
		this->autoBackSpeedX = x;
		this->autoBackSpeedY = y;
	}
	virtual void SetAutoFrontSpeed(double x, double y) {
		this->autoFrontSpeedX = x;
		this->autoFrontSpeedY = y;
	}
	virtual void Update(double elapsed, Map*map = 0);
protected:
	virtual void RenderBackground()const;
private:
	Image*backLayer;
	Image*frontLayer;
	double backX, backY;
	double frontX, frontY;
	double relBackSpeedX, relBackSpeedY;
	double relFrontSpeedX, relFrontSpeedY;
	double autoBackSpeedX, autoBackSpeedY;
	double autoFrontSpeedX, autoFrontSpeedY;
};
#endif