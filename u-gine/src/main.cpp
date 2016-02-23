#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
/*Practicas 2D 1-11 si cuenta con dos niveles añadir _1 o _2 para basica o avanzada*/
/*Practicas de Audio A1-A3*/
#define P11


#include "../include/u-gine.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	AudioEngine::Instance().Init();
	String *fontFileName = new String();
	*fontFileName = "../data/monospaced.png";
	String *text = new String();
	uint32 TextHeight;
	Font *font = ResourceManager::Instance().LoadFont(*fontFileName);
	*text = "FPS: 0";
	int frames;
	double seconds;
	frames = seconds = 0;
	srand(0);
#pragma region Practica 1 INIT
#ifdef P1
	int16 centerHeight, centerWidth, mouseX, mouseY, circleCenterX, circleCenterY, trueAngle;
	int16 angle = 0;
	String * title = new String();
	int32 distance;
#endif
#pragma endregion

#pragma region Practica 2 INIT
#ifdef P2
	String *fileName = new String();
	*fileName = "../data/test.png";
	Image * ballTex = ResourceManager::Instance().LoadImage(*fileName);
	ballTex->SetMidHandle();
	double rotation = 0;
	double scale = 0;
	int increment = 1;
#endif
#pragma endregion

#pragma region Practica 3 INIT
#if defined(P3_1) || defined(P3_2)
	uint32 blendModeSRC;
	uint32 blendModeDST;
	String *boxFileName = new String();
	*boxFileName = "../data/box.jpg";
	Image * boxTex = ResourceManager::Instance().LoadImage(*boxFileName);
	String *LightFileName = new String();
	*LightFileName = "../data/light.png";
	Image * lightTex = ResourceManager::Instance().LoadImage(*LightFileName);
	uint16 thirdOfWidth = Screen::Instance().GetWidth() / 3;
	uint16 eighthOfHeight = Screen::Instance().GetHeight() / 8;
	uint16 sixthdOfWidth = Screen::Instance().GetWidth() / 6;
	uint16 eighthOfWidth = Screen::Instance().GetWidth() / 8;
#endif
#pragma endregion

#pragma region Practica 4-1 INIT
#ifdef P4_1
	srand(time(0));
	Array<Sprite *> *spriteArray = new Array<Sprite *>(4);
	struct spriteSpeed {
		double x, y;
		spriteSpeed(double x, double y) {
			this->x = x;
			this->y = y;
		}
	};
	spriteSpeed * userData;
	Sprite * currentSprite;
	double incX, incY;
	String *fileName = new String();
	int32 mouseX, mouseY;
	//Basquetball
	*fileName = "data/ball.png";
	Image * bBallTex = ResourceManager::Instance().LoadImage(*fileName);
	bBallTex->SetMidHandle();
	spriteArray->Add(new Sprite(bBallTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition((rand() % (Screen::Instance().GetWidth() - bBallTex->GetWidth())) + bBallTex->GetWidth() / 2, (rand() % (Screen::Instance().GetHeight() - bBallTex->GetHeight())) + bBallTex->GetHeight() / 2);
	spriteArray->Last()->SetUserData(new spriteSpeed((rand() % 100) + 100, (rand() % 100) + 100));

	//Football
	*fileName = "data/soccer_npot.png";
	Image * fBallTex = ResourceManager::Instance().LoadImage(*fileName);
	fBallTex->SetMidHandle();
	spriteArray->Add(new Sprite(fBallTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition((rand() % (Screen::Instance().GetWidth() - fBallTex->GetWidth())) + fBallTex->GetWidth() / 2, (rand() % (Screen::Instance().GetHeight() - fBallTex->GetHeight())) + fBallTex->GetHeight() / 2);
	spriteArray->Last()->SetUserData(new spriteSpeed((rand() % 100) + 100, (rand() % 100) + 100));

	//Box
	*fileName = "data/box.jpg";
	Image * boxTex = ResourceManager::Instance().LoadImage(*fileName);
	boxTex->SetMidHandle();
	spriteArray->Add(new Sprite(boxTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition((rand() % (Screen::Instance().GetWidth() - boxTex->GetWidth())) + boxTex->GetWidth() / 2, (rand() % (Screen::Instance().GetHeight() - boxTex->GetHeight())) + boxTex->GetHeight() / 2);
	spriteArray->Last()->SetUserData(new spriteSpeed((rand() % 100) + 100, (rand() % 100) + 100));

	//Alien
	*fileName = "data/alien.png";
	Image * alienTex = ResourceManager::Instance().LoadImage(*fileName);
	alienTex->SetMidHandle();
	spriteArray->Add(new Sprite(alienTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition((rand() % (Screen::Instance().GetWidth() - alienTex->GetWidth())) + alienTex->GetWidth() / 2, (rand() % (Screen::Instance().GetHeight() - alienTex->GetHeight())) + alienTex->GetHeight() / 2);
	spriteArray->Last()->SetUserData(new spriteSpeed((rand() % 100) + 100, (rand() % 100) + 100));
#endif
#pragma endregion

#pragma region Practica 4-2 INIT
#ifdef P4_2
	srand(time(0));
	Array<Sprite *> *spriteArray = new Array<Sprite *>(4);
	Sprite * currentSprite;
	String *fileName = new String();
	int32 mouseX, mouseY;

	*fileName = "data/alien.png";
	Image * alienTex = ResourceManager::Instance().LoadImage(*fileName);
	alienTex->SetMidHandle();

	//Alien 1
	spriteArray->Add(new Sprite(alienTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition(0 + alienTex->GetWidth() / 2, 0 + alienTex->GetHeight() / 2);

	//Alien 2
	spriteArray->Add(new Sprite(alienTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition(800 - alienTex->GetWidth() / 2, 0 + alienTex->GetHeight() / 2);

	//Alien 3
	spriteArray->Add(new Sprite(alienTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition(0 + alienTex->GetWidth() / 2, 600 - alienTex->GetHeight() / 2);

	//Alien 4
	spriteArray->Add(new Sprite(alienTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition(800 - alienTex->GetWidth() / 2, 600 - alienTex->GetHeight() / 2);
#endif
#pragma endregion

#pragma region Practica 5-1 INIT
#ifdef P5_1
	Array<Sprite *> *spriteArray = new Array<Sprite *>(4);
	Sprite * currentSprite;
	String *fileName = new String();
	int32 mouseX, mouseY;

	*fileName = "data/alienanim.png";
	Image * alienTex = ResourceManager::Instance().LoadImage(*fileName, 8, 1);
	alienTex->SetMidHandle();

	//Alien 1
	spriteArray->Add(new Sprite(alienTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition(0 + alienTex->GetWidth() / 2, 0 + alienTex->GetHeight() / 2);
	spriteArray->Last()->SetFPS(16);
	spriteArray->Last()->SetScale(4, 4);

	//Alien 2
	spriteArray->Add(new Sprite(alienTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition(800 - alienTex->GetWidth() / 2, 0 + alienTex->GetHeight() / 2);
	spriteArray->Last()->SetFPS(16);
	spriteArray->Last()->SetScale(4, 4);

	//Alien 3
	spriteArray->Add(new Sprite(alienTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition(0 + alienTex->GetWidth() / 2, 600 - alienTex->GetHeight() / 2);
	spriteArray->Last()->SetFPS(16);
	spriteArray->Last()->SetScale(4, 4);

	//Alien 4
	spriteArray->Add(new Sprite(alienTex));
	spriteArray->Last()->SetBlendMode(Renderer::ALPHA);
	spriteArray->Last()->SetPosition(800 - alienTex->GetWidth() / 2, 600 - alienTex->GetHeight() / 2);
	spriteArray->Last()->SetFPS(16);
	spriteArray->Last()->SetScale(4, 4);
#endif
#pragma endregion

#pragma region Practica 5-2 INIT
#ifdef P5_2
	int32 mouseX, mouseY;
	String *fileName = new String();
	*fileName = "data/animation.xml";
	SkeletonSprite *skeleton = new SkeletonSprite(*fileName);
	skeleton->SetBlendMode(Renderer::ALPHA);
	skeleton->SetFPS(32);
#endif
#pragma endregion

#pragma region Practica 6 INIT
#ifdef P6
	*fontFileName = "../data/arial16.png";
	*text = "Hola, Mundo";
	font = ResourceManager::Instance().LoadFont(*fontFileName);
	double speedX, speedY;
	speedX = rand() % 127 + 128;
	speedY = rand() % 127 + 128;
	double x, y;
	x = y = 0;
	uint16 r, g, b, a;
	r = g = b = 255;
#endif
#pragma endregion 

#pragma region Practica 7-1 INIT
#ifdef P7_1
	String * title = new String();

	int32 incX, incY, angle;
	String *fileName = new String();
	*fileName = "../data/background.png";
	Image *backgroundImage = ResourceManager::Instance().LoadImage(*fileName);
	Scene *scene = new Scene(backgroundImage);
	*fileName = "../data/alienanim.png";
	Image *alienImage = ResourceManager::Instance().LoadImage(*fileName, 8, 1);
	alienImage->SetMidHandle();
	Sprite *alien = scene->CreateSprite(alienImage, Scene::LAYER_FRONT);
	alien->SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);
	alien->SetScale(4, 4);
	alien->SetFPS(16);
	Camera *camera = &scene->GetCamera();
	camera->SetBounds(0, 0, backgroundImage->GetWidth(), backgroundImage->GetHeight());
	camera->FollowSprite(alien);
	*title = "Alien[";
	*title += title->FromInt(alien->GetX());
	*title += ",";
	*title += title->FromInt(alien->GetY());
	*title += "]";
	*title += " Camera[";
	*title += title->FromInt(camera->GetX());
	*title += ",";
	*title += title->FromInt(camera->GetY());
	*title += "]";
#endif
#pragma endregion

#pragma region Practica 7-2 INIT
#ifdef P7_2
	String * title = new String();

	int32 incX, incY, angle;
	String *fileName = new String();
	*fileName = "../data/backlayer.png";
	Image *backLayerImage = ResourceManager::Instance().LoadImage(*fileName);
	*fileName = "../data/frontlayer.png";
	Image *frontLayerImage = ResourceManager::Instance().LoadImage(*fileName);
	ParallaxScene *scene = new ParallaxScene(backLayerImage, frontLayerImage);
	*fileName = "../data/alienanim.png";
	Image *alienImage = ResourceManager::Instance().LoadImage(*fileName, 8, 1);
	alienImage->SetMidHandle();
	Sprite *alien = scene->CreateSprite(alienImage, Scene::LAYER_FRONT);
	alien->SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);
	alien->SetScale(4, 4);
	alien->SetFPS(16);
	scene->SetAutoBackSpeed(32, 32);
	scene->SetRelativeBackSpeed(0.8, 0.8);
	scene->SetAutoFrontSpeed(-32, 32);
	scene->SetRelativeFrontSpeed(1, 1);
	Camera *camera = &scene->GetCamera();
	camera->FollowSprite(alien);
	*title = "Alien[";
	*title += title->FromInt(alien->GetX());
	*title += ",";
	*title += title->FromInt(alien->GetY());
	*title += "]";
	*title += " Camera[";
	*title += title->FromInt(camera->GetX());
	*title += ",";
	*title += title->FromInt(camera->GetY());
	*title += "]";
#endif
#pragma endregion

#pragma region Practica 8-1 INIT
#ifdef P8_1
	String *fileName = new String();
	*fileName = "../data/star.png";
	Image *starImage = ResourceManager::Instance().LoadImage(*fileName);
	starImage->SetMidHandle();
	Scene scene;
	Sprite *star = scene.CreateSprite(starImage,Scene::LAYER_FRONT);
	star->SetColor(255, 0, 0);
	Emitter *starEmitter = scene.CreateEmitter(starImage, true);
	starEmitter->SetRate(500, 1000);
	starEmitter->SetAngularVelocity(0, 360);
	starEmitter->SetLifetime(1, 2);
	starEmitter->SetVelocityX(-128, 128);
	starEmitter->SetVelocityY(-128, 128);
#endif
#pragma endregion

#pragma region Practica 8-2 INIT
#ifdef P8_2
	String *fileName = new String();
	*fileName = "../data/star.png";
	Image *starImage = ResourceManager::Instance().LoadImage(*fileName);
	starImage->SetMidHandle();
	Scene scene;
	Sprite *star = scene.CreateSprite(starImage, Scene::LAYER_FRONT);
	star->SetColor(255, 0, 0);
	Emitter *starEmitter = scene.CreateEmitter(starImage, true);
	Affector *affector;
	starEmitter->SetRate(500, 1000);
	starEmitter->SetAngularVelocity(0, 360);
	starEmitter->SetLifetime(1, 2);
	starEmitter->SetVelocityX(-128, 128);
	starEmitter->SetVelocityY(-128, 128);
	starEmitter->AddAffector("left", 0, 0, Screen::Instance().GetWidth() / 3, Screen::Instance().GetHeight());
	affector = starEmitter->getAffector("left");
		if (affector) {
			affector->SetMinColor(0, 0, 0);
			affector->SetMaxColor(255, 255, 0);
			affector->setAngularVelocity(0, 360);
		}
		starEmitter->AddAffector("right", 2*(Screen::Instance().GetWidth() / 3) + 1,0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
		affector = starEmitter->getAffector("right");
		if (affector) {
			affector->SetMinColor(0, 0, 0);
			affector->SetMaxColor(0, 255, 255);
			affector->setAngularVelocity(360, 720);
		}
#endif
#pragma endregion

#pragma region Practica 9 INIT
#ifdef P9
		double forthHeight, forthWidth;
		forthHeight = Screen::Instance().GetHeight() / 4;
		forthWidth= Screen::Instance().GetWidth() / 4;
		Array<Sprite *> objects;
		//Images
		String *fileName = new String();
		*fileName = "../data/box.jpg";
		Image *boxImage = ResourceManager::Instance().LoadImage(*fileName);
		boxImage->SetMidHandle();
		*fileName = "../data/ball.png";
		Image *ballImage = ResourceManager::Instance().LoadImage(*fileName);
		ballImage->SetMidHandle();
		*fileName = "../data/circle.png";
		Image *circleImage = ResourceManager::Instance().LoadImage(*fileName);
		circleImage->SetMidHandle();
		*fileName = "../data/rect.png";
		Image *rectImage = ResourceManager::Instance().LoadImage(*fileName);
		rectImage->SetMidHandle();
		*fileName = "../data/alien.png";
		Image *alienImage = ResourceManager::Instance().LoadImage(*fileName);
		alienImage->SetMidHandle();
		Scene scene;
		//Sprites
		Sprite *box = scene.CreateSprite(boxImage);
		box->SetPosition(forthWidth * 3, forthHeight * 3);
		box->SetCollision(Sprite::COLLISION_RECT);
		objects.Add(box);
		Sprite *ball = scene.CreateSprite(ballImage);
		ball->SetPosition(forthWidth, forthHeight);
		ball->SetCollision(Sprite::COLLISION_CIRCLE);
		objects.Add(ball);
		Sprite *alien = scene.CreateSprite(alienImage);
		alien->SetPosition(forthWidth, forthHeight * 3);
		alien->SetCollision(Sprite::COLLISION_PIXEL);
		objects.Add(alien);
		Sprite *collider = scene.CreateSprite(circleImage);
		collider->SetCollision(Sprite::COLLISION_CIRCLE);
		objects.Add(collider);
		
#endif
#pragma endregion

#pragma region Practica 10 INIT
#ifdef P10
		int32 incX, incY, angle;
		String *fileName = new String();
		*fileName = "../data/alien.png";
		Image *alienImage = ResourceManager::Instance().LoadImage(*fileName);
		alienImage->SetMidHandle();
		*fileName = "../data/map.tmx";
		Map *map = ResourceManager::Instance().LoadMap(*fileName);
		MapScene *scene = new MapScene(map);
		Sprite *alien=scene->CreateSprite(alienImage);
		alien->SetPosition(Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
		alien->SetCollision(Sprite::COLLISION_PIXEL);
		Camera *camera = &scene->GetCamera();
		camera->SetBounds(0, 0, map->GetWidth(), map->GetHeight());
		camera->FollowSprite(alien);

#endif
#pragma endregion

#pragma region Practica 11 INIT
#ifdef P11
		uint32 posX, posY, prevX,prevY;
		String *fileName = new String();
		*fileName = "../data/isoplayer.png";
		Image *isoPlayerImage = ResourceManager::Instance().LoadImage(*fileName,8,8);
		isoPlayerImage->SetMidHandle();
		*fileName = "../data/isometric.tmx";
		IsometricMap *map = ResourceManager::Instance().LoadIsometricMap(*fileName,4);
		IsometricScene *scene = new IsometricScene(map);
		IsometricSprite *isoPlayer = scene->CreateSprite(isoPlayerImage);
		isoPlayer->SetFPS(8);
		isoPlayer->SetFrameRange(0, 4);
		isoPlayer->SetPosition(map->GetTileWidth()*1.5, map->GetTileHeight()*1.5,0);
		isoPlayer->SetCollision(Sprite::COLLISION_PIXEL);
		Camera *camera = &scene->GetCamera();
		camera->FollowSprite(isoPlayer);
#endif
#pragma endregion

#pragma region Practica A1 INIT
#ifdef PA1
		String *fileName = new String();
		*fileName = "../data/music.wav";
		AudioBuffer * audio = new AudioBuffer(*fileName);
		AudioSource * source = new AudioSource(audio);
		float spX, spY,spZ,pitch, gain;
		spX =  0;
		spY = 0;
		spZ = 0;
		pitch = 1;
		gain = 1;
		Listener::Instance().SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2, 0);
#endif
#pragma endregion

#pragma region Practica A2 INIT
#ifdef PA2
		float rotationCenterX, rotationCenterY, prevCircleCenterX, prevCircleCenterY, circleCenterX, circleCenterY, velX,velY,rotationRadius;
		double angle = 0;
		String *fileName = new String();
		*fileName = "../data/engine.wav";
		AudioBuffer * audio = new AudioBuffer(*fileName);
		AudioSource * source = new AudioSource(audio);
		source->SetGain(100);
		source->SetLooping(true);
		float lpX, lpY,prevLpX,prevLpY, pitch, gain;
		prevLpX=lpX = 0;
		prevLpY=lpY = 0;
		pitch = 1;
		gain = 1;
		rotationCenterX = Screen::Instance().GetWidth() / 2;
		rotationCenterY = Screen::Instance().GetHeight() / 2;
		rotationRadius= Screen::Instance().GetWidth() / 4;
		AudioEngine::Instance().SetDopplerFactor(1);
		prevCircleCenterY = rotationCenterY + (20 * DegSin(angle)*-1); //calc center Y of circle orbiting square
		prevCircleCenterX = rotationCenterX + (20 * DegCos(angle)); //calc center X of circle orbiting square
#endif
#pragma endregion

#pragma region Practica A3 INIT
#ifdef PA3
		String *fileName = new String();
		*fileName = "../data/mutant.ogg";
		AudioSource * source = new AudioSource(*fileName);
		source->SetLooping(false);
		float spX, spY, spZ, pitch, gain;
		spX = 0;
		spY = 0;
		spZ = 0;
		pitch = 1;
		gain = 1;
		Listener::Instance().SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2, 0);
		source->Play();
#endif
#pragma endregion
	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
#pragma region Practica 1 
#ifdef P1
		angle++;
		angle = WrapValue(angle, 360); //wrap counter between [0,360)
		centerHeight = Screen::Instance().GetHeight() / 2; //calc Vertical center of viewPort
		centerWidth = Screen::Instance().GetWidth() / 2; //calc Horizontal center of viewPort
		mouseY = Screen::Instance().GetMouseY(); //get mouse position X
		mouseX = Screen::Instance().GetMouseX(); //get mouse position Y

		circleCenterY = Screen::Instance().GetMouseY() + (20 * DegSin(angle)*-1); //calc center Y of circle orbiting square
		circleCenterX = Screen::Instance().GetMouseX() + (20 * DegCos(angle)); //calc center X of circle orbiting square

		*title = "Angle: ";
		trueAngle = Angle(mouseX, mouseY, circleCenterX, circleCenterY);
		*title += String::FromInt(trueAngle);
		*title += "º-Distance: ";
		distance = Distance(centerWidth, centerHeight, mouseX, mouseY);
		*title += String::FromInt(distance);

		Screen::Instance().SetTitle(*title);

		Renderer::Instance().SetColor(255, 0, 0, 0);
		Renderer::Instance().DrawRect(centerWidth - 10, centerHeight - 10, 20, 20);

		Renderer::Instance().SetColor(0, 255, 0, 0);
		Renderer::Instance().DrawRect(mouseX - 5, mouseY - 5, 10, 10);

		Renderer::Instance().SetColor(0, 0, 255, 0);
		Renderer::Instance().DrawEllipse(circleCenterX, circleCenterY, 5, 5);

		// Refrescamos la pantalla
		Screen::Instance().Refresh();
		Renderer::Instance().Clear(0, 0, 0);
#endif
#pragma endregion

#pragma region Practica 2
#ifdef P2
		scale += ((2 * increment) * Screen::Instance().ElapsedTime());
		rotation += (30 * Screen::Instance().ElapsedTime());
		if (scale >= 5) {
			increment = -1;
		}
		else if (scale <= 0.5) {
			increment = 1;
		}
		Renderer::Instance().SetBlendMode(Renderer::ALPHA);
		Renderer::Instance().DrawImage(ballTex, Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY(), 0, ballTex->GetWidth()*scale, ballTex->GetHeight()*scale, rotation);
#endif
#pragma endregion

#pragma region Practica 3-1
#ifdef P3_1
		Renderer::Instance().SetBlendMode(Renderer::SOLID);
		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawRect(thirdOfWidth, 0, thirdOfWidth, Screen::Instance().GetHeight());
		//SOLID
			//RED
		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(3 * sixthdOfWidth, eighthOfHeight, 37, 37);
		//GREEN
		Renderer::Instance().SetColor(0, 255, 0, 255);
		Renderer::Instance().DrawEllipse(3 * sixthdOfWidth - 18, eighthOfHeight + 37, 37, 37);
		//BLUE
		Renderer::Instance().SetColor(0, 0, 255, 255);
		Renderer::Instance().DrawEllipse(3 * sixthdOfWidth + 18, eighthOfHeight + 37, 37, 37);
		//ALPHA
		Renderer::Instance().SetBlendMode(Renderer::ALPHA);
		//RED
		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(sixthdOfWidth, 4 * eighthOfHeight - 37, 37, 37);
		//GREEN
		Renderer::Instance().SetColor(0, 255, 0, 128);
		Renderer::Instance().DrawEllipse(sixthdOfWidth - 18, 4 * eighthOfHeight, 37, 37);
		//BLUE
		Renderer::Instance().SetColor(0, 0, 255, 128);
		Renderer::Instance().DrawEllipse(sixthdOfWidth + 18, 4 * eighthOfHeight, 37, 37);
		//MULTIPLICATIVE
		Renderer::Instance().SetBlendMode(Renderer::MULTIPLICATIVE);
		//RED
		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(3 * sixthdOfWidth, 7 * eighthOfHeight - 37, 37, 37);
		//GREEN
		Renderer::Instance().SetColor(0, 255, 0, 255);
		Renderer::Instance().DrawEllipse(3 * sixthdOfWidth - 18, 7 * eighthOfHeight, 37, 37);
		//BLUE
		Renderer::Instance().SetColor(0, 0, 255, 255);
		Renderer::Instance().DrawEllipse(3 * sixthdOfWidth + 18, 7 * eighthOfHeight, 37, 37);
		//ADDITIVE
		Renderer::Instance().SetBlendMode(Renderer::ADDITIVE);
		//RED
		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(5 * sixthdOfWidth, 4 * eighthOfHeight - 37, 37, 37);
		//GREEN
		Renderer::Instance().SetColor(0, 255, 0, 255);
		Renderer::Instance().DrawEllipse(5 * sixthdOfWidth - 18, 4 * eighthOfHeight, 37, 37);
		//BLUE
		Renderer::Instance().SetColor(0, 0, 255, 255);
		Renderer::Instance().DrawEllipse(5 * sixthdOfWidth + 18, 4 * eighthOfHeight, 37, 37);
#endif
#pragma endregion

#pragma region Practica 3-2
#ifdef P3_2
		Renderer::Instance().SetBlendMode(Renderer::SOLID);
		for (unsigned int x = 0; x < 8; x++)
		{
			for (unsigned int y = 0; y < 8; y++)
			{
				Renderer::Instance().SetBlendMode(Renderer::SOLID);
				Renderer::Instance().DrawImage(boxTex, (eighthOfWidth*x) + 20, (eighthOfHeight*y) + 5);
				switch (x) {
				case 0:
					switch (y) {
					case 0:
						glBlendFunc(GL_ZERO, GL_ZERO);
						break;
					case 1:
						glBlendFunc(GL_ZERO, GL_ONE);
						break;
					case 2:
						glBlendFunc(GL_ZERO, GL_SRC_COLOR);
						break;
					case 3:
						glBlendFunc(GL_ZERO, GL_DST_COLOR);
						break;
					case 4:
						glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
						break;
					case 5:
						glBlendFunc(GL_ZERO, GL_ONE_MINUS_DST_COLOR);
						break;
					case 6:
						glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
						break;
					case 7:
						glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
						break;
					}
					break;
				case 1:
					switch (y) {
					case 0:
						glBlendFunc(GL_ONE, GL_ZERO);
						break;
					case 1:
						glBlendFunc(GL_ONE, GL_ONE);
						break;
					case 2:
						glBlendFunc(GL_ONE, GL_SRC_COLOR);
						break;
					case 3:
						glBlendFunc(GL_ONE, GL_DST_COLOR);
						break;
					case 4:
						glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
						break;
					case 5:
						glBlendFunc(GL_ONE, GL_ONE_MINUS_DST_COLOR);
						break;
					case 6:
						glBlendFunc(GL_ONE, GL_SRC_ALPHA);
						break;
					case 7:
						glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
						break;
					}
					break;
				case 2:
					switch (y) {
					case 0:
						glBlendFunc(GL_SRC_COLOR, GL_ZERO);
						break;
					case 1:
						glBlendFunc(GL_SRC_COLOR, GL_ONE);
						break;
					case 2:
						glBlendFunc(GL_SRC_COLOR, GL_SRC_COLOR);
						break;
					case 3:
						glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
						break;
					case 4:
						glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
						break;
					case 5:
						glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
						break;
					case 6:
						glBlendFunc(GL_SRC_COLOR, GL_SRC_ALPHA);
						break;
					case 7:
						glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
						break;
					}
					break;
				case 3:
					switch (y) {
					case 0:
						glBlendFunc(GL_DST_COLOR, GL_ZERO);
						break;
					case 1:
						glBlendFunc(GL_DST_COLOR, GL_ONE);
						break;
					case 2:
						glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
						break;
					case 3:
						glBlendFunc(GL_DST_COLOR, GL_DST_COLOR);
						break;
					case 4:
						glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
						break;
					case 5:
						glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR);
						break;
					case 6:
						glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA);
						break;
					case 7:
						glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
						break;
					}
					break;
				case 4:
					switch (y) {
					case 0:
						glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ZERO);
						break;
					case 1:
						glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE);
						break;
					case 2:
						glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_SRC_COLOR);
						break;
					case 3:
						glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR);
						break;
					case 4:
						glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
						break;
					case 5:
						glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
						break;
					case 6:
						glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA);
						break;
					case 7:
						glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
						break;
					}
					break;
				case 5:
					switch (y) {
					case 0:
						glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
						break;
					case 1:
						glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
						break;
					case 2:
						glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_SRC_COLOR);
						break;
					case 3:
						glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_DST_COLOR);
						break;
					case 4:
						glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
						break;
					case 5:
						glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_DST_COLOR);
						break;
					case 6:
						glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA);
						break;
					case 7:
						glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
						break;
					}
					break;
				case 6:
					switch (y) {
					case 0:
						glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
						break;
					case 1:
						glBlendFunc(GL_SRC_ALPHA, GL_ONE);
						break;
					case 2:
						glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
						break;
					case 3:
						glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
						break;
					case 4:
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
						break;
					case 5:
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR);
						break;
					case 6:
						glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
						break;
					case 7:
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						break;
					}
					break;
				case 7:
					switch (y) {
					case 0:
						glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ZERO);
						break;
					case 1:
						glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE);
						break;
					case 2:
						glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_COLOR);
						break;
					case 3:
						glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_DST_COLOR);
						break;
					case 4:
						glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
						break;
					case 5:
						glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR);
						break;
					case 6:
						glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
						break;
					case 7:
						glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						break;
					}
					break;
				}
				Renderer::Instance().DrawImage(lightTex, (eighthOfWidth*x) + 20, (eighthOfHeight*y) + 5);
			}
		}
#endif
#pragma endregion

#pragma region Practica 4-1
#ifdef P4_1
		for (unsigned int i = 0; i < spriteArray->Size(); i++) {
			currentSprite = (*spriteArray)[i];
			userData = static_cast<spriteSpeed *>(currentSprite->GetUserData());
			incX = userData->x*Screen::Instance().ElapsedTime();
			incY = userData->y*Screen::Instance().ElapsedTime();
			if ((currentSprite->GetX() + incX) + (currentSprite->GetImage()->GetWidth() / 2)>Screen::Instance().GetWidth() || (currentSprite->GetX() + incX) - (currentSprite->GetImage()->GetWidth() / 2) < 0) {
				currentSprite->SetX(currentSprite->GetX() + (incX*-1));
				userData->x = userData->x*-1;
			}
			else {
				currentSprite->SetX(currentSprite->GetX() + incX);
			}
			if ((currentSprite->GetY() + incY) + (currentSprite->GetImage()->GetHeight() / 2) > Screen::Instance().GetHeight() || (currentSprite->GetY() + incY) - (currentSprite->GetImage()->GetHeight() / 2) < 0) {
				currentSprite->SetY(currentSprite->GetY() + (incY*-1));
				userData->y = userData->y*-1;
			}
			else {
				currentSprite->SetY(currentSprite->GetY() + incY);
			}
			currentSprite->Render();
		}
#endif
#pragma endregion

#pragma region Practica 4-2
#ifdef P4_2
		mouseX = Screen::Instance().GetMouseX();
		mouseY = Screen::Instance().GetMouseY();

		for (unsigned int i = 0; i < spriteArray->Size(); i++) {
			currentSprite = (*spriteArray)[i];
			currentSprite->MoveTo(mouseX, mouseY, 100 + (i * 100));

			if (currentSprite->GetX() == mouseX && currentSprite->GetY() == mouseY) {
				currentSprite->RotateTo(0, 30);
			}
			else {
				if (currentSprite->GetX() < mouseX) {
					currentSprite->RotateTo(-15, 30);
				}
				else {
					currentSprite->RotateTo(15, 30);
				}
			}

			currentSprite->Update(Screen::Instance().ElapsedTime());
			currentSprite->Render();
		}
#endif
#pragma endregion

#pragma region Practica 5-1
#ifdef P5_1 
		mouseX = Screen::Instance().GetMouseX();
		mouseY = Screen::Instance().GetMouseY();

		for (unsigned int i = 0; i < spriteArray->Size(); i++) {
			currentSprite = (*spriteArray)[i];
			currentSprite->MoveTo(mouseX, mouseY, 100 + (i * 100));

			if (currentSprite->GetX() == mouseX && currentSprite->GetY() == mouseY) {
				currentSprite->RotateTo(0, 30);
			}
			else {
				if (currentSprite->GetX() < mouseX) {
					currentSprite->RotateTo(-15, 30);
				}
				else {
					currentSprite->RotateTo(15, 30);
				}
			}

			currentSprite->Update(Screen::Instance().ElapsedTime());
			currentSprite->Render();
		}
#endif
#pragma endregion

#pragma region Practica 5-2
#ifdef P5_2
		mouseX = Screen::Instance().GetMouseX();
		mouseY = Screen::Instance().GetMouseY();
		skeleton->SetPosition(mouseX, mouseY);
		skeleton->Update(Screen::Instance().ElapsedTime());
		skeleton->Render();
#endif
#pragma endregion

#pragma region Practica 6
#ifdef P6
		x += speedX*Screen::Instance().ElapsedTime();
		y += speedY*Screen::Instance().ElapsedTime();
		if (x + font->GetTextWidth(*text) > Screen::Instance().GetWidth()) {
			x = Screen::Instance().GetWidth() - font->GetTextWidth(*text);
			speedX *= -1;
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;
		}
		else if(x<=0) {
			x =0;
			speedX *= -1;
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;
		}
		if ( y + font->GetTextHeight(*text) >= Screen::Instance().GetHeight()) {
			y = Screen::Instance().GetHeight() - font->GetTextHeight(*text);
			speedY *= -1;
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;
		}
		else if (y <= 0) {
			y = 0;
			speedY *= -1;
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;
		}
		Renderer::Instance().SetColor(r, g, b, 225);
		Renderer::Instance().DrawText(font, *text, x, y);
#endif
#pragma endregion

#pragma region Practica 7-1
#ifdef P7_1
		Screen::Instance().SetTitle(*title);
		incX = incY = angle = 0;
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP) && alien->GetY() - alien->GetImage()->GetHeight()*alien->GetScaleY() / 2 > 0) {
			incY-=100;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN) && alien->GetY() + alien->GetImage()->GetHeight()*alien->GetScaleY() / 2 < backgroundImage->GetHeight()) {
			incY+=100;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT) && alien->GetX() - alien->GetImage()->GetWidth()*alien->GetScaleX() / 2 > 0) {
			incX-=100;
			angle += 15;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT) && alien->GetX() + alien->GetImage()->GetWidth()*alien->GetScaleX() / 2 < backgroundImage->GetWidth()) {
			incX+=100;
			angle -= 15;
		}
		alien->MoveTo(alien->GetX() + incX, alien->GetY() + incY, 100);
		alien->RotateTo(angle, 30);
		scene->Update(Screen::Instance().ElapsedTime());
		scene->Render();
		*title = "Alien[";
		*title += title->FromInt(alien->GetX());
		*title += ",";
		*title += title->FromInt(alien->GetY());
		*title += "]";
		*title += " Camera[";
		*title += title->FromInt(camera->GetX());
		*title += ",";
		*title += title->FromInt(camera->GetY());
		*title += "]";
#endif
#pragma endregion

#pragma region Practica 7-2
#ifdef P7_2
		Screen::Instance().SetTitle(*title);
		incX = incY = angle = 0;
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			incY--;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			incY++;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT)) {
			incX--;
			angle += 15;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT)) {
			incX++;
			angle -= 15;
		}
		alien->MoveTo(alien->GetX() + incX, alien->GetY() + incY, 100);
		alien->RotateTo(angle, 30);
		scene->Update(Screen::Instance().ElapsedTime());
		scene->Render();
		*title = "Alien[";
		*title += title->FromInt(alien->GetX());
		*title += ",";
		*title += title->FromInt(alien->GetY());
		*title += "]";
		*title += " Camera[";
		*title += title->FromInt(camera->GetX());
		*title += ",";
		*title += title->FromInt(camera->GetY());
		*title += "]";
#endif
#pragma endregion

#pragma region Practica 8
#if defined(P8_1) || defined(P8_2)
		
		if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			if (!starEmitter->IsEmitting()) {
				starEmitter->Start();
			}
		}
		else {
			starEmitter->Stop();
		}
		star->SetPosition(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY());
		starEmitter->SetPosition(star->GetX(), star->GetY());
		scene.Update(Screen::Instance().ElapsedTime());
		scene.Render();
		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawLine(Screen::Instance().GetWidth() / 2, 0, Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight());
#endif
#pragma endregion

#pragma region Practica 9
#ifdef P9
		if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			collider->SetImage(circleImage);
			collider->SetRadius(circleImage->GetHeight() / 2);
			collider->SetCollision(Sprite::COLLISION_CIRCLE);

		}
		else if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			collider->SetImage(rectImage);
			collider->SetRadius(rectImage->GetHeight() / 2);
			collider->SetCollision(Sprite::COLLISION_RECT);
		}
		else if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
			collider->SetImage(alienImage);
			collider->SetRadius(alienImage->GetHeight() / 2);
			collider->SetCollision(Sprite::COLLISION_PIXEL);
		}
		for (uint32 i = 0; i < objects.Size(); i++)
		{
			if (objects[i]->DidCollide()) {
				objects[i]->SetColor(255, 0, 0, 255);
			}
			else {
				objects[i]->SetColor(255, 255, 255, 255);
			}
		}
		collider->SetPosition(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY());
		scene.Update(Screen::Instance().ElapsedTime());
		scene.Render();
			
#endif
#pragma endregion

#pragma region Practica 10
#ifdef P10
		incX = incY = angle = 0;
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP) && alien->GetY() - alien->GetImage()->GetHeight()*alien->GetScaleY() / 2 > 0) {
			incY -= 100;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN) && alien->GetY() + alien->GetImage()->GetHeight()*alien->GetScaleY() / 2 < map->GetHeight()) {
			incY += 100;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT) && alien->GetX() - alien->GetImage()->GetWidth()*alien->GetScaleX() / 2 > 0) {
			incX -= 100;
			angle += 15;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT) && alien->GetX() + alien->GetImage()->GetWidth()*alien->GetScaleX() / 2 < map->GetWidth()) {
			incX += 100;
			angle -= 15;
		}
		alien->MoveTo(alien->GetX() + incX, alien->GetY() + incY, 100);
		alien->RotateTo(angle, 30);
		scene->Update(Screen::Instance().ElapsedTime());
		scene->Render();
#endif
#pragma endregion
		
#pragma region Practica 11
#ifdef P11
		prevX=posX = (int)isoPlayer->GetX()/map->GetTileWidth();
		prevY=posY = (int)isoPlayer->GetY()/map->GetTileHeight();
		if (!isoPlayer->IsMoving()) {
			isoPlayer->SetFPS(0);
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			
			isoPlayer->SetFrameRange(24, 28);
			posY--;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			isoPlayer->SetFrameRange(56, 60);
			posY ++;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT)) {
			isoPlayer->SetFrameRange(0, 4);
			posX --;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT)) {
			isoPlayer->SetFrameRange(40, 44);
			posX ++;
		}
		if (map->GetLayerId(posX, posY) < map->GetFirstColId() && (prevX!=posX || prevY!=posY)) {
			isoPlayer->SetFPS(8);
			isoPlayer->MoveTo(posX*(map->GetTileWidth())+ map->GetTileWidth()/2,posY*(map->GetTileHeight()) + map->GetTileHeight()/2, 100);
		}
		scene->Update(Screen::Instance().ElapsedTime());
		scene->Render();
#endif
#pragma endregion

#pragma region Practica A1
#ifdef PA1
		if (!source->IsPlaying()) {
			source->Play();
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			pitch+=0.1;
		}else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			pitch-=0.1;
		}

		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT)) {
			spX--;
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT)) {
			spX++;
		}
		if (Screen::Instance().KeyPressed('W')) {
			spY--;
		}
		else if (Screen::Instance().KeyPressed('S')) {
			spY++;
		}
		if (Screen::Instance().KeyPressed('A')) {
			gain += 0.1;
		}
		else if (Screen::Instance().KeyPressed('D')) {
			gain -= 0.1;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_KP_ADD)) {
			spZ++;
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_KP_SUBTRACT)) {
			spZ--;
		}
		source->SetPitch(pitch);
		source->SetGain(gain);
		source->SetPosition(spX, spY, spz);
		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(spX, spY, 10+spZ, 10+spZ);
		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawEllipse(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2, 10, 10);
		
		*text = "Pitch: ";
		*text += String::FromFloat(pitch);
		Renderer::Instance().DrawText(font, *text, 0, 0);
		TextHeight = font->GetTextHeight(*text);
		*text = "Gain: ";
		*text += String::FromFloat(gain);
		Renderer::Instance().DrawText(font, *text, 0, TextHeight);
		TextHeight += font->GetTextHeight(*text);
		*text = "Position: ";
		*text += String::FromFloat(spX) + ":" + String::FromFloat(spY) + ":" + String::FromFloat(spZ);
		Renderer::Instance().DrawText(font, *text, 0, TextHeight);
#endif
#pragma endregion

#pragma region Practica A1
#ifdef PA2
		if (!source->IsPlaying()) {
			source->Play();
		}
		angle+= 30 * Screen::Instance().ElapsedTime();
		angle = WrapValue(angle, 360); //wrap counter between [0,360)
		
		circleCenterY = rotationCenterY + (rotationRadius * DegSin(angle)*-1); //calc center Y of circle orbiting square
		circleCenterX = rotationCenterX + (rotationRadius * DegCos(angle)); //calc center X of circle orbiting square

		velX = circleCenterX - prevCircleCenterX;
		velY = circleCenterY - prevCircleCenterY;
		prevCircleCenterX = circleCenterY;
		prevCircleCenterY = circleCenterY;

		if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			lpY-=100*Screen::Instance().ElapsedTime();
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			lpY+= 100 * Screen::Instance().ElapsedTime();
		}

		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT)) {
			lpX-= 100 * Screen::Instance().ElapsedTime();
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT)) {
			lpX+= 100 * Screen::Instance().ElapsedTime();
		}


		source->SetPosition(circleCenterX, circleCenterY, 0);
		source->SetVelocity(velX, velY, 0);
		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(circleCenterX, circleCenterY, 10, 10);
		
		velX = (Screen::Instance().GetWidth() / 2+prevLpX) - (Screen::Instance().GetWidth() / 2+lpX);
		velX = (Screen::Instance().GetHeight()+prevLpY) - (Screen::Instance().GetHeight()+lpY);
		Listener::Instance().SetPosition(Screen::Instance().GetWidth()/2+lpX, Screen::Instance().GetHeight()+ lpY, 0);
		Listener::Instance().SetVelocity(velX, velX, 0);
		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawEllipse(Screen::Instance().GetWidth() / 2 + lpX, Screen::Instance().GetHeight() + lpY, 10, 10);
#endif
#pragma endregion
#pragma region Practica A3
#ifdef PA3
		
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			pitch += 0.1;
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			pitch -= 0.1;
		}

		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT)) {
			spX--;
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT)) {
			spX++;
		}
		if (Screen::Instance().KeyPressed('W')) {
			spY--;
		}
		else if (Screen::Instance().KeyPressed('S')) {
			spY++;
		}
		if (Screen::Instance().KeyPressed('A')) {
			gain += 0.1;
		}
		else if (Screen::Instance().KeyPressed('D')) {
			gain -= 0.1;
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_KP_ADD)) {
			spZ++;
		}
		else if (Screen::Instance().KeyPressed(GLFW_KEY_KP_SUBTRACT)) {
			spZ--;
		}
		source->SetPitch(pitch);
		source->SetGain(gain);
		source->SetPosition(spX, spY, spZ);
		
		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(spX, spY, 10 + spZ, 10 + spZ);
		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawEllipse(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2, 10, 10);

		*text = "Pitch: ";
		*text += String::FromFloat(pitch);
		Renderer::Instance().DrawText(font, *text, 0, 0);
		TextHeight = font->GetTextHeight(*text);
		*text = "Gain: ";
		*text += String::FromFloat(gain);
		Renderer::Instance().DrawText(font, *text, 0, TextHeight);
		TextHeight += font->GetTextHeight(*text);
		*text = "Position: ";
		*text += String::FromFloat(spX) + ":" + String::FromFloat(spY) + ":" + String::FromFloat(spZ);
		Renderer::Instance().DrawText(font, *text, 0, TextHeight);
		AudioStream::UpdateAll();
#endif
#pragma endregion
		// Refrescamos la pantalla
		Screen::Instance().Refresh();
		Renderer::Instance().Clear(0, 0, 0);
	}
	/*if (source->IsPlaying()) {
		source->Stop();
	}*/
	AudioEngine::Instance().Finish();
	Screen::Instance().Close();
	ResourceManager::Instance().FreeResources();
	//delete(title);
	/*for (unsigned int i = 0; i < spriteArray->Size(); i++) {
		delete((*spriteArray)[i]->GetUserData());
		(*spriteArray)[i]->SetUserData(nullptr);
	}*/
	return 0;
}
