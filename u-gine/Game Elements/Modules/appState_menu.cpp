#include "../Headers/appState_menu.h"
#include"../../include/renderer.h"
#include"../../include/resourcemanager.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
#include "../Headers/externs.h"
void AppStateMenu::run() {
	this->x = Screen::Instance().GetWidth() / 2;
	this->y = Screen::Instance().GetHeight() / 2;
	if (screen) {
		this->options.Clear();
		this->options.Add("Nivel 1");
		this->options.Add("Nivel 2");
		this->options.Add("Nivel 3");
		this->options.Add("Back");
	}
	else {
		this->options.Clear();
		this->options.Add("Start");
		this->options.Add("Exit");
	}
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
	if (ready) {
		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
			ready = false;
			lasPressed= GLFW_KEY_ENTER;
			switch (selectedOption) {
			case 0:
				if (!screen) {
					screen++;
					selectedOption = 0;
				}
				else {
					whantedState = STATE_GAME;
					lvlFile = "data/basic.txt";
				}
				break;
			case 1:
				if (!screen) {
					whantedState = STATE_NULL;
				}
				else {
					whantedState = STATE_GAME;
					lvlFile = "data/medium.txt";
				}
				break;
			case 2:
				whantedState = STATE_GAME;
				lvlFile = "data/hard.txt";
				break;
			case 3:
				screen--;
				selectedOption = 0;
				break;
			}
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			ready = false;
			lasPressed = GLFW_KEY_DOWN;
			if (!screen) {
				if (selectedOption < 1) {
					selectedOption++;
				}
			}
			else {
				if (selectedOption < 3) {
					selectedOption++;
				}
			}
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			ready = false;
			lasPressed = GLFW_KEY_UP;
			if (selectedOption) {
				selectedOption--;
			}
		}
	}
	else {
		if (!Screen::Instance().KeyPressed(lasPressed)) {
			ready = true;
		}
	}
}

void AppStateMenu::activate() {
	if (game) {
		delete game;
		game = nullptr;
	}
	String FileName;
	FileName = "data/arial16.png";
	font = ResourceManager::Instance().LoadFont(FileName);
	FileName = "data/next.png";
	selectorImage = ResourceManager::Instance().LoadImage(FileName);
	this->options.Add("Start");
	this->options.Add("Exit");
	ready = true;
}

void AppStateMenu::deactivate() {

}
