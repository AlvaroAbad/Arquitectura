#include "..\Headers\world.h"
#include "../../include/screen.h"
#include "../../include/resourcemanager.h"
#include "../../include/math.h"
#include "../Headers/game.h"

#define COLLISIONER_SPEED_LIMIT 50
#define COLLISIONER_SIZE 20
#define COLLISIONER_SPAWN_AREA 50
#define SHOOTER_SPEED_LIMIT 400
#define SHOOTER_SIZE 60
#define PLAYER_MAX_RADIOUS 20
#define INFINITE 9999

extern String lvlFile;
extern Game *game;
World::World()
{
	mouseX = 0;
	mouseY = 0;
	font = nullptr;
	collisionerImage = nullptr;
	shooterImage = nullptr;
	playerImage = nullptr;
	speedBoost = 0;
	player = nullptr;
	firstImpact = nullptr;
	collisionersElapsedSpawnTime = 0;
	shootersElapsedSpawnTime = 0;
	endGame = false;
}
void World::worldInit()
{
	String imageFile;
	Array<String> lvlCfg;

	//Load Font
	String fontFileName = "data/font.png";
	font = ResourceManager::Instance().LoadFont(fontFileName);

	//Load Level Config
	imageFile = String::Read(lvlFile);
	lvlCfg = imageFile.Split("\n");

	//Load Background
	imageFile = lvlCfg[0].Replace("\r", "");
	backgroundImage = ResourceManager::Instance().LoadImage(imageFile);

	//Load Shooter Image
	imageFile = lvlCfg[1].Replace("\r", "");
	shooterImage = ResourceManager::Instance().LoadImage(imageFile);

	//Set Speed
	speedBoost = atoi(lvlCfg[2].ToCString());

	//Load Collisioner Image
	imageFile = "data/collisioner.png";
	collisionerImage = ResourceManager::Instance().LoadImage(imageFile);

	//Load Player Image
	imageFile = "data/player.png";
	playerImage = ResourceManager::Instance().LoadImage(imageFile);
	playerImage->SetMidHandle();

	srand(0);

	//player init
	player = new Player(playerImage, "0", Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() - 10, 10);
	entities.Add(player);

	//collisioner init
	EnemyCollisioner *newCollisioner = new EnemyCollisioner(collisionerImage, "0", Screen::Instance().GetWidth(), rand() % COLLISIONER_SPAWN_AREA + (Screen::Instance().GetHeight() - COLLISIONER_SPAWN_AREA - COLLISIONER_SIZE), COLLISIONER_SIZE, COLLISIONER_SIZE);
	newCollisioner->setSpeed(-(rand() % (int)(COLLISIONER_SPEED_LIMIT + speedBoost * 10) + COLLISIONER_SPEED_LIMIT + speedBoost * 10));
	entities.Add(newCollisioner);

	//shooter init
	EnemyShooter *newShooter = new EnemyShooter(shooterImage, "0", (rand() % 1)* Screen::Instance().GetWidth(), rand() % (Screen::Instance().GetHeight() / 2), SHOOTER_SIZE, SHOOTER_SIZE);
	newShooter->setSpeedX(rand() % (int)(SHOOTER_SPEED_LIMIT + speedBoost * 10) - ((SHOOTER_SPEED_LIMIT + speedBoost * 10) / 2));
	newShooter->setSpeedY(rand() % (int)(SHOOTER_SPEED_LIMIT + speedBoost * 10) - ((SHOOTER_SPEED_LIMIT + speedBoost * 10) / 2));
	entities.Add(newShooter);

}
World::~World()
{
	for (size_t i = 0; i < entities.Size(); i++)
	{
		delete entities[i];
		entities.RemoveAt(i);
	}
}
void World::run()
{
	double elapsed = Screen::Instance().ElapsedTime();
	collisionersElapsedSpawnTime += elapsed;
	shootersElapsedSpawnTime += elapsed;
	if (player->getRadius() >= PLAYER_MAX_RADIOUS || endGame) {
		if (endGame) {
			player->setRadius(PLAYER_MAX_RADIOUS);
			endGame = false;
		}
		player->setRadius(player->getRadius() + INFINITE / 2 * elapsed);
		if (player->getRadius() > INFINITE) {
			endGame = true;
		}
	}
	else {
		playerUpdate(elapsed);
		enemiesUpdate(elapsed);
	}

}

void World::draw()
{
	Renderer::Instance().SetColor(255, 255, 255, 255);
	Renderer::Instance().DrawImage(backgroundImage, 0, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
	if (player->isFiring()) {
		double centerX, centerY, distance;
		double angle = Angle(player->getX(), player->getY(), mouseX, mouseY);
		double oX = DegCos(angle);
		double oY = DegSin(angle)*-1;
		if (!firstImpact) {
			distance = INFINITE;
		}
		else {
			centerX = firstImpact->getX() + firstImpact->getWidth() / 2;
			centerY = firstImpact->getY() + firstImpact->getHeight() / 2;
			distance = Distance(player->getX(), player->getY(), centerX, centerY);
			if (firstImpact->getType() == 'S') {
				game->setScore(game->getScore() + (10 + (speedBoost / 2)));
				entities.Remove(firstImpact);
				delete(firstImpact);
			}
		}
		firstImpact = nullptr;
		Renderer::Instance().SetColor(255, 255, 0, 255);
		Renderer::Instance().DrawLine(player->getX(), player->getY(), player->getX() + oX *distance, player->getY() + oY * distance);
	}
	for (uint32 i = 0; i < entities.Size(); i++)
	{
		if (entities[i]->getType() == 'P') {
			entities[i]->setColor(255, 255 - player->getOverheat(), 255 - player->getOverheat() * 2);
			entities[i]->render();
		}
		else {
			entities[i]->render();
		}

	}
	player->setWidth(player->getRadius() * 2);
	player->setHeight(player->getRadius() * 2);
	if (!player->isJumping()) {
		player->setY(Screen::Instance().GetHeight() - player->getHeight() / 2);
	}
}

void World::playerUpdate(double elapsed)
{
	if (player->isFiring()) {
		double angle = Angle(player->getX(), player->getY(), mouseX, mouseY);
		double oX = DegCos(angle);
		double oY = DegSin(angle)*-1;

		firstImpact = nullptr;
		player->setFiringLimit(player->getFiringLimit() - elapsed);
		player->setOverheat(player->getOverheat() + 1);
		if (player->getOverheat() >= 127) {
			player->overheated();
		}
		for (size_t i = 0; i < entities.Size(); i++)
		{
			if (rayRectColision(entities[i]->getX(), entities[i]->getY(), entities[i]->getWidth(), entities[i]->getHeight(), player->getX(), player->getY(), player->getX() + oX * INFINITE, player->getY() + oY * INFINITE)) {
				if (!firstImpact) {
					firstImpact = entities[i];
				}
				else {
					if (closestRectToPoint(player->getX(), player->getY(), firstImpact->getX(), firstImpact->getY(), firstImpact->getWidth(), firstImpact->getHeight(), entities[i]->getX(), entities[i]->getY(), entities[i]->getWidth(), entities[i]->getHeight()) < 0) {
						firstImpact = entities[i];
					}
				}
			}
		}
	}
	else {
		if (player->getOverheat() > 0) {
			player->setOverheat(player->getOverheat() - 1 * elapsed);
		}
		if (player->getOverheat() <= 0) {
			player->setOverheat(0);
			player->cooled();
		}
		player->setX(player->getX() + ((100 - player->getRadius())*elapsed)*player->getMovement());
	}
	if (player->isJumping()) {
		if (player->getY() <= Screen::Instance().GetHeight() - (100 + player->getRadius())) {
			player->setDirection(Player::DOWN);
		}
		if (player->getY() <= Screen::Instance().GetHeight() - player->getHeight() / 2) {
			player->setY(player->getY() + 300 * elapsed*player->getDirection());
		}
		if (player->getY() >= Screen::Instance().GetHeight() - player->getHeight() / 2 && player->getDirection() == Player::DOWN) {
			player->setY(Screen::Instance().GetHeight() - player->getHeight() / 2);
			player->land();
			player->setDirection(Player::UP);
		}
	}
	if (!player->isJumping()) {
		player->setY(Screen::Instance().GetHeight() - player->getHeight() / 2);
	}
}

void World::enemiesUpdate(double elapsed)
{
	for (size_t i = 0; i < entities.Size(); i++)
	{
		if (entities[i]->getType() != 'P') {
			entities[i]->update(elapsed);
			if (rectCircleColision(entities[i]->getX(), entities[i]->getY(), entities[i]->getWidth(), entities[i]->getHeight(), player->getX(), player->getY(), player->getWidth() / 2, player->getHeight() / 2)) {
				entities[i]->kill();
				player->setRadius(player->getRadius() + 1);
				player->setY(player->getY() - 1);
			}
			if (entities[i]->isDead()) {
				deadEnemies.Add(entities[i]);
			}
		}
	}
	for (size_t i = 0; i < deadEnemies.Size(); i++)
	{
		entities.Remove(deadEnemies[i]);
	}
	deadEnemies.Clear();
	if (!((int)collisionersElapsedSpawnTime % (int)(11 - speedBoost)) && (int)collisionersElapsedSpawnTime) {
		EnemyCollisioner *newEnemy = new EnemyCollisioner(collisionerImage, String::Chr('C') + String::FromInt(elapsed), Screen::Instance().GetWidth(), rand() % COLLISIONER_SPAWN_AREA + (Screen::Instance().GetHeight() - COLLISIONER_SPAWN_AREA - COLLISIONER_SIZE), COLLISIONER_SIZE, COLLISIONER_SIZE);
		newEnemy->setSpeed(-(rand() % (int)(COLLISIONER_SPEED_LIMIT + speedBoost * 10) + COLLISIONER_SPEED_LIMIT + speedBoost * 10));
		entities.Add(newEnemy);
		collisionersElapsedSpawnTime = 0;
	}
	if (!((int)shootersElapsedSpawnTime % (int)(11 - speedBoost)) && (int)shootersElapsedSpawnTime) {
		EnemyShooter *newEnemy = new EnemyShooter(shooterImage, String::Chr('S') + String::FromInt(elapsed), (rand() % 1)* Screen::Instance().GetWidth(), rand() % (Screen::Instance().GetHeight() / 2), SHOOTER_SIZE, SHOOTER_SIZE);
		newEnemy->setSpeedX(rand() % (int)(SHOOTER_SPEED_LIMIT + speedBoost * 10) - ((SHOOTER_SPEED_LIMIT + speedBoost * 10) / 2));
		newEnemy->setSpeedY(rand() % (int)(SHOOTER_SPEED_LIMIT + speedBoost * 10) - ((SHOOTER_SPEED_LIMIT + speedBoost * 10) / 2));
		entities.Add(newEnemy);
		shootersElapsedSpawnTime = 0;
	}
}

bool World::rectCircleColision(double rX, double rY, double rWidth, double rHeight, double cX, double cY, double cR1, double cR2)
{
	double tlX, tlY, trX, trY, blX, blY, brX, brY;//Circle check points
	tlX = cX - cR1;
	tlY = cY - cR2;
	trX = cX + cR1;
	trY = cY - cR2;
	blX = cX - cR1;
	blY = cY + cR2;
	brX = cX + cR1;
	brY = cY + cR2;
	if (rX >= tlX && rX <= trX || rX + rWidth >= tlX && rX + rWidth <= trX) {
		if (rY >= tlY && rY <= brY || rY + rHeight >= tlY && rY + rHeight <= brY) {
			return true;
		}
	}
	return false;
}

bool World::rayRectColision(double rX, double rY, double rWidth, double rHeight, double oX, double oY, double dX, double dY)
{
	uint32 tlAngle, brAngle, lineAngle;
	tlAngle = Angle(rX, rY, oX, oY);
	brAngle = Angle(rX + rWidth, rY + rHeight, oX, oY);
	lineAngle = Angle(dX, dY, oX, oY);
	return lineAngle <= tlAngle &&  lineAngle >= brAngle;
}

int32 World::closestRectToPoint(double oX, double oY, double r1X, double r1Y, double r1Width, double r1Height, double r2X, double r2Y, double r2Width, double r2Height)
{
	uint32 ret;
	double distance[8] = {
		Distance(oX, oY, r1X, r1Y),
		Distance(oX, oY, r1X + r1Width, r1Y),
		Distance(oX, oY, r1X, r1Y + r1Height),
		Distance(oX, oY, r1X, r1Y + r1Height),
		Distance(oX, oY, r2X, r2Y),
		Distance(oX, oY, r2X + r2Width, r2Y),
		Distance(oX, oY, r2X, r2Y + r2Height),
		Distance(oX, oY, r2X + r2Width, r2Y + r2Height)
	};
	ret = 0;
	for (size_t i = 1; i < 8; i++) {
		if (distance[ret] > distance[i]) {
			ret = i;
		}
	}
	if (ret > 3) {
		return -1;
	}
	else {
		return 1;
	}
}
