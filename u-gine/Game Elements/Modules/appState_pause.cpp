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
}

void AppStatePause::getInputs() const
{
	if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		whantedState = STATE_MENU;
	}
	else if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
		whantedState = STATE_GAME;
	}
}

void AppStatePause::activate()
{
	String fontFileName;
	fontFileName = "data/arial16.png";
	font = ResourceManager::Instance().LoadFont(fontFileName);
	this->options.Add("Start(enter)");
	this->options.Add("Exit(Esc)");
}

void AppStatePause::deactivate()
{
}
