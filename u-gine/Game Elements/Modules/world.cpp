#include "..\Headers\world.h"
#include "../../include/screen.h"
#include "../../include/resourcemanager.h"
#include "../../include/math.h"
World::World()
{
	this->mouseX = 0;
	this->mouseY = 0;
	this->font = nullptr;
	this->collisionerImage = nullptr;
	this->shooterImage = nullptr;
	this->playerImage = nullptr;
	this->speedBoost = 0;
	this->player = nullptr;
	this->firstImpact = nullptr;
	this->collisionersElapsedSpawnTime = 0;;
	this->shootersElapsedSpawnTime = 0;
	this->endGame = false;
}
void World::worldInit()
{
	String fontFileName = "data/arial16.png";
	font = ResourceManager::Instance().LoadFont(fontFileName);
	String imageFile = "data/collisioner.png";
	collisionerImage = ResourceManager::Instance().LoadImage(imageFile);
	imageFile = "data/shooter.png";
	shooterImage = ResourceManager::Instance().LoadImage(imageFile);
	imageFile = "data/player.png";
	playerImage = ResourceManager::Instance().LoadImage(imageFile);
	playerImage->SetMidHandle();
	srand(0);
	player = new Player(playerImage, "0", Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() - 10, 10);
	enemies.Add(player);
	//collisioner init
	EnemyCollisioner *newCollisioner = new EnemyCollisioner(collisionerImage, "0", Screen::Instance().GetWidth(), rand() % 100 + (Screen::Instance().GetHeight() - 100), 20, 20);
	newCollisioner->setSpeed(-(rand() % (int)(50 + speedBoost) + 50 + speedBoost));
	enemies.Add(newCollisioner);

	//shooter init
	EnemyShooter *newShooter = new EnemyShooter(shooterImage, "0", (rand() % 1)* Screen::Instance().GetWidth(), rand() % (Screen::Instance().GetHeight() / 2), 60, 60);
	newShooter->setSpeedX(rand() % (int)(400 + speedBoost) - (200 + speedBoost));
	newShooter->setSpeedY(rand() % (int)(400 + speedBoost) - (200 + speedBoost));
	enemies.Add(newShooter);

}
World::~World()
{
	delete this->player;
	for (size_t i = 0; i < this->enemies.Size(); i++)
	{
		delete this->enemies[i];
		this->enemies.RemoveAt(i);
	}
}
void World::run()
{
	double elapsed = Screen::Instance().ElapsedTime();
	this->speedBoost += elapsed;
	collisionersElapsedSpawnTime += elapsed;
	shootersElapsedSpawnTime += elapsed;
	if (this->player->getRadius() >= 20 || this->endGame) {
		if (endGame) {
			this->player->setRadius(20);
			endGame = false;
		}
		this->player->setRadius(this->player->getRadius() + 500 * elapsed);
		if (this->player->getRadius() > 1000) {
			this->endGame = true;
		}
	}
	else {
		this->playerUpdate(elapsed);
		this->enemiesUpdate(elapsed);
	}

}

void World::draw()
{
	if (this->player->isFiring()) {
		double centerX, centerY, distance;
		double angle = Angle(player->getX(), player->getY(), mouseX, mouseY);
		double oX = DegCos(angle);
		double oY = DegSin(angle)*-1;
		if (!firstImpact) {
			distance = 1000;
		}
		else {
			centerX = this->firstImpact->getX() + this->firstImpact->getWidth() / 2;
			centerY = this->firstImpact->getY() + this->firstImpact->getHeight() / 2;
			distance = Distance(this->player->getX(), this->player->getY(), centerX, centerY);
			if (this->firstImpact->getType() == 'S') {
				enemies.Remove(this->firstImpact);
				delete(this->firstImpact);
			}
		}
		this->firstImpact = nullptr;
		Renderer::Instance().SetColor(255, 255, 0, 255);
		Renderer::Instance().DrawLine(this->player->getX(), this->player->getY(), this->player->getX() + oX *distance, this->player->getY() + oY * distance);
	}
	for (uint32 i = 0; i < this->enemies.Size(); i++)
	{
		this->enemies[i]->render();

	}
	this->player->setColor(255, 255 - player->getOverheat(), 255 - player->getOverheat() * 2);
	Renderer::Instance().SetColor(this->player->getOverheat() * 2, this->player->getOverheat(), 255 - this->player->getOverheat() * 2, 255);
	this->player->render();
	this->player->setWidth(player->getRadius() * 2);
	this->player->setHeight(player->getRadius() * 2);
	if (!this->player->isJumping()) {
		this->player->setY(Screen::Instance().GetHeight() - player->getHeight() / 2);
	}
}

void World::playerUpdate(double elapsed)
{
	if (this->player->isFiring()) {
		double angle = Angle(this->player->getX(), this->player->getY(), this->mouseX, this->mouseY);
		double oX = DegCos(angle);
		double oY = DegSin(angle)*-1;

		this->firstImpact = nullptr;
		this->player->setFiringLimit(this->player->getFiringLimit() - elapsed);
		this->player->setOverheat(this->player->getOverheat() + 1);
		if (this->player->getOverheat() >= 128) {
			this->player->overheated();
		}
		for (size_t i = 0; i < this->enemies.Size(); i++)
		{
			if (rayRectColision(this->enemies[i]->getX(), this->enemies[i]->getY(), this->enemies[i]->getWidth(), this->enemies[i]->getHeight(), this->player->getX(), this->player->getY(), this->player->getX() + oX * 1000, player->getY() + oY * 1000)) {
				if (!this->firstImpact) {
					this->firstImpact = enemies[i];
				}
				else {
					if (closestRectToPoint(this->player->getX(), this->player->getY(), this->firstImpact->getX(), this->firstImpact->getY(), this->firstImpact->getWidth(), this->firstImpact->getHeight(), this->enemies[i]->getX(), this->enemies[i]->getY(), this->enemies[i]->getWidth(), this->enemies[i]->getHeight()) < 0) {
						this->firstImpact = this->enemies[i];
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
		player->setX(player->getX() + ((100 - player->getRadius())*elapsed)*this->player->getMovement());
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
	for (size_t i = 0; i < enemies.Size(); i++)
	{	if(enemies[i]->getType()!='P'){
		this->enemies[i]->update(elapsed);
		if (this->rectCircleColision(this->enemies[i]->getX(), this->enemies[i]->getY(), this->enemies[i]->getWidth(), this->enemies[i]->getHeight(), this->player->getX(), this->player->getY(), this->player->getWidth() / 2, this->player->getHeight() / 2)) {
			this->enemies[i]->kill();
			this->player->setRadius(player->getRadius() + 1);
			this->player->setY(player->getY() - 1);
		}
		if (this->enemies[i]->isDead()) {
			this->deadEnemies.Add(enemies[i]);
		}
	}
	}
	for (size_t i = 0; i < this->deadEnemies.Size(); i++)
	{
		this->enemies.Remove(deadEnemies[i]);
	}
	this->deadEnemies.Clear();
	if (((int)this->collisionersElapsedSpawnTime % (int)(1 + this->speedBoost)) && (int)this->collisionersElapsedSpawnTime) {
		EnemyCollisioner *newEnemy = new EnemyCollisioner(this->collisionerImage, String::Chr('C') + String::FromInt(elapsed), Screen::Instance().GetWidth(), rand() % 100 + (Screen::Instance().GetHeight() - 100), 20, 20);
		newEnemy->setSpeed(-(rand() % (int)(50 + this->speedBoost) + 50 + this->speedBoost));
		this->enemies.Add(newEnemy);
		this->collisionersElapsedSpawnTime = 0;
	}
	if (((int)shootersElapsedSpawnTime % (int)(1 + speedBoost)) && (int)shootersElapsedSpawnTime) {
		EnemyShooter *newEnemy = new EnemyShooter(shooterImage, String::Chr('S') + String::FromInt(elapsed), (rand() % 1)* Screen::Instance().GetWidth(), rand() % (Screen::Instance().GetHeight() / 2), 60, 60);
		newEnemy->setSpeedX(rand() % (int)(400 + speedBoost) - (200 + speedBoost));
		newEnemy->setSpeedY(rand() % (int)(400 + speedBoost) - (200 + speedBoost));
		enemies.Add(newEnemy);
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

uint32 World::closestRectToPoint(double oX, double oY, double r1X, double r1Y, double r1Width, double r1Height, double r2X, double r2Y, double r2Width, double r2Height)
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
