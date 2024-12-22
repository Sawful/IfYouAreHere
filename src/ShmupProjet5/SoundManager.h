#pragma once
#include "SFML/Audio.hpp"

enum SoundType
{
	HITSOUND,
	WEAPONUPSOUND,
	ENEMYDEATHSOUND,
	PICKUPSOUND
};

enum MusicType
{
	STAGE1,
	STAGE1BOSS,
	STAGE2BOSS
};

class SoundManager
{
	sf::Sound mHitSound;
	sf::SoundBuffer mHitSoundBuffer;

	sf::Sound mEnemyDeathSound;
	sf::SoundBuffer mEnemyDeathSoundBuffer;

	sf::Sound mWeaponUpSound;
	sf::SoundBuffer mWeaponUpSoundBuffer;

	sf::Sound mPickupSound;
	sf::SoundBuffer mPickupSoundBuffer;

	sf::Music* mCurrentMusic;

	sf::Music mStage1;
	sf::Music mStage1Boss;
	sf::Music mStage2Boss;

public:
	SoundManager();
	~SoundManager();

	void PlaySound(SoundType sound);
	void ChangeMusic(MusicType newMusic);
};

