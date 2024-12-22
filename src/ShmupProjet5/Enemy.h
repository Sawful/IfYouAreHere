#pragma once
#include "Character.h"
#include "Level.h"
#include "Path.h"
#include "SoundManager.h"

class GameManager;

class Enemy: public Character
{
protected:
	int mHealth; // Only current health as no enemy needs to heal + probs no healthbar
	float mSpeed;
	sf::Vector2f mDirection;
	sf::Texture* mDropTexture;
	int mDropAmount; // In percent --> 45 means 45%
	Level* mCurrentStage;
	int scoreValue;
	GameManager* mGameManager;
	SoundManager* mSoundManager;
	std::vector<Path*> mMovementPath;
	int mPathNumber;

public:
	Enemy(sf::Vector2f position, float rotation, int dropAmount, sf::Texture* texture, sf::Texture* dropTexture, bool isActive);
	virtual void TakeDamage(int damage);
	virtual void Die();
	virtual void Attack() = 0;
	virtual void Move(float deltaTime);
};

