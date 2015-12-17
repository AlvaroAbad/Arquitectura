#include "../Headers/appState_menu.h"
#include"../../include/renderer.h"
#include"../../include/resourcemanager.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
#include "../Headers/externs.h"
void AppStateMenu::run(){
	this->x = Screen::Instance().GetWidth() / 2;
	this->y = Screen::Instance().GetHeight() / 2;
}

void AppStateMenu::draw() const{
	uint32 posY;
	posY = this->y;
	Renderer::Instance().SetColor(255, 255, 255, 255);
	for (uint8 i = 0; i < this->options.Size(); i++)
	{
		Renderer::Instance().DrawText(font, options[i], this->x-this->font->GetTextWidth(this->options[i])/2, posY);
		posY += this->font->GetTextHeight(options[i]);
	}
}

void AppStateMenu::getInputs() const{
	if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		whantedState = STATE_NULL;
	}
	else if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
		whantedState = STATE_GAME;
	}
}

void AppStateMenu::activate(){
	if (game) {
		delete game;
	}
	String fontFileName;
	fontFileName = "data/arial16.png";
	font = ResourceManager::Instance().LoadFont(fontFileName);
	this->options.Add("Start(enter)");
	this->options.Add("Exit(Esc)");
}

void AppStateMenu::deactivate(){

}
