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
#include "../Headers/componentsensorline.h"

#define GRAVITY 98
#define START_BULLET_SIZE_W 10
#define START_BULLET_SIZE_H 20
#define START_SHOOTER_SIZE_W 50
#define START_SHOOTER_SIZE_H 25
#define START_COLLISIONER_SIZE_W 20
#define START_COLLISIONER_SIZE_H 20
#define START_PLAYER_SIZE_W 20
#define START_PLAYER_SIZE_H 20
#define POPING_PLAYER_THRESHOLD 100
#define INFINITE 9999

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
	playerImage->SetHandle(playerImage->GetWidth() / 2, playerImage->GetHeight());

	//Load Bullet Image
	imageFile = "data/bullet.png";
	bulletImage = ResourceManager::Instance().LoadImage(imageFile);
	bulletImage->SetMidHandle();

	srand(0);

	//player init
	createPlayer();


	//collisioner init
	createCollisioner();

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
	MessageGetEntityState msgGEntityState;
	player->ReciveMessage(&msgGEntityState);
	if (msgGEntityState.o_width >= POPING_PLAYER_THRESHOLD) {
		if (msgGEntityState.o_width >= INFINITE) {
			endGame = true;
		}else{
		msgGEntityState.o_width +=  INFINITE * Screen::Instance().ElapsedTime();
		msgGEntityState.o_height += INFINITE * Screen::Instance().ElapsedTime();
		MessageSetScale msgSScale(msgGEntityState.o_width, msgGEntityState.o_height);
		player->ReciveMessage(&msgSScale);
		player->Update(Screen::Instance().ElapsedTime());
		}
	}
	else {
		if (collisionersElapsedSpawnTime >= LevelManager::Instance().getCollisionerSpawnRate()) {
			collisionersElapsedSpawnTime = 0;
			createCollisioner();
		}
		else {
			collisionersElapsedSpawnTime += Screen::Instance().ElapsedTime();
		}

		if (shootersElapsedSpawnTime >= LevelManager::Instance().getShooterSpawnRate()) {
			shootersElapsedSpawnTime = 0;
			createShooter();
		}
		else {
			shootersElapsedSpawnTime += Screen::Instance().ElapsedTime();
		}
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
		MessageGetEntityType msgGType;
		for (uint32 i = 0; i < deadEnemies.Size(); i++)
		{
			if (deadEnemies[i] == player) {
				msgGEntityState.o_width += POPING_PLAYER_THRESHOLD;
				msgGEntityState.o_height += POPING_PLAYER_THRESHOLD;
				MessageSetScale msgSScale(msgGEntityState.o_width, msgGEntityState.o_height);
				player->ReciveMessage(&msgSScale);
			}else{
			deadEnemies[i]->ReciveMessage(&msgGSprite);
			deadEnemies[i]->ReciveMessage(&msgGType);
			scene->DeleteSprite(msgGSprite.o_sprite);
			entities.Remove(deadEnemies[i]);
			delete deadEnemies[i];
			if (msgGType.o_eType == ETSHOOTER) {
				game->setScore(game->getScore() + (10 * (min<double>(LevelManager::Instance().getShooterHSpeed(), LevelManager::Instance().getShooterVSpeed()) / max<double>(LevelManager::Instance().getShooterHSpeed(), LevelManager::Instance().getShooterVSpeed()))));
			}
			}
		}
		deadEnemies.Clear();
	}
}

void World::draw()
{

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
			Renderer::Instance().DrawLine(msgFiringVector.o_originX, msgFiringVector.o_originY, msgFiringVector.o_targetX, msgFiringVector.o_targetY);
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
	ComponentEntityState *state = new ComponentEntityState(originX, originY, 0, 0, START_BULLET_SIZE_W, START_BULLET_SIZE_H);
	bullet->AddComponent(state);
	ComponentAutomaticMovement * movement = new ComponentAutomaticMovement(0, GRAVITY, true, &deadEnemies);
	movement->SetBoundaries(0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
	bullet->AddComponent(movement);
	ComponentCollision * collision = new ComponentCollision(bulletSprite->GetCollision(), &deadEnemies);
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
	ComponentEntityState *state = new ComponentEntityState(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight(), 0, 0, START_PLAYER_SIZE_W, START_PLAYER_SIZE_H);
	player->AddComponent(state);
	ComponentPlayerControl * control = new ComponentPlayerControl(100, 100);
	player->AddComponent(control);
	ComponentFire * fire = new ComponentFire(0.5, nullptr, this);
	player->AddComponent(fire);
	ComponentCollision * collision = new ComponentCollision(playerSprite->GetCollision(), &deadEnemies);
	player->AddComponent(collision);
	entities.Add(player);
}

void World::createCollisioner()
{
	Entity * collider = new Entity();
	ComponentType * type = new ComponentType(ETCOLLISIONER);
	collider->AddComponent(type);
	Sprite *colliderSprite = scene->CreateSprite(collisionerImage);
	colliderSprite->SetCollision(Sprite::COLLISION_RECT);
	ComponentRender * body = new ComponentRender(colliderSprite);
	collider->AddComponent(body);
	ComponentEntityState *state = new ComponentEntityState(Screen::Instance().GetWidth(), Screen::Instance().GetHeight() - rand() % 50, 0, 0, START_COLLISIONER_SIZE_W, START_COLLISIONER_SIZE_H);
	collider->AddComponent(state);
	ComponentAutomaticMovement * movement = new ComponentAutomaticMovement(LevelManager::Instance().getCollisionerHSpeed(), LevelManager::Instance().getCollisionerVSpeed(), false, &deadEnemies);
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
	ComponentEntityState *state = new ComponentEntityState(rand() % Screen::Instance().GetWidth(), 0, 0, 0, START_SHOOTER_SIZE_W, START_SHOOTER_SIZE_H);
	shooter->AddComponent(state);
	ComponentAutomaticMovement * movement = new ComponentAutomaticMovement(LevelManager::Instance().getShooterHSpeed(), LevelManager::Instance().getShooterVSpeed(), false, &deadEnemies);
	movement->SetBoundaries(0, 0, 800, 300);
	shooter->AddComponent(movement);
	ComponentSensorLine * sensor = new ComponentSensorLine(0.5, 0.5, player, ComponentSensorLine::VERTICAL, Screen::Instance().GetHeight());
	shooter->AddComponent(sensor);
	ComponentFire * fire = new ComponentFire(0.5, bulletImage, this);
	shooter->AddComponent(fire);
	ComponentCollision * collision = new ComponentCollision(shooterSprite->GetCollision(), &deadEnemies);
	shooter->AddComponent(collision);
	entities.Add(shooter);
}

