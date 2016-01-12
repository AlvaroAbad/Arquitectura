#include "../Headers/appState_menu.h"
#include"../../include/renderer.h"
#include"../../include/resourcemanager.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
#include "../Headers/externs.h"
#include "../Headers/lvlManager.h"
void AppStateMenu::run() {
	if (screen) {
		options.Clear();
		for (uint32 i = 0; i < LevelManager::Instance().getNumLevels(); i++)
		{
			options.Add("Nivel "+(i+1));
		}
		options.Add(MENU_BACK);
	}
	else {
		options.Clear();
		options.Add(MENU_START);
		options.Add(MENU_EXIT);
	}
	escapePoint->Update(Screen::Instance().ElapsedTime());
}

void AppStateMenu::draw() const {
	uint32 posY;
	posY = y;
	Renderer::Instance().SetColor(255, 255, 255, 255);
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	for (uint8 i = 0; i < options.Size(); i++)
	{
		Renderer::Instance().DrawText(font, options[i], x - TEXT_POITION_OFFSET, posY);
		posY += font->GetTextHeight(options[i]);
	}
	Renderer::Instance().DrawImage(selectorImage, x - TEXT_POITION_OFFSET- SELECTOR_WIDTH_HEIGHT, y + (selectedOption*font->GetHeight()),0, SELECTOR_WIDTH_HEIGHT, SELECTOR_WIDTH_HEIGHT);
	escapePoint->Render();
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
					LevelManager::Instance().loadLevel(LevelManager::EASY);
				}
				break;
			case 1:
				if (!screen) {
					whantedState = STATE_NULL;
				}
				else {
					whantedState = STATE_GAME;
					LevelManager::Instance().loadLevel(LevelManager::MEDIUM);
				}
				break;
			case 2:
				whantedState = STATE_GAME;
				LevelManager::Instance().loadLevel(LevelManager::HARD);
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
				if (selectedOption < LevelManager::Instance().getNumLevels()) {
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
	else if (!Screen::Instance().KeyPressed(lasPressed)) {
			ready = true;
	}
}

void AppStateMenu::activate() {
	if (game) {
		delete game;
		game = nullptr;
	}
	String FileName;
	FileName = FONT_DIR;
	font = ResourceManager::Instance().LoadFont(FileName);
	FileName = "data/next.png";
	selectorImage = ResourceManager::Instance().LoadImage(FileName);
	options.Add(MENU_START);
	options.Add(MENU_EXIT);
	ready = true;
	x = Screen::Instance().GetWidth() / 2;
	y = Screen::Instance().GetHeight() / 2;
	escapePoint = new Emitter(ResourceManager::Instance().LoadImage(COLLISIONER_ENEMY_IMG), false);
	escapePoint->SetPosition(x, y);
	escapePoint->SetLifetime(2, 2);
	escapePoint->setScale(0, 5);
	escapePoint->SetAngularVelocity(0, 0);
	escapePoint->SetMinColor(255, 255, 255);
	escapePoint->SetMaxColor(255, 255, 255);
	escapePoint->SetVelocityX(-256, 256);
	escapePoint->SetVelocityY(-256, 256);
	escapePoint->SetRate(1, 1);
	escapePoint->Start();
}

void AppStateMenu::deactivate() {
	delete escapePoint;
}
