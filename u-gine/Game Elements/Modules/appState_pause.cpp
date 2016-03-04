#include "..\Headers\appState_pause.h"
#include"../../include/renderer.h"
#include"../../include/resourcemanager.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
#include "../Headers/externs.h"
#include "../Headers/languagemanager.h"

void AppStatePause::run()
{
	
}

void AppStatePause::draw() const
{
	game->draw();
	uint32 posY;
	posY = y;
	Renderer::Instance().SetColor(204, 204, 204, 128);
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	Renderer::Instance().DrawRect(0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
	Renderer::Instance().SetColor(255, 0, 0, 255);
	for (uint8 i = 0; i < options.Size(); i++)
	{
		Renderer::Instance().DrawText(font, options[i], x - TEXT_POITION_OFFSET, posY);
		posY += font->GetTextHeight(options[i]);
	}
	Renderer::Instance().SetColor(255, 255, 255, 255);
	Renderer::Instance().DrawImage(selectorImage, x - TEXT_POITION_OFFSET - SELECTOR_WIDTH_HEIGHT, y + (selectedOption*font->GetHeight()), 0, SELECTOR_WIDTH_HEIGHT, SELECTOR_WIDTH_HEIGHT);
}

void AppStatePause::getInputs()
{
	if (ready) {
		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
			ready = false;
			lasPressed = GLFW_KEY_ENTER;
			switch (selectedOption) {
			case 0:
				whantedState = STATE_GAME;
				break;
			case 1:
				whantedState = STATE_MENU;
				break;
			case 2:
				whantedState = STATE_NULL;
				break;
			}
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			ready = false;
			lasPressed = GLFW_KEY_DOWN;
			if (selectedOption < 2) {
				selectedOption++;
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

void AppStatePause::activate()
{
	String FileName;
	FileName = FONT_DIR;
	font = ResourceManager::Instance().LoadFont(FileName);
	FileName = "data/next.png";
	selectorImage = ResourceManager::Instance().LoadImage(FileName);
	options.Add(LanguageManager::Instance().GetString("LANG_CONTINUE", 0));
	options.Add(LanguageManager::Instance().GetString("LANG_MENU", 0));
	options.Add(LanguageManager::Instance().GetString("LANG_EXIT", 0));
	ready = true;
	x = Screen::Instance().GetWidth() / 2;
	y = Screen::Instance().GetHeight() / 2;
}

void AppStatePause::deactivate()
{
}
