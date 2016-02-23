#include "../include/parallaxscene.h"
ParallaxScene::ParallaxScene(Image * imageBack, Image * imageFront){
	this->backLayer = imageBack;
	this->frontLayer = imageFront;
	this->backX=0;
	this->backY = 0;
	this->frontX = 0;
	this->frontY = 0;
	this->relBackSpeedX = 0.5;
	this->relBackSpeedY = 0.5;
	this->relFrontSpeedX = 1;
	this->relFrontSpeedY = 1;
	this->autoBackSpeedX = 0.25;
	this->autoBackSpeedY = 0.25;
	this->autoFrontSpeedX = 0.5;
	this->autoFrontSpeedY = 0.5;
}
void ParallaxScene::Update(double elapsed, Map * map){
	Scene::Update(elapsed, map);
	this->backX += this->autoBackSpeedX*elapsed;
	this->backY += this->autoBackSpeedY*elapsed;
	this->frontX += this->autoFrontSpeedX*elapsed;
	this->frontY += this->autoFrontSpeedY*elapsed;

}
void ParallaxScene::RenderBackground() const{
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	if(this->backLayer){
	Renderer::Instance().DrawTiledImage(this->backLayer,0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), this->GetCamera().GetX()*this->relBackSpeedX  - this->backX, this->GetCamera().GetY()*this->relBackSpeedY - this->backY);
	}
	if(this->frontLayer){
	Renderer::Instance().DrawTiledImage(this->frontLayer,0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), this->GetCamera().GetX()*this->relFrontSpeedX- this->frontX, this->GetCamera().GetY()*this->relFrontSpeedY- this->frontY);
	}
}