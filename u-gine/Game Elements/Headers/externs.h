#ifndef WORLDDEFENDER_EXTERNS_H
#define WORLDDEFENDER_EXTERNS_H
#include "../Headers/game.h"
#include "../Headers/appState.h"
#define TEXT_POITION_OFFSET 70
#define SELECTOR_WIDTH_HEIGHT 16
#define MENU_START "Start"
#define MENU_CONTINUE "Continue"
#define MENU_MENU "Menu"
#define MENU_EXIT "Exit"
#define MENU_BACK "Back"
extern Game *game;
extern appStates whantedState;
extern String lvlFile;
#endif