#include "../Headers/appState_menu.h"
#include"../../include/renderer.h"
#include"../../include/resourcemanager.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
#include "../Headers/externs.h"
void AppStateMenu::run() {
	this->x = Screen::Instance().GetWidth() / 2;
	this->y = Screen::Instance().GetHeight() / 2;
}

void AppStateMenu::draw() const {
	uint32 posY;
	posY = this->y;
	Renderer::Instance().SetColor(255, 255, 255, 255);
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	for (uint8 i = 0; i < this->options.Size(); i++)
	{
		Renderer::Instance().DrawText(font, options[i], this->x - this->font->GetTextWidth(this->options[i]) / 2, posY);
		posY += this->font->GetTextHeight(options[i]);
	}
	Renderer::Instance().DrawImage(selectorImage, x - 70, y + (selectedOption*font->GetHeight()),0,16,16);
}

void AppStateMenu::getInputs() {
	if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
		switch(selectedOption) {
		case 0:
			whantedState = STATE_GAME;
			break;
		case 1:
			whantedState = STATE_NULL;
			break;
		case 2:
			break;
		}
	}
	else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
		if (!screen){
			if (selectedOption < 1) {
				selectedOption++;
			}
	}
	else {
		if (selectedOption < 2) {
			selectedOption++;
		}
	}
	}
	else if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
		if (selectedOption) {
			selectedOption--;
		}
	}
}

void AppStateMenu::activate() {
	if (game) {
		delete game;
	}
	String FileName;
	FileName = "data/arial16.png";
	font = ResourceManager::Instance().LoadFont(FileName);
	FileName = "data/next.png";
	selectorImage = ResourceManager::Instance().LoadImage(FileName);
	this->options.Add("Start(enter)");
	this->options.Add("Exit(Esc)");
}

void AppStateMenu::deactivate() {

}
