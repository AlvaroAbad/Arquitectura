#include "../Headers/lvlManager.h"
#include "../../include/resourcemanager.h"
#include "../../include/string.h"
#define LVLINDEX "data/lvlIndex.txt"
LevelManager * LevelManager::levelManager = NULL;
LevelManager::LevelManager()
{
	String levelsFile;
	levelsFile = String::Read(LVLINDEX);
	levels = levelsFile.Split("\n");
	for (uint32 i = 0; i < levels.Size(); i++)
	{
		levels[i] = levels[i].Replace("\r", "");
	}
	backgroundImage = nullptr;
	shooterImage = nullptr;
	shooterVSpeed = 0;
	shooterHSpeed = 0;
	shooterSpawnRate = 0;
	collisionerVSpeed = 0;
	collisionerHSpeed = 0;
	collisionerSpawnRate = 0;
}
LevelManager & LevelManager::Instance()
{
	if (!levelManager)
		levelManager = new LevelManager();
	return *levelManager;
}

void LevelManager::loadLevel(levelDificulty difuculty)
{
	String levelFile;
	Array<String> levelParameters;
	switch (difuculty)
	{
	case LevelManager::EASY:
		levelFile = String::Read(levels[0]);
		break;
	case LevelManager::MEDIUM:
		levelFile = String::Read(levels[1]);
		break;
	case LevelManager::HARD:
		levelFile = String::Read(levels[2]);
		break;
	default:
		break;
	}
	levelParameters = levelFile.Split("\n");
	backgroundImage = ResourceManager::Instance().LoadImage(levelParameters[0].Replace("\r", ""));
	shooterImage = ResourceManager::Instance().LoadImage(levelParameters[1].Replace("\r", ""));
	shooterHSpeed = levelParameters[2].ToInt();
	shooterVSpeed = levelParameters[3].ToInt();
	shooterSpawnRate = levelParameters[4].ToInt();
	collisionerHSpeed = levelParameters[5].ToInt();
	collisionerVSpeed = levelParameters[6].ToInt();
	collisionerSpawnRate = levelParameters[7].ToInt();
}


