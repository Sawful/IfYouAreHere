#pragma once
#include "Scene.h"

class PlayerController;
class Bullet;
class Enemy;
class Drop;
class GameManager;

class Stage: public Scene
{
protected:
	sf::Clock mStageTimer;

	sf::View mGameView;
	sf::View mScoreView;

	sf::Texture mSky;
	sf::Sprite mSkySprite;

	sf::Font mFontTest;
	sf::Text mScore;
	std::string mScoreText;

	int numbLives;
	sf::Texture lifeText;
	sf::Sprite lives;

	std::vector<Bullet*> mEnemyBullets;
	std::vector<Bullet*> mPlayerBullets;
	std::vector<Drop*> mEnemyDrops;
	std::vector<Enemy*> mEnemies;

	GameManager* mGameManager;
	PlayerController* mPlayerController;

	sf::Texture mDropTexture;

public:
	Stage(sf::RenderWindow* window, PlayerController* playerController, GameManager* gm);

	virtual void AddToEntities(Bullet* entity);
	virtual void AddToEntities(Enemy* entity);
	virtual void AddToEntities(Drop* entity);

	virtual void AddToEntities(Entity* entity);

	void ResetTimer();
	virtual void ResetScene();

	virtual void Draw() override;

	virtual void Update(float deltaTime) override;
	
	virtual void PlayStage(float deltaTime);
	PlayerController* GetPlayerController();
	virtual void EnterScene() = 0;
};

