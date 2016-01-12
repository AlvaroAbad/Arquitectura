#ifndef WORLDDEFENDER_LEVEL_MANAGER
#define WORLDDEFENDER_LEVEL_MANAGER
#include "../../include/image.h"
class LevelManager {
public:
	enum levelDificulty {
		EASY,
		MEDIUM,
		HARD
	};
	static LevelManager& Instance();

	virtual void loadLevel(levelDificulty difuculty);
	virtual Image * getBackgroundImage()const { return this->backgroundImage; }
		virtual Image * getShooterImage() const { return this->shooterImage; }
		virtual double getSpeedBoost() const { return this->speedBoost; }
		virtual uint32 getNumLevels() const { return levels.Size(); } 
protected:
	LevelManager();
	virtual ~LevelManager() {};
private:
	Array<String> levels;
	static LevelManager * levelManager;
	Image * backgroundImage, *shooterImage;
	double speedBoost;
};
#endif
