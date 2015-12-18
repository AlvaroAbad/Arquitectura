#include "..\Headers\appState_pause.h"
#include"../../include/renderer.h"
#include"../../include/resourcemanager.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
#include "../Headers/externs.h"

void AppStatePause::run()
{
	this->x = Screen::Instance().GetWidth() / 2;
	this->y = Screen::Instance().GetHeight() / 2;
}

void AppStatePause::draw() const
{
	game->draw();
	uint32 posY;
	posY = this->y;
	Renderer::Instance().SetColor(204, 204, 204, 128);
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	Renderer::Instance().DrawRect(0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
	Renderer::Instance().SetColor(255, 0, 0, 255);
	for (uint8 i = 0; i < this->options.Size(); i++)
	{
		Renderer::Instance().DrawText(font, options[i], this->x - this->font->GetTextWidth(this->options[i]) / 2, posY);
		posY += this->font->GetTextHeight(options[i]);
	}
	Renderer::Instance().SetColor(255, 255, 255, 255);
	Renderer::Instance().DrawImage(selectorImage, x - 70, y + (selectedOption*font->GetHeight()), 0, 16, 16);
}

void AppStatePause::getInputs()
{
	if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
		switch (selectedOption) {
		case 0:
			whantedState = STATE_GAME;
			break;
		case 1:
			whantedState = STATE_NULL;
			break;
		}
	}
	else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			if (selectedOption < 1) {
				selectedOption++;
			}
	}
	else if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
		if (selectedOption) {
			selectedOption--;
		}
	}
}

void AppStatePause::activate()
{
	String FileName;
	FileName = "data/arial16.png";
	font = ResourceManager::Instance().LoadFont(FileName);
	FileName = "data/next.png";
	selectorImage = ResourceManager::Instance().LoadImage(FileName);
	this->options.Add("Continue");
	this->options.Add("Exit");
}

void AppStatePause::deactivate()
{
}
