#ifndef WORLDDEFENDER_LEVEL_MANAGER
#define WORLDDEFENDER_LEVEL_MANAGER
#include "../../include/image.h"
	class LevelManager{
	public:
		enum levelDificulty {
			EASY,
			MEDIUM,
			HARD
		};
		static LevelManager& Instance();

		virtual void loadLevel(levelDificulty difuculty);
		virtual Image * getBackgroundImage() { return this->backgroundImage; }
		virtual Image * getShooterImage() { return this->shooterImage; }
		virtual double getSpeedBoost() { return this->speedBoost; }
	protected:
		LevelManager();
		virtual ~LevelManager() {};
	private:
		Array<String> levels;
		static LevelManager * levelManager;
		Image * backgroundImage, * shooterImage;
		double speedBoost;
	};
#endif
