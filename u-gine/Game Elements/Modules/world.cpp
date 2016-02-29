#include "../Headers/world.h"
#include "../../include/screen.h"
#include "../../include/resourcemanager.h"
#include "../../include/math.h"
#include "../Headers/game.h"
#include "../Headers/lvlManager.h"
#include "../Headers/enemyShooter.h"
#include "../Headers/enemyCollisioner.h"
#include "../Headers/bullet.h"
#include "../Headers/externs.h"
#include "../Headers/componentrender.h"
#include "../Headers/componententitystate.h"
#include "../Headers/componentplayercontrol.h"
#include "../Headers/componentfire.h"
#include "../Headers/componentautomovement.h"
#include "../Headers/componentcollision.h"
#include "../Headers/componenttype.h"
#include "../Headers/enumentitytype.h"

#define COLLISIONER_SPEED_LIMIT 50
#define COLLISIONER_SIZE 20
#define COLLISIONER_SPAWN_AREA 50
#define SHOOTER_SPEED_LIMIT 400
#define SHOOTER_SIZE 60
#define PLAYER_MAX_RADIOUS 20
#define INFINITE 9999
#define GRAVITY 300

extern String lvlFile;
extern Game *game;
World::World()
{
	mouseX = 0;
	mouseY = 0;
	font = nullptr;
	collisionerImage = nullptr;
	playerImage = nullptr;
	bulletImage = nullptr;
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

	//create Scene
	scene = new Scene(LevelManager::Instance().getBackgroundImage());

	//Load Collisioner Image
	imageFile = COLLISIONER_ENEMY_IMG;
	collisionerImage = ResourceManager::Instance().LoadImage(imageFile);

	//Load Player Image
	imageFile = "data/player.png";
	playerImage = ResourceManager::Instance().LoadImage(imageFile);
	playerImage->SetHandle(playerImage->GetWidth()/2,playerImage->GetHeight());

	//Load Bullet Image
	imageFile = "data/bullet.png";
	bulletImage = ResourceManager::Instance().LoadImage(imageFile);
	bulletImage->SetMidHandle();

	srand(0);

	//player init
	createPlayer();
	

	//collisioner init
	createCollider();
	createCollider();

	//shooter init
	createShooter();

}
World::~World()
{
	for (size_t i = 0; i < entities.Size(); i++)
	{
		delete entities[i];
		entities.RemoveAt(i);
	}
	delete scene;
}
void World::run()
{
	/*double elapsed = Screen::Instance().ElapsedTime();
	collisionersElapsedSpawnTime += elapsed;
	shootersElapsedSpawnTime += elapsed;
	if (player->getRadius() >= PLAYER_MAX_RADIOUS || endGame || player->isDead()) {
		if (endGame) {
			player->setRadius(PLAYER_MAX_RADIOUS);
			endGame = false;
		}
		player->setRadius(player->getRadius() + INFINITE / 2 * elapsed);
		player->setY(player->getY() - INFINITE / 2 * elapsed);
		if (player->getRadius() > INFINITE) {
			endGame = true;
		}
	}
	else {
		playerUpdate(elapsed);
		enemiesUpdate(elapsed);
	}*/
	MessageCheckCollision msgCCollision;
	for (size_t i = 0; i < entities.Size(); i++)
	{
		entities[i]->Update(Screen::Instance().ElapsedTime());
		for (int j = i + 1; j < (int)entities.Size(); j++) {
			msgCCollision.entity = entities[j];
			entities[i]->ReciveMessage(&msgCCollision);
		}
	}
	MessageGetSprite msgGSprite;
	for (uint32 i = 0; i < deadEnemies.Size(); i++)
	{
		deadEnemies[i]->ReciveMessage(&msgGSprite);
		scene->DeleteSprite(msgGSprite.o_sprite);
		entities.Remove(deadEnemies[i]);
		delete deadEnemies[i];
	}
	deadEnemies.Clear();
}

void World::draw()
{
	
	//Renderer::Instance().SetColor(255, 255, 255, 255);
	//scene->Render();
	//if (player->isFiring()) {
	//	double centerX, centerY, distance;
	//	double angle = Angle(player->getX(), player->getY(), mouseX, mouseY);
	//	double oX = DegCos(angle);
	//	double oY = DegSin(angle)*-1;
	//	if (!firstImpact) {
	//		distance = INFINITE;
	//	}
	//	else {
	//		centerX = firstImpact->getX() + firstImpact->getWidth() / 2;
	//		centerY = firstImpact->getY() + firstImpact->getHeight() / 2;
	//		distance = Distance(player->getX(), player->getY(), centerX, centerY);
	//		if (firstImpact->getType() == 'S') {
	//			game->setScore(game->getScore() + (10 + (LevelManager::Instance().getSpeedBoost() / 2)));
	//			entities.Remove(firstImpact);
	//			scene->DeleteSprite(firstImpact->GetSprite());
	//			delete(firstImpact);
	//		}
	//	}
	//	firstImpact = nullptr;
	//	Renderer::Instance().SetColor(255, 255, 0, 255);
	//	Renderer::Instance().DrawLine(player->getX(), player->getY(), player->getX() + oX *distance, player->getY() + oY * distance);
	//}
	//player->setWidth(player->getRadius() * 2);
	//player->setHeight(player->getRadius() * 2);
	//if (!player->isJumping()) {
	//	player->setY(Screen::Instance().GetHeight() - player->getHeight() / 2);
	//}
	Renderer::Instance().SetColor(255, 255, 255, 255);
	scene->Render();
	MessageGetFiringVector msgFiringVector;
	MessageGetEntityState msgEntityState;
	for (size_t i = 0; i < entities.Size(); i++)
	{
		entities[i]->ReciveMessage(&msgFiringVector);
		if (msgFiringVector.o_firing) {
			entities[i]->ReciveMessage(&msgEntityState);
			Renderer::Instance().SetColor(255, 255, 0, 255);
			Renderer::Instance().DrawLine(msgFiringVector.o_originX, msgFiringVector.o_originY,msgFiringVector.o_targetX, msgFiringVector.o_targetY);
		}
	}
}

void World::CreateBullet(Image * image, double originX, double originY, double directionX, double directionY)
{
	Entity * bullet = new Entity();
	ComponentType * type = new ComponentType(ETEBULLET);
	bullet->AddComponent(type);
	Sprite * bulletSprite = scene->CreateSprite(image);
	bulletSprite->SetCollision(Sprite::COLLISION_RECT);
	ComponentRender * body = new ComponentRender(bulletSprite);
	bullet->AddComponent(body);
	ComponentEntityState *state = new ComponentEntityState(originX, originY, 0, 0, 10, 20);
	bullet->AddComponent(state);
	ComponentAutomaticMovement * movement = new ComponentAutomaticMovement(0, 98, false);
	movement->SetBoundaries(0, 0, 800, 600);
	bullet->AddComponent(movement);
	ComponentCollision * collision = new ComponentCollision(bulletSprite->GetCollision(),&deadEnemies);
	bullet->AddComponent(collision);

	entities.Add(bullet);
}

void World::createPlayer()
{
	player = new Entity();
	ComponentType * type = new ComponentType(ETPLAYER);
	player->AddComponent(type);
	Sprite *playerSprite = scene->CreateSprite(playerImage);
	playerSprite->SetCollision(Sprite::COLLISION_CIRCLE);
	ComponentRender * body = new ComponentRender(playerSprite);
	player->AddComponent(body);
	ComponentEntityState *state = new ComponentEntityState(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight(),0,0,20,20);
	player->AddComponent(state);
	ComponentPlayerControl * control = new ComponentPlayerControl(10, 10);
	player->AddComponent(control);
	ComponentFire * fire = new ComponentFire(0.5,nullptr,this);
	player->AddComponent(fire);
	ComponentCollision * collision = new ComponentCollision(playerSprite->GetCollision(), &deadEnemies);
	player->AddComponent(collision);
	entities.Add(player);
}

void World::createCollider()
{
	Entity * collider = new Entity();
	ComponentType * type = new ComponentType(ETCOLLISIONER);
	collider->AddComponent(type);
	Sprite *colliderSprite = scene->CreateSprite(collisionerImage);
	colliderSprite->SetCollision(Sprite::COLLISION_RECT);
	ComponentRender * body = new ComponentRender(colliderSprite);
	collider->AddComponent(body);
	ComponentEntityState *state = new ComponentEntityState(Screen::Instance().GetWidth(), Screen::Instance().GetHeight()-rand() % 50, 0, 0, 20, 20);
	collider->AddComponent(state);
	ComponentAutomaticMovement * movement = new ComponentAutomaticMovement(-50, 0,false);
	movement->SetBoundaries(0, 500, 800, 600);
	collider->AddComponent(movement);
	ComponentCollision * collision = new ComponentCollision(colliderSprite->GetCollision(), &deadEnemies);
	collider->AddComponent(collision);
	entities.Add(collider);
}

void World::createShooter()
{
	Entity * shooter = new Entity();
	ComponentType * type = new ComponentType(ETSHOOTER);
	shooter->AddComponent(type);
	Sprite *shooterSprite = scene->CreateSprite(LevelManager::Instance().getShooterImage());
	shooterSprite->SetCollision(Sprite::COLLISION_RECT);
	ComponentRender * body = new ComponentRender(shooterSprite);
	shooter->AddComponent(body);
	ComponentEntityState *state = new ComponentEntityState(20, 20, 0, 0, 50, 25);
	shooter->AddComponent(state);
	ComponentAutomaticMovement * movement = new ComponentAutomaticMovement(50, 100, false);
	movement->SetBoundaries(0, 0, 800, 300);
	shooter->AddComponent(movement);
	ComponentCollision * collision = new ComponentCollision(shooterSprite->GetCollision(), &deadEnemies);
	shooter->AddComponent(collision);
	entities.Add(shooter);
}

void World::playerUpdate(double elapsed)
{
	/*if (player->isFiring()) {
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
			player->setY(player->getY() + GRAVITY * elapsed*player->getDirection());
		}
		if (player->getY() >= Screen::Instance().GetHeight() - player->getHeight() / 2 && player->getDirection() == Player::DOWN) {
			player->setY(Screen::Instance().GetHeight() - player->getHeight() / 2);
			player->land();
			player->setDirection(Player::UP);
		}
	}
	if (!player->isJumping()) {
		player->setY(Screen::Instance().GetHeight() - player->getHeight() / 2);
	}*/
}

void World::enemiesUpdate(double elapsed)
{
	//for (size_t i = 0; i < entities.Size(); i++)
	//{
	//	if (entities[i]->getType() != 'P') {
	//		double x;
	//		entities[i]->update(elapsed);
	//		switch (entities[i]->getType())
	//		{
	//		case 'S':
	//			x = entities[i]->getX();
	//			if (entities[i]->getX() > player->getX()- player->getRadius() && entities[i]->getX()< player->getX() + player->getRadius() && reinterpret_cast<EnemyShooter*>(entities[i])->readyToShoot()) {
	//				double w, h;
	//				w = entities[i]->getWidth();
	//				h = entities[i]->getHeight();
	//				reinterpret_cast<EnemyShooter*>(entities[i])->fire();
	//				Sprite * bulletSprite = scene->CreateSprite(bulletImage);
	//				Bullet *bullet = new Bullet(bulletSprite, String::FromInt(elapsed), entities[i]->getX(), entities[i]->getY(), bulletImage->GetHeight(), bulletImage->GetWidth());
	//				bullet->setSpeed(GRAVITY/2);
	//				entities.Add(bullet);
	//			}
	//			break;
	//		case 'C':
	//			if (rectCircleColision(entities[i]->getX(), entities[i]->getY(), entities[i]->getWidth(), entities[i]->getHeight(), player->getX(), player->getY(), player->getWidth() / 2, player->getHeight() / 2)) {
	//				entities[i]->kill();
	//				player->setRadius(player->getRadius() + 1);
	//				player->setY(player->getY() - 1);
	//			}
	//			break;
	//		case 'B':
	//			if (rectCircleColision(entities[i]->getX(), entities[i]->getY(), entities[i]->getWidth(), entities[i]->getHeight(), player->getX(), player->getY(), player->getWidth() / 2, player->getHeight() / 2)) {
	//				entities[i]->kill();
	//				player->kill();
	//			}
	//			break;
	//		}
	//		
	//		if (entities[i]->isDead()) {
	//			deadEnemies.Add(entities[i]);
	//		}
	//	}
	//}
	//for (size_t i = 0; i < deadEnemies.Size(); i++)
	//{
	//	scene->DeleteSprite(deadEnemies[i]->GetSprite());
	//	entities.Remove(deadEnemies[i]);
	//	delete deadEnemies[i];
	//}
	//deadEnemies.Clear();
	//if (!((int)collisionersElapsedSpawnTime % (int)(11 - LevelManager::Instance().getSpeedBoost())) && (int)collisionersElapsedSpawnTime) {
	//	Sprite * collisionerSprite = scene->CreateSprite(collisionerImage);
	//	EnemyCollisioner *newEnemy = new EnemyCollisioner(collisionerSprite, String::Chr('C') + String::FromInt(elapsed), Screen::Instance().GetWidth(), rand() % COLLISIONER_SPAWN_AREA + (Screen::Instance().GetHeight() - COLLISIONER_SPAWN_AREA - COLLISIONER_SIZE), COLLISIONER_SIZE, COLLISIONER_SIZE);
	//	newEnemy->setSpeed(-(rand() % (int)(COLLISIONER_SPEED_LIMIT + LevelManager::Instance().getSpeedBoost() * 10) + COLLISIONER_SPEED_LIMIT + LevelManager::Instance().getSpeedBoost() * 10));
	//	entities.Add(newEnemy);
	//	collisionersElapsedSpawnTime = 0;
	//}
	//if (!((int)shootersElapsedSpawnTime % (int)(11 - LevelManager::Instance().getSpeedBoost())) && (int)shootersElapsedSpawnTime) {
	//	Sprite * shooterSprite = scene->CreateSprite(LevelManager::Instance().getShooterImage());
	//	EnemyShooter *newEnemy = new EnemyShooter(shooterSprite, String::Chr('S') + String::FromInt(elapsed), (rand() % 1)* Screen::Instance().GetWidth(), rand() % (Screen::Instance().GetHeight() / 2), SHOOTER_SIZE, SHOOTER_SIZE);
	//	newEnemy->setSpeedX(rand() % (int)(SHOOTER_SPEED_LIMIT + LevelManager::Instance().getSpeedBoost() * 10) - ((SHOOTER_SPEED_LIMIT + LevelManager::Instance().getSpeedBoost() * 10) / 2));
	//	newEnemy->setSpeedY(rand() % (int)(SHOOTER_SPEED_LIMIT + LevelManager::Instance().getSpeedBoost() * 10) - ((SHOOTER_SPEED_LIMIT + LevelManager::Instance().getSpeedBoost() * 10) / 2));
	//	entities.Add(newEnemy);
	//	shootersElapsedSpawnTime = 0;
	//}
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

